const b4a = require('b4a')
const EventEmitter = require('events')
const binding = require('../binding')

const App = require('./app')

module.exports = class Window extends EventEmitter {
  constructor (x, y, width, height) {
    const app = App.shared()

    super()

    this.app = app
    this.x = x
    this.y = y
    this.width = width
    this.height = height
    this.closed = false

    this._handle = b4a.allocUnsafe(binding.sizeof_fx_napi_window_t)

    binding.fx_napi_window_init(app._handle, this._handle, x, y, width, height, this,
      this._onresize,
      this._onmove,
      this._onclose
    )
  }

  _onresize (width, height) {
    this.width = width
    this.height = height

    this.emit('resize', width, height)
  }

  _onmove (x, y) {
    this.x = x
    this.y = y

    this.emit('move', x, y)
  }

  _onclose () {
    if (this.closed) return

    this.closed = true
    this.emit('close')
  }
}
