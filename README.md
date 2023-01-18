# fx-native

https://github.com/holepunchto/libfx JavaScript bindings for Node.js.

```sh
npm install fx-native
```

## Usage

See [`example/`](example).

## API

### Application

#### `const app = App.shared()`

#### `app.running`

#### `app.isMain`

#### `app.isWorker`

#### `app.run()`

> :warning: Only has an effect on the main thread.

#### `app.terminate()`

#### `app.broadcast(buffer)`

#### `app.on('launch')`

#### `app.on('terminate')`

#### `app.on('message', buffer)`

### Node

#### `node.attached`

#### `node.destroyed`

#### `node.appendChild(child)`

#### `node.removeChild(child)`

#### `node.destroy()`

#### `node.on('attach')`

#### `node.on('detach')`

#### `node.on('destroy')`

### Window

Extends [`Node`](#node).

> :warning: Only available on the main thread.

#### `const window = new Window(x, y, width, height)`

#### `window.visible`

#### `window.closed`

#### `window.getBounds()`

#### `window.show()`

#### `window.hide()`

#### `window.on('resize', width, height)`

#### `window.on('move', x, y)`

#### `window.on('close')`

### View

Extends [`Node`](#node).

> :warning: Only available on the main thread.

#### `const view = new View(x, y, width, height)`

#### `view.getBounds()`

#### `view.setBounds(x, y, width, height)`

### Text

Extends [`Node`](#node).

> :warning: Only available on the main thread.

#### `const text = new Text(x, y, width, height)`

#### `text.getBounds()`

#### `text.getBoundsUsed()`

#### `text.setBounds(x, y, width, height)`

### Web View

Extends [`Node`](#node).

> :warning: Only available on the main thread.

#### `const webView = new WebView(x, y, width, height)`

#### `webView.getBounds()`

#### `webView.setBounds(x, y, width, height)`

#### `webView.postMessage(json)`

#### `webView.loadURL(url)`

#### `webView.loadHTML(html)`

#### `webView.on('message', json)`

## License

ISC
