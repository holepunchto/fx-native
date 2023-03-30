{
  'targets': [{
    'target_name': 'fx',
    'include_dirs': [
      '<!(node -e "require(\'napi-macros\')")',
      './vendor/libfx/include',
    ],
    'dependencies': [
      './vendor/libfx.gyp:libfx',
    ],
    'sources': [
      './binding.c',
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
        'libraries': [
          '-framework Foundation',
          '-framework AppKit',
          '-framework AVFoundation',
          '-framework AVKit',
          '-framework WebKit'
        ],
      }],
      ['OS=="win"', {
        'libraries': [
          '<(module_root_dir)/vendor/libfx/src/win32/webview2/<(target_arch)/WebView2LoaderStatic',
        ],
      }],
    ],
  }]
}
