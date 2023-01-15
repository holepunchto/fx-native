const b4a = require('b4a')
const binding = require('../binding')

const Node = require('./node')

module.exports = class WebView extends Node {
  constructor (x = 0, y = 0, width = 0, height = 0) {
    super()

    this.x = x
    this.y = y
    this.width = width
    this.height = height

    this._handle = b4a.allocUnsafe(binding.sizeof_fx_napi_web_view_t)

    binding.fx_napi_web_view_init(this.app._handle, this._handle, x, y, width, height, this,
      this._onmessage
    )
  }

  _onmessage (message) {
    this.emit('message', JSON.parse(message))
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
