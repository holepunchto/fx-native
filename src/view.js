const b4a = require('b4a')
const binding = require('../binding')

const Node = require('./node')

module.exports = class View extends Node {
  constructor (x = 0, y = 0, width = 0, height = 0) {
    super()

    this.x = x
    this.y = y
    this.width = width
    this.height = height

    this._handle = b4a.allocUnsafe(binding.sizeof_fx_napi_view_t)

    binding.fx_napi_view_init(this.app._handle, this._handle, x, y, width, height, this)
  }

  _ondestroy () {
    binding.fx_napi_view_destroy(this._handle)
  }

  setBounds (x, y, width, height) {
    this.x = x
    this.y = y
    this.width = width
    this.height = height

    binding.fx_napi_set_view_bounds(this._handle, x, y, width, height)
  }
}
