const path = require('path')
const { Worker } = require('worker_threads')
const { App, Window, WebView } = require('..')

const app = App.shared()

const window = new Window(0, 0, 500, 500)

window
  .on('move', (x, y) => {
    console.log('move', x, y)
  })
  .on('resize', (width, height) => {
    console.log('resize', width, height)

    webview.setBounds(0, 0, width, height)
  })
  .on('close', () => {
    console.log('close')

    app.terminate()
  })

const webview = new WebView(path.join(__dirname, 'webview'), 0, 0, 500, 500)

webview
  .on('ready', () => {
    webview.loadHTML(`
      <style>body { font-family: system-ui }</style>
      <p>Hello world!<p>
      <script>
      bridge.postMessage({ from: 'WebView' })
      </script>
    `)
  })
  .on('message', (message) => {
    console.log(message)
  })

window
  .appendChild(webview)
  .show()

app
  .on('launch', () => new Worker(require.resolve('./background')))
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
