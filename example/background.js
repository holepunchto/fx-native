const { App } = require('..')

const app = App.shared()

app.send(Buffer.from('hello world'))
