const binding = require('../binding')
const b4a = require('b4a')
const EventEmitter = require('events')

function ondispatch () {
  this.resolve()
}

module.exports = class App extends EventEmitter {
  constructor () {
    super()

    this.running = false

    this._handle = b4a.allocUnsafe(binding.sizeof_fx_napi_t)

    binding.fx_napi_init(this._handle, this,
      this._onlaunch,
      this._onterminate,
      this._onmessage
    )

    this.isMain = binding.fx_napi_is_main(this._handle) !== 0
    this.isWorker = !this.isMain
  }

  static _instance = null

  static shared () {
    if (this._instance === null) this._instance = new App()
    return this._instance
  }

  _onlaunch () {
    this.running = true
    this.emit('launch')
  }

  _onterminate () {
    this.running = false
    this.emit('terminate')
  }

  _onmessage (message) {
    this.emit('message', message)
  }

  run () {
    if (!this.isMain) throw new Error('run() can only be called on main thread')

    binding.fx_napi_run(this._handle)
  }

  terminate () {
    if (!this.isMain) throw new Error('terminate() can only be called on main thread')

    binding.fx_napi_terminate(this._handle)
  }

  dispatch (cb) {
    if (!this.isMain) throw new Error('dispatch() can only be called on main thread')

    const req = b4a.allocUnsafe(binding.sizeof_fx_napi_dispatch_t)
    const ctx = {
      req,
      resolve: cb
    }

    binding.fx_napi_dispatch(req, ctx, ondispatch)
  }

  broadcast (message) {
    if (typeof message === 'string') message = b4a.from(message)

    binding.fx_napi_broadcast(this._handle, message)
  }
}
