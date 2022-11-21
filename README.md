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

### Window

> :warning: Only available on the main thread.

#### `const window = new Window(x, y, width, height)`

#### `window.app`

#### `window.x`

#### `window.y`

#### `window.width`

#### `window.height`

#### `window.closed`

#### `window.on('resize', width, height)`

#### `window.on('move', x, y)`

#### `window.on('close')`

## License

ISC
