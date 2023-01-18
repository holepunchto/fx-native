const b4a = require('b4a')
const binding = require('../binding')

const App = require('./app')
const Node = require('./node')

const constants = Node.constants

module.exports = class Window extends Node {
  constructor (x = 0, y = 0, width = 0, height = 0) {
    const app = App.shared()

    super()

    this._handle = b4a.allocUnsafe(binding.sizeof_fx_napi_window_t)

    binding.fx_napi_window_init(app._handle, this._handle, Float32Array.of(x, y, width, height), this,
      this._onresize,
      this._onmove,
      this._onclose
    )
  }

  _ondestroy () {
    binding.fx_napi_window_destroy(this._handle)
  }

  _onresize (width, height) {
    this.emit('resize', width, height)
  }

  _onmove (x, y) {
    this.emit('move', x, y)
  }

  _onclose () {
    if (this._state & constants.STATE_CLOSED) return
    this._state |= constants.STATE_CLOSED

    this.emit('close')
  }

  get visible () {
    return (this._state & constants.STATE_VISIBLE) !== 0
  }

  get closed () {
    return (this._state & constants.STATE_CLOSED) !== 0
  }

  getBounds () {
    const result = new Float32Array(4)

    binding.fx_napi_get_window_bounds(this._handle, result)

    const [x, y, width, height] = result

    return {
      x,
      y,
      width,
      height
    }
  }

  show () {
    if (this._state & constants.STATE_VISIBLE) return
    this._state |= constants.STATE_VISIBLE

    binding.fx_napi_show_window(this._handle)

    this._onattach()
  }

  hide () {
    if ((this._state & constants.STATE_VISIBLE) === 0) return
    this._state ^= constants.STATE_VISIBLE

    binding.fx_napi_hide_window(this._handle)

    this._ondetach()
  }
}
