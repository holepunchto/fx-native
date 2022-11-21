const App = exports.App = require('./src/app')

const app = App.shared()

if (app.isMain) {
  exports.Window = require('./src/window')
  exports.Text = require('./src/text')
}
