const binding = require('../binding')
const b4a = require('b4a')
const EventEmitter = require('events')

function ondelivered () {
  this.resolve()
}

module.exports = class App extends EventEmitter {
  constructor () {
    super()

    this.running = false

    this._handle = b4a.allocUnsafe(binding.sizeof_fx_napi_t)

    binding.fx_napi_init(this._handle, this,
      this._onlaunch,
      this._onmessage
    )

    this.isMain = binding.fx_napi_is_main(this._handle) !== 0
  }

  static _instance = null

  static shared () {
    if (this._instance === null) this._instance = new App()
    return this._instance
  }

  _onlaunch () {
    this.emit('launch')
  }

  _onmessage (message) {
    this.emit('message', message)
  }

  run () {
    if (!this.isMain) throw new Error('run() can only be called on main thread')

    if (this.running) return
    this.running = true

    binding.fx_napi_run(this._handle)
  }

  stop () {
    if (!this.isMain) throw new Error('stop() can only be called on main thread')

    this.running = false

    binding.fx_napi_stop(this._handle)
  }

  terminate () {
    if (!this.isMain) throw new Error('terminate() can only be called on main thread')

    this.running = false

    binding.fx_napi_terminate(this._handle)
  }

  async send (message) {
    if (this.isMain) throw new Error('send() cannot be called on main thread')

    if (typeof message === 'string') message = b4a.from(message)

    const req = b4a.allocUnsafe(binding.sizeof_fx_napi_send_t)
    const ctx = {
      req,
      resolve: null
    }

    const promise = new Promise((resolve) => {
      ctx.resolve = resolve
    })

    binding.fx_napi_send(this._handle, req, message, ctx, ondelivered)

    return promise
  }
}
