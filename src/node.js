const EventEmitter = require('events')
const binding = require('../binding')

const App = require('./app')

module.exports = class Node extends EventEmitter {
  constructor () {
    const app = App.shared()

    super()

    this.app = app
    this.parent = null
    this.index = -1
    this.children = []
  }

  appendChild (child) {
    if (child.parent) return

    const index = this.children.length

    binding.fx_napi_set_child(this._handle, child._handle, index)

    child.index = index
    child.parent = this

    this.children.push(child)

    return this
  }

  removeChild (child) {
    if (child.parent !== this) return

    const index = child.index

    binding.fx_napi_unset_child(this._handle, child._handle, index)

    child.index = -1
    child.parent = null

    this.children[index] = null

    return this
  }
}
