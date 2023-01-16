const b4a = require('b4a')
const binding = require('../binding')

const Node = require('./node')

module.exports = class Text extends Node {
  constructor (x = 0, y = 0, width = 0, height = 0) {
    super()

    this.x = x
    this.y = y
    this.width = width
    this.height = height

    this._handle = b4a.allocUnsafe(binding.sizeof_fx_napi_text_t)

    binding.fx_napi_text_init(this.app._handle, this._handle, x, y, width, height, this)
  }

  _ondestroy () {
    binding.fx_napi_text_destroy(this._handle)
  }

  setBounds (x, y, width, height) {
    this.x = x
    this.y = y
    this.width = width
    this.height = height

    binding.fx_napi_set_text_bounds(this._handle, x, y, width, height)
  }

  appendChild (child) {
    if (typeof child === 'string') return this.appendSpan(child)

    return super.appendChild(child)
  }

  appendSpan (value) {
    Text.createSpan(value).appendTo(this)

    return this
  }

  static createSpan (value) {
    return new TextSpan(value)
  }
}

class TextSpan {
  constructor (value) {
    this.value = value

    this._handle = b4a.allocUnsafe(binding.sizeof_fx_napi_text_span_t)
  }

  appendTo (text) {
    binding.fx_napi_append_text_span(text._handle, this._handle, this.value)
  }
}
