const b4a = require('b4a')
const EventEmitter = require('events')
const binding = require('../binding')

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

    process.once('exit', this._onexit.bind(this))
  }

  static _instance = null

  static shared () {
    if (this._instance === null) this._instance = new App()
    return this._instance
  }

  _onexit () {
    binding.fx_napi_destroy(this._handle)
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
    if (this.isMain) binding.fx_napi_run(this._handle)
  }

  terminate () {
    binding.fx_napi_terminate(this._handle)
  }

  dispatch (cb) {
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
