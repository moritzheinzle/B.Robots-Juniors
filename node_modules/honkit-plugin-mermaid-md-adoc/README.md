# Mermaid plugin for HonKit

Plugin for [HonKit](https://github.com/honkit/honkit) which renders [Mermaid](https://github.com/knsv/mermaid) diagrams and flow charts detected in the book markdown and asciidoc.

## How to install it?

You can use install via **npm**:

```sh
npm install honkit-plugin-mermaid-md-adoc
```

And use it for your book with in the book.json:

```json
{
  "plugins": ["mermaid-md-adoc"]
}
```

## How to use it?

Just put the code into fenced code block and tag it **mermaid** key word like this:

````text
```mermaid
graph
  A --> B;
  A --> C;
  B --> D;
  C --> D;
```
````
