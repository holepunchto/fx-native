const b4a = require('b4a')
const binding = require('../binding')

const Node = require('./node')

module.exports = class Text extends Node {
  constructor (value, x, y, width, height) {
    super()

    this.value = value
    this.x = x
    this.y = y
    this.width = width
    this.height = height

    this._handle = b4a.allocUnsafe(binding.sizeof_fx_napi_text_t)

    binding.fx_napi_text_init(this.app._handle, this._handle, value, x, y, width, height, this)
  }
}
