import time
import machine
from machine import UART
import math
import sensor
import image
import uos
import gc
import ml
import uasyncio

VERIFIED = 2
NOT_VERIFIED = 3
FOUND = 4
NOT_FOUND = 5
CONTINUE = 6
STOP = 7
FORWARD = 1
BACKWARDS = 2
STOP = 3

uart = UART(1, 9600)
p9 = machine.Pin("P9", machine.Pin.OUT)

# Sensor Setup
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.set_vflip(False)

# ML Setup
net = None
labels = None
min_confidence = 0.95
n_frames = 10
min_frames = 8

try:
    net = ml.Model("trained.tflite", load_to_fb=uos.stat('trained.tflite')[6] > (gc.mem_free() - (64 * 1024)))
except Exception:
    raise Exception("Error with tflite")

try:
    labels = [line.rstrip('\n') for line in open("labels.txt")]
except Exception:
    raise Exception("Error with labels.txt")

colors = [(255, 0, 0), (0, 255, 0), (255, 255, 0), (0, 0, 255), (255, 0, 255), (0, 255, 255), (255, 255, 255)]
threshold_list = [(math.ceil(min_confidence * 255), 255)]


def fomo_post_process(model, inputs, outputs):
    ob, oh, ow, oc = model.output_shape[0]
    x_scale = inputs[0].roi[2] / ow
    y_scale = inputs[0].roi[3] / oh
    scale = min(x_scale, y_scale)
    x_offset = ((inputs[0].roi[2] - (ow * scale)) / 2) + inputs[0].roi[0]
    y_offset = ((inputs[0].roi[3] - (ow * scale)) / 2) + inputs[0].roi[1]

    l = [[] for i in range(oc)]
    for i in range(oc):
        img = image.Image(outputs[0][0, :, :, i] * 255)
        blobs = img.find_blobs(threshold_list, x_stride=1, y_stride=1, area_threshold=1, pixels_threshold=1)
        for b in blobs:
            rect = b.rect()
            x, y, w, h = rect
            score = img.get_statistics(thresholds=threshold_list, roi=rect).l_mean() / 255.0
            x = int((x * scale) + x_offset)
            y = int((y * scale) + y_offset)
            w = int(w * scale)
            h = int(h * scale)
            l[i].append((x, y, w, h, score))
    return l


def process_frame(net, img, min_confidence):
    detection_list = []
    for i, detection in enumerate(net.predict([img], callback=fomo_post_process)):
        if i == 0: continue
        if len(detection) == 0: continue

        for x, y, w, h, score in detection:
            if score >= min_confidence:
                center_x = math.floor(x + (w / 2))
                center_y = math.floor(y + (h / 2))
                detection_list.append((center_x, center_y, score, i))
    return detection_list


async def verify_object_async(net, min_confidence, initial_label, initial_x, initial_y, n_frames=10, min_required_detection_count=8):
    detection_count = 0
    frame_count = 0
    while frame_count < n_frames:
        img = sensor.snapshot()
        detection_list = process_frame(net, img, min_confidence)
        for (center_x, center_y, score, label) in detection_list:
            if score >= min_confidence and label == initial_label:
                if abs(center_x - initial_x) < 20 and abs(center_y - initial_y) < 20:
                    detection_count += 1
        frame_count += 1
    return detection_count >= min_required_detection_count


async def send_command_async(x):
    if x < 10:
        send_to_arduino(FORWARD)
    elif x > 10:
        send_to_arduino(BACKWARDS)
    else:
        send_to_arduino(STOP)
    await uasyncio.sleep(0.05)

def send_to_arduino(message):
    if not isinstance(message, (bytes, bytearray)):
        message = bytearray([message])
    uart.write(message)

async def communication_and_detection():
    possible = False
    initial_object = None
    initial_x = initial_y = None

    while True:
        img = sensor.snapshot()
        detection_list = process_frame(net, img, min_confidence)
        print("main")
        if detection_list:
            print("detection")  # Debugging
            p9.high()
            if uart.any():
                command = uart.read().decode().strip()
                if command == str(VERIFIED):
                    possible = True
                    initial_object = detection_list[0][3]
                    initial_x, initial_y = detection_list[0][0], detection_list[0][1]
                    print("Verification started. Object detected.")
                elif command == str(NOT_VERIFIED):
                    possible = False

            if possible:
                if await verify_object_async(net, min_confidence, initial_object, initial_x, initial_y):
                    send_to_arduino(FOUND)
                    print("Verification successful.")
                    while True:
                        if uart.any():
                            command = uart.read().decode().strip()
                            if command == str(STOP):
                                print("Stop command received. Ending coordinate sending.")
                                p9.low()
                                break

                        img = sensor.snapshot()
                        detection_list = process_frame(net, img, min_confidence)
                        for (center_x, center_y, score, label) in detection_list:
                            if label == initial_object and score >= min_confidence:
                                await send_command_async(center_x)
                                await uasyncio.sleep(0.05)

                else:
                    send_to_arduino(NOT_FOUND)
                    print("Verification failed.")
                possible = False








uasyncio.run(communication_and_detection())
