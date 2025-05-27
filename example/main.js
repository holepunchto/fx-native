const { Thread } = Bare
const { App, Window } = require('..')

const app = App.shared()

let window

app
  .on('launch', () => {
    window = new Window(0, 0, 500, 500)

    window
      .on('move', (x, y) => {
        console.log('move', x, y)
      })
      .on('resize', (width, height) => {
        console.log('resize', width, height)
      })
      .on('close', () => {
        console.log('close')
      })

    window.show()

    Thread.create(require.resolve('./background'))
  })
  .on('terminate', () => {
    console.log('terminate')

    window.destroy()
  })
  .once('message', (message) => {
    console.log(message.toString())

    app
      .once('message', (message) => {
        console.log(message.toString())
      })
      .broadcast('from main')
  })
  .run()
