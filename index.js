const App = exports.App = require('./src/app')

const app = App.shared()

if (app.isMain) {
  exports.Window = require('./src/window')
  exports.View = require('./src/view')
  exports.Text = require('./src/text')
  exports.WebView = require('./src/web-view')
}
