const b4a = require('b4a')
const binding = require('../binding')

const Node = require('./node')

module.exports = class Window extends Node {
  constructor (x, y, width, height) {
    super()

    this.x = x
    this.y = y
    this.width = width
    this.height = height
    this.closed = false

    this._handle = b4a.allocUnsafe(binding.sizeof_fx_napi_window_t)

    binding.fx_napi_window_init(this.app._handle, this._handle, x, y, width, height, this,
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
