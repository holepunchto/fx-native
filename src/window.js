const b4a = require('b4a')
const binding = require('../binding')

const Node = require('./node')

module.exports = class Window extends Node {
  constructor (x = 0, y = 0, width = 0, height = 0) {
    super()

    this.x = x
    this.y = y
    this.width = width
    this.height = height
    this.attached = true
    this.closed = false

    this._handle = b4a.allocUnsafe(binding.sizeof_fx_napi_window_t)

    binding.fx_napi_window_init(this.app._handle, this._handle, x, y, width, height, this,
      this._onresize,
      this._onmove,
      this._onclose
    )
  }

  _ondestroy () {
    binding.fx_napi_window_destroy(this._handle)
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
