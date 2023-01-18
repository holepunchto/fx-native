#ifndef FX_NATIVE_VIEW_H
#define FX_NATIVE_VIEW_H

#include <fx.h>
#include <napi-macros.h>
#include <node_api.h>
#include <stdlib.h>
#include <uv.h>

#include "app.h"

typedef struct {
  fx_view_t *view;

  napi_env env;
  napi_ref ctx;
} fx_napi_view_t;

NAPI_METHOD(fx_napi_view_init) {
  NAPI_ARGV(4)
  NAPI_ARGV_BUFFER_CAST(fx_napi_t *, app, 0)
  NAPI_ARGV_BUFFER_CAST(fx_napi_view_t *, view, 1)
  NAPI_ARGV_BUFFER_CAST(float *, bounds, 2)

  view->env = env;

  napi_create_reference(env, argv[3], 1, &view->ctx);

  float x = bounds[0];
  float y = bounds[1];
  float width = bounds[2];
  float height = bounds[3];

  fx_view_init(app->app, x, y, width, height, &view->view);

  fx_set_view_data(view->view, (void *) view);

  return NULL;
}

NAPI_METHOD(fx_napi_view_destroy) {
  NAPI_ARGV(1)
  NAPI_ARGV_BUFFER_CAST(fx_napi_view_t *, view, 0)

  fx_view_destroy(view->view);

  napi_delete_reference(env, view->ctx);

  return NULL;
}

NAPI_METHOD(fx_napi_get_view_bounds) {
  NAPI_ARGV(2)
  NAPI_ARGV_BUFFER_CAST(fx_napi_view_t *, view, 0)
  NAPI_ARGV_BUFFER_CAST(float *, bounds, 1)

  float *x = &bounds[0];
  float *y = &bounds[1];
  float *width = &bounds[2];
  float *height = &bounds[3];

  fx_get_view_bounds(view->view, x, y, width, height);

  return NULL;
}

NAPI_METHOD(fx_napi_set_view_bounds) {
  NAPI_ARGV(2)
  NAPI_ARGV_BUFFER_CAST(fx_napi_view_t *, view, 0)
  NAPI_ARGV_BUFFER_CAST(float *, bounds, 1)

  float x = bounds[0];
  float y = bounds[1];
  float width = bounds[2];
  float height = bounds[3];

  fx_set_view_bounds(view->view, x, y, width, height);

  return NULL;
}

#endif // FX_NATIVE_VIEW_H
