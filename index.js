const App = (exports.App = require('./lib/app'))

const app = App.shared()

if (app.isMain) {
  exports.Window = require('./lib/window')
  exports.View = require('./lib/view')
  exports.Text = require('./lib/text')
  exports.WebView = require('./lib/web-view')
}
