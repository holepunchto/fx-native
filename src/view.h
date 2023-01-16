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
  NAPI_ARGV(7)
  NAPI_ARGV_BUFFER_CAST(fx_napi_t *, app, 0)
  NAPI_ARGV_BUFFER_CAST(fx_napi_view_t *, view, 1)
  NAPI_ARGV_UINT32(x, 2)
  NAPI_ARGV_UINT32(y, 3)
  NAPI_ARGV_UINT32(width, 4)
  NAPI_ARGV_UINT32(height, 5)

  view->env = env;

  napi_create_reference(env, argv[6], 1, &view->ctx);

  fx_view_init(app->app, x, y, width, height, &view->view);

  fx_set_view_data(view->view, (void *) view);

  return NULL;
}

NAPI_METHOD(fx_napi_set_view_bounds) {
  NAPI_ARGV(5)
  NAPI_ARGV_BUFFER_CAST(fx_napi_view_t *, view, 0)
  NAPI_ARGV_UINT32(x, 1)
  NAPI_ARGV_UINT32(y, 2)
  NAPI_ARGV_UINT32(width, 3)
  NAPI_ARGV_UINT32(height, 4)

  fx_set_view_bounds(view->view, x, y, width, height);

  return NULL;
}

#endif // FX_NATIVE_VIEW_H
