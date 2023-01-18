const EventEmitter = require('events')
const binding = require('../binding')

module.exports = exports = class Node extends EventEmitter {
  constructor () {
    super()

    this._state = 0
    this._index = -1

    this.children = []

    this.once('destroy', this._ondestroy.bind(this))
  }

  _ondestroy () {}

  _onattach () {
    this._state |= constants.STATE_ATTACHED

    this.emit('attach')

    for (const child of this.children) {
      if (child !== null) child._onattach()
    }
  }

  _ondetach () {
    this._state ^= constants.STATE_ATTACHED

    this.emit('detach')

    for (const child of this.children) {
      if (child !== null) child._ondetach()
    }
  }

  get attached () {
    return (this._state & constants.STATE_ATTACHED) !== 0
  }

  get destroyed () {
    return (this._state & constants.STATE_ATTACHED) !== 0
  }

  appendChild (child) {
    if (child._index !== -1) return

    const index = this.children.length

    binding.fx_napi_set_child(this._handle, child._handle, index)

    child._index = index

    this.children.push(child)

    if (this._state & constants.STATE_ATTACHED) child._onattach()

    return this
  }

  removeChild (child) {
    if (child._index !== -1) return

    const index = child._index

    binding.fx_napi_unset_child(this._handle, child._handle, index)

    child._index = -1

    this.children[index] = null

    if (this._state & constants.STATE_ATTACHED) child._ondetach()

    return this
  }

  destroy () {
    if (this._state & constants.STATE_DESTROYED) return
    this._state |= constants.STATE_DESTROYED

    for (const child of this.children) {
      if (child !== null) child.destroy()
    }

    if (this._state & constants.STATE_ATTACHED) {
      this._state ^= constants.STATE_ATTACHED
    }

    this.emit('destroy')
  }
}

const constants = exports.constants = {
  STATE_ATTACHED: 0x1,
  STATE_DESTROYED: 0x2,
  STATE_VISIBLE: 0x4,
  STATE_CLOSED: 0x8
}
