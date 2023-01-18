const b4a = require('b4a')
const binding = require('../binding')

const App = require('./app')
const Node = require('./node')

module.exports = class WebView extends Node {
  constructor (x = 0, y = 0, width = 0, height = 0) {
    const app = App.shared()

    super()

    this._handle = b4a.allocUnsafe(binding.sizeof_fx_napi_web_view_t)

    binding.fx_napi_web_view_init(app._handle, this._handle, Float32Array.of(x, y, width, height), this,
      this._onmessage
    )
  }

  _ondestroy () {
    binding.fx_napi_web_view_destroy(this._handle)
  }

  _onmessage (message) {
    this.emit('message', JSON.parse(message))
  }

  getBounds () {
    const result = new Float32Array(4)

    binding.fx_napi_get_web_view_bounds(this._handle, result)

    const [x, y, width, height] = result

    return {
      x,
      y,
      width,
      height
    }
  }

  setBounds (x, y, width, height) {
    binding.fx_napi_set_web_view_bounds(this._handle, Float32Array.of(x, y, width, height))
  }

  postMessage (message) {
    binding.fx_napi_web_view_post_message(this._handle, JSON.stringify(message))
  }

  loadURL (url) {
    binding.fx_napi_web_view_load_url(this._handle, url)
  }

  loadHTML (html) {
    binding.fx_napi_web_view_load_html(this._handle, html)
  }
}
