const EventEmitter = require('events')
const binding = require('../binding')

const constants = require('./constants')

module.exports = exports = class Node extends EventEmitter {
  constructor () {
    super()

    this._state = 0
    this._index = -1
    this._children = []
  }

  _ondestroy () {}

  _onattach () {
    this._state |= constants.STATE_ATTACHED

    this.emit('attach')

    for (const child of this._children) {
      if (child !== null) child._onattach()
    }
  }

  _ondetach () {
    this._state ^= constants.STATE_ATTACHED

    this.emit('detach')

    for (const child of this._children) {
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

    const index = this._children.length

    binding.fx_napi_set_child(this._handle, child._handle, index)

    child._index = index

    this._children.push(child)

    if (this._state & constants.STATE_ATTACHED) child._onattach()

    return this
  }

  removeChild (child) {
    if (child._index !== -1) return

    const index = child._index

    binding.fx_napi_unset_child(this._handle, child._handle, index)

    child._index = -1

    this._children[index] = null

    if (this._state & constants.STATE_ATTACHED) child._ondetach()

    return this
  }

  destroy () {
    if (this._state & constants.STATE_DESTROYED) return
    this._state |= constants.STATE_DESTROYED

    for (const child of this._children) {
      if (child !== null) child.destroy()
    }

    if (this._state & constants.STATE_ATTACHED) {
      this._state ^= constants.STATE_ATTACHED
    }

    this._ondestroy()

    this.emit('destroy')
  }
}
