#ifndef FX_NATIVE_TEXT_H
#define FX_NATIVE_TEXT_H

#include <fx.h>
#include <napi-macros.h>
#include <node_api.h>
#include <stdlib.h>
#include <uv.h>

#include "app.h"

typedef struct {
  fx_text_t *text;

  napi_env env;
  napi_ref ctx;
} fx_napi_text_t;

NAPI_METHOD(fx_napi_text_init) {
  NAPI_ARGV(8)
  NAPI_ARGV_BUFFER_CAST(fx_napi_t *, app, 0)
  NAPI_ARGV_BUFFER_CAST(fx_napi_text_t *, text, 1)
  NAPI_ARGV_UTF8_MALLOC(value, 2)
  NAPI_ARGV_UINT32(x, 3)
  NAPI_ARGV_UINT32(y, 4)
  NAPI_ARGV_UINT32(width, 5)
  NAPI_ARGV_UINT32(height, 6)

  text->env = env;

  napi_create_reference(env, argv[7], 1, &text->ctx);

  fx_text_init(app->app, value, value_size, x, y, width, height, &text->text);

  fx_set_text_data(text->text, (void *) text);

  free(value);

  return NULL;
}

#endif // FX_NATIVE_TEXT_H
