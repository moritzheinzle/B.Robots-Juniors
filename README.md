# Bilderkennung mithilfe einer OpenMV H7 R2

Dieses Projekt wurde im Rahmen von **B.Robots Junior** entwickelt und implementiert ein System zur **Objekterkennung** und **Verifikation** für einen Roboter. Der Roboter nutzt eine Kamera und ein vortrainiertes maschinelles Lernmodell, um Objekte zu erkennen und ihre Koordinaten an ein Arduino zu senden. Das System ermöglicht es, Objekte zu verifizieren und ihre Position kontinuierlich zu überwachen.

## Funktionsweise

- **Objekterkennung**: Der Roboter nimmt mit einer Kamera Bilder auf und verwendet ein vortrainiertes TensorFlow Lite Modell, um Objekte in den Bildern zu erkennen.
- **Verifikation**: Ein Benutzer kann die Verifikation eines Objekts anfordern. Der Roboter überprüft, ob das erkannte Objekt in mehreren Frames an der gleichen Position bleibt.
- **Kommunikation**: Die Koordinaten des verifizierten Objekts werden über UART an ein Arduino gesendet. Das Arduino kann dann weiterverarbeiten oder reagieren.

## Funktionsweise der Kommunikation

Die Kommunikation zwischen dem Mikrocontroller (Pyboard) und dem Arduino erfolgt über **UART**. Die wichtigsten Zustände sind:

- **DETECTED (1)**: Ein Objekt wurde erkannt.
- **VERIFY (2)**: Eine Verifikation des Objekts wird angefordert.
- **ABORT (3)**: Die Verifikation wird abgebrochen.
- **FOUND (4)**: Das Objekt wurde erfolgreich verifiziert.
- **NOT_FOUND (5)**: Die Verifikation ist fehlgeschlagen.
- **CONTINUE (6)**: Das System setzt die Objekterkennung fort.
- **STOP (7)**: Das System stoppt die Koordinatensendung.

## Hardwareanforderungen

- **OpenMV H7 R2**: Für die Aufnahme und Verarbeitung von Bilder
- **Kommunikation**: UART 3 für Kommunikation mit dem Arduino
- **Arduino Mega**: Für die Verarbeitung der Koordinaten und mögliche Steuerung des Roboters

## Softwareanforderungen

- **MicroPython**: Das Projekt nutzt MicroPython auf dem Pyboard.
- **TensorFlow Lite**: Für das maschinelle Lernmodell zur Objekterkennung.
- **Bibliotheken**:
  - `pyb`: Für die Interaktion mit der Pyboard-Hardware.
  - `sensor`: Zur Steuerung der Kamera.
  - `image`: Zur Bildverarbeitung und Blob-Erkennung.
  - `ml`: Für das Laden und Ausführen des TensorFlow Lite Modells.
  - `uos`, `gc`: Für das Dateisystem und die Speicherkontrolle.
  - `uasyncio`: Für asynchrone Aufgaben und Zeitsteuerung.
