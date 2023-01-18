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

typedef struct {
  fx_text_span_t *span;
} fx_napi_text_span_t;

NAPI_METHOD(fx_napi_text_init) {
  NAPI_ARGV(4)
  NAPI_ARGV_BUFFER_CAST(fx_napi_t *, app, 0)
  NAPI_ARGV_BUFFER_CAST(fx_napi_text_t *, text, 1)
  NAPI_ARGV_BUFFER_CAST(float *, bounds, 2)

  text->env = env;

  napi_create_reference(env, argv[3], 1, &text->ctx);

  float x = bounds[0];
  float y = bounds[1];
  float width = bounds[2];
  float height = bounds[3];

  fx_text_init(app->app, x, y, width, height, &text->text);

  fx_set_text_data(text->text, (void *) text);

  return NULL;
}

NAPI_METHOD(fx_napi_text_destroy) {
  NAPI_ARGV(1)
  NAPI_ARGV_BUFFER_CAST(fx_napi_text_t *, text, 0)

  fx_text_destroy(text->text);

  napi_delete_reference(env, text->ctx);

  return NULL;
}

NAPI_METHOD(fx_napi_get_text_bounds) {
  NAPI_ARGV(2)
  NAPI_ARGV_BUFFER_CAST(fx_napi_text_t *, text, 0)
  NAPI_ARGV_BUFFER_CAST(float *, bounds, 1)

  float *x = &bounds[0];
  float *y = &bounds[1];
  float *width = &bounds[2];
  float *height = &bounds[3];

  fx_get_text_bounds(text->text, x, y, width, height);

  return NULL;
}

NAPI_METHOD(fx_napi_get_text_bounds_used) {
  NAPI_ARGV(2)
  NAPI_ARGV_BUFFER_CAST(fx_napi_text_t *, text, 0)
  NAPI_ARGV_BUFFER_CAST(float *, bounds, 1)

  float *x = &bounds[0];
  float *y = &bounds[1];
  float *width = &bounds[2];
  float *height = &bounds[3];

  fx_get_text_bounds_used(text->text, x, y, width, height);

  return NULL;
}

NAPI_METHOD(fx_napi_set_text_bounds) {
  NAPI_ARGV(2)
  NAPI_ARGV_BUFFER_CAST(fx_napi_text_t *, text, 0)
  NAPI_ARGV_BUFFER_CAST(float *, bounds, 1)

  float x = bounds[0];
  float y = bounds[1];
  float width = bounds[2];
  float height = bounds[3];

  fx_set_text_bounds(text->text, x, y, width, height);

  return NULL;
}

NAPI_METHOD(fx_napi_append_text_span) {
  NAPI_ARGV(3)
  NAPI_ARGV_BUFFER_CAST(fx_napi_text_t *, text, 0)
  NAPI_ARGV_BUFFER_CAST(fx_napi_text_span_t *, span, 1)
  NAPI_ARGV_UTF8_MALLOC(value, 2)

  fx_append_text_span(text->text, value, value_len, &span->span);

  free(value);

  return NULL;
}

#endif // FX_NATIVE_TEXT_H
