const EventEmitter = require('events')
const b4a = require('b4a')
const binding = require('../binding')

const constants = require('./constants')

function ondispatch () {
  this.resolve()
}

module.exports = class App extends EventEmitter {
  constructor () {
    super()

    this._state = 0

    this._handle = b4a.allocUnsafe(binding.sizeof_fx_napi_t)

    binding.fx_napi_init(this._handle, this,
      this._onlaunch,
      this._onterminate,
      this._onsuspend,
      this._onresume,
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
    this._state |= constants.STATE_RUNNING
    this.emit('launch')
  }

  _onterminate () {
    this._state ^= constants.STATE_RUNNING
    this.emit('terminate')
  }

  _onsuspend () {
    this._state |= constants.STATE_SUSPENDED
    this.emit('suspend')
  }

  _onresume () {
    this._state ^= constants.STATE_SUSPENDED
    this.emit('resume')
  }

  _onmessage (message) {
    this.emit('message', message)
  }

  get running () {
    return (this._state & constants.STATE_RUNNING) !== 0
  }

  get suspended () {
    return (this._state & constants.STATE_SUSPENDED) !== 0
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
