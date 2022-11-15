{
  'targets': [{
    'target_name': 'libfx',
    'type': 'static_library',
    'sources': [],
    'configurations': {
      'Debug': {
        'defines': ['DEBUG'],
      },
      'Release': {
        'defines': ['NDEBUG'],
      },
    },
    'conditions': [
      ['OS=="mac"', {
        'sources': [
          './libfx/src/darwin/appkit/fx.m',
          './libfx/src/darwin/appkit/image.m',
          './libfx/src/darwin/appkit/node.m',
          './libfx/src/darwin/appkit/screen.m',
          './libfx/src/darwin/appkit/text.m',
          './libfx/src/darwin/appkit/text-input.m',
          './libfx/src/darwin/appkit/video.m',
          './libfx/src/darwin/appkit/view.m',
          './libfx/src/darwin/appkit/window.m',
        ],
      }],
    ],
  }]
}
