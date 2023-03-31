const path = require('path')
const b4a = require('b4a')
const binding = require('../binding')

const App = require('./app')
const Node = require('./node')

const constants = require('./constants')

module.exports = class WebView extends Node {
  constructor (dataDirectory = path.resolve('webview'), x = 0, y = 0, width = 0, height = 0) {
    const app = App.shared()

    super()

    this._handle = b4a.allocUnsafe(binding.sizeof_fx_napi_web_view_t)

    const bounds = Float32Array.of(x, y, width, height)

    binding.fx_napi_web_view_init(app._handle, this._handle, dataDirectory, bounds, this,
      this._onready,
      this._onmessage
    )
  }

  _onready () {
    this._state |= constants.STATE_READY
    this.emit('ready')
  }

  _ondestroy () {
    binding.fx_napi_web_view_destroy(this._handle)
  }

  _onmessage (message) {
    this.emit('message', JSON.parse(message))
  }

  get ready () {
    return (this._state & constants.STATE_READY) !== 0
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
    if (this.ready) binding.fx_napi_web_view_post_message(this._handle, JSON.stringify(message))
  }

  loadURL (url) {
    if (this.ready) binding.fx_napi_web_view_load_url(this._handle, url)
  }

  loadHTML (html) {
    if (this.ready) binding.fx_napi_web_view_load_html(this._handle, html)
  }
}
