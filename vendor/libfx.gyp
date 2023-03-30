{
  'targets': [{
    'target_name': 'libfx',
    'type': 'static_library',
    'sources': [
      './libfx/src/shared/channel.c',
      './libfx/src/shared/fx.c',
    ],
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
          './libfx/src/darwin/fx.m',
          './libfx/src/darwin/image.m',
          './libfx/src/darwin/node.m',
          './libfx/src/darwin/screen.m',
          './libfx/src/darwin/scroll-view.m',
          './libfx/src/darwin/text.m',
          './libfx/src/darwin/text-input.m',
          './libfx/src/darwin/video.m',
          './libfx/src/darwin/view.m',
          './libfx/src/darwin/web-view.m',
          './libfx/src/darwin/window.m',
        ],
      }],
      ['OS=="win"', {
        'include_dirs': [
          './libfx/src/win32/webview2/include',
        ],
        'sources': [
          './libfx/src/win32/fx.cc',
          './libfx/src/win32/image.cc',
          './libfx/src/win32/node.cc',
          './libfx/src/win32/screen.cc',
          './libfx/src/win32/scroll-view.cc',
          './libfx/src/win32/text.cc',
          './libfx/src/win32/text-input.cc',
          './libfx/src/win32/video.cc',
          './libfx/src/win32/view.cc',
          './libfx/src/win32/web-view.cc',
          './libfx/src/win32/window.cc',
        ],
      }],
    ],
  }]
}
