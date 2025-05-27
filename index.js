exports.App = require('./lib/app')

const app = exports.App.shared()

if (app.isMain) {
  exports.Image = require('./lib/image')
  exports.Text = require('./lib/text')
  exports.View = require('./lib/view')
  exports.WebView = require('./lib/web-view')
  exports.Window = require('./lib/window')
}
