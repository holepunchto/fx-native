const b4a = require('b4a')
const binding = require('../binding')

const App = require('./app')
const Node = require('./node')

module.exports = class Text extends Node {
  constructor (x = 0, y = 0, width = 0, height = 0) {
    const app = App.shared()

    super()

    this._handle = b4a.allocUnsafe(binding.sizeof_fx_napi_text_t)

    binding.fx_napi_text_init(app._handle, this._handle, Float32Array.of(x, y, width, height), this)
  }

  _ondestroy () {
    binding.fx_napi_text_destroy(this._handle)
  }

  appendChild (child) {
    if (typeof child === 'string') return this.appendSpan(child)

    return super.appendChild(child)
  }

  appendSpan (value) {
    Text.createSpan(value).appendTo(this)

    return this
  }

  setBounds (x, y, width, height) {
    binding.fx_napi_set_text_bounds(this._handle, Float32Array.of(x, y, width, height))
  }

  getBounds () {
    const result = new Float32Array(4)

    binding.fx_napi_get_text_bounds(this._handle, result)

    const [x, y, width, height] = result

    return {
      x,
      y,
      width,
      height
    }
  }

  getBoundsUsed () {
    const result = new Float32Array(4)

    binding.fx_napi_get_text_bounds_used(this._handle, result)

    const [x, y, width, height] = result

    return {
      x,
      y,
      width,
      height
    }
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
