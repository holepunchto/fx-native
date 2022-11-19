const { App } = require('..')

const app = App.shared()

app
  .on('message', (message) => {
    app.broadcast(message)
  })
  .broadcast('from background')
