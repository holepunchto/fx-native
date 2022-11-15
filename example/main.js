const { Worker } = require('worker_threads')
const { App, Window } = require('..')

const app = App.shared()

app
  .on('launch', () => new Worker(require.resolve('./background')))
  .on('message', () => {
    const window = new Window(0, 0, 500, 500)

    window
      .on('move', (x, y) => {
        console.log('move', x, y)
      })
      .on('resize', (width, height) => {
        console.log('resize', width, height)
      })
      .on('close', () => {
        app.stop()
      })
  })
  .run()
