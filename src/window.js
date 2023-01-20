const b4a = require('b4a')
const EventEmitter = require('events')
const binding = require('../binding')

const App = require('./app')
const Node = require('./node')
const View = require('./view')

const constants = Node.constants

module.exports = class Window extends EventEmitter {
  constructor (x = 0, y = 0, width = 0, height = 0) {
    const app = App.shared()

    super()

    this._state = 0
    this._view = new View()

    this._handle = b4a.allocUnsafe(binding.sizeof_fx_napi_window_t)

    binding.fx_napi_window_init(app._handle, this._handle, this._view._handle, Float32Array.of(x, y, width, height), this,
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

  appendChild (child) {
    this._view.appendChild(child)
    return this
  }

  removeChild (child) {
    this._view.removeChild(child)
    return this
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

    this._view._onattach()

    this.emit('show')
  }

  hide () {
    if ((this._state & constants.STATE_VISIBLE) === 0) return
    this._state ^= constants.STATE_VISIBLE

    binding.fx_napi_hide_window(this._handle)

    this._view._ondetach()

    this.emit('hide')
  }

  destroy () {
    if (this._state & constants.STATE_DESTROYED) return
    this._state |= constants.STATE_DESTROYED

    this._view.destroy()

    if (this._state & constants.STATE_ATTACHED) {
      this._state ^= constants.STATE_ATTACHED
    }

    this._ondestroy()

    this.emit('destroy')
  }
}
