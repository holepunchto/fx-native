const b4a = require('b4a')
const binding = require('../binding')

const Node = require('./node')

module.exports = class Text extends Node {
  constructor (value = '', x = 0, y = 0, width = 0, height = 0) {
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
