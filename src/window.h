#ifndef FX_NATIVE_WINDOW_H
#define FX_NATIVE_WINDOW_H

#include <fx.h>
#include <napi-macros.h>
#include <node_api.h>
#include <uv.h>

#include "app.h"
#include "shared.h"

typedef struct {
  fx_view_t *view;
  fx_window_t *window;

  napi_env env;
  napi_ref ctx;

  napi_ref on_resize;
  napi_ref on_move;
  napi_ref on_close;
} fx_napi_window_t;

static void
on_window_resize (fx_window_t *fx_window) {
  fx_napi_window_t *window;

  fx_get_window_data(fx_window, (void **) &window);

  napi_env env = window->env;

  float width, height;

  fx_get_window_bounds(window->window, NULL, NULL, &width, &height);

  FX_NAPI_CALLBACK(window, window->on_resize, {
    napi_value argv[2];
    napi_create_double(env, width, &argv[0]);
    napi_create_double(env, height, &argv[1]);
    NAPI_MAKE_CALLBACK(env, NULL, ctx, callback, 2, argv, NULL);
  })
}

static void
on_window_move (fx_window_t *fx_window) {
  fx_napi_window_t *window;

  fx_get_window_data(fx_window, (void **) &window);

  napi_env env = window->env;

  float x, y;

  fx_get_window_bounds(window->window, &x, &y, NULL, NULL);

  FX_NAPI_CALLBACK(window, window->on_move, {
    napi_value argv[2];
    napi_create_double(env, x, &argv[0]);
    napi_create_double(env, y, &argv[1]);
    NAPI_MAKE_CALLBACK(env, NULL, ctx, callback, 2, argv, NULL);
  })
}

static void
on_window_close (fx_window_t *fx_window) {
  fx_napi_window_t *window;

  fx_get_window_data(fx_window, (void **) &window);

  napi_env env = window->env;

  FX_NAPI_CALLBACK(window, window->on_close, {
    NAPI_MAKE_CALLBACK(env, NULL, ctx, callback, 0, NULL, NULL);
  })
}

NAPI_METHOD(fx_napi_window_init) {
  NAPI_ARGV(7)
  NAPI_ARGV_BUFFER_CAST(fx_napi_t *, app, 0)
  NAPI_ARGV_BUFFER_CAST(fx_napi_window_t *, window, 1)
  NAPI_ARGV_BUFFER_CAST(float *, bounds, 2)

  window->env = env;

  napi_create_reference(env, argv[3], 1, &window->ctx);
  napi_create_reference(env, argv[4], 1, &window->on_resize);
  napi_create_reference(env, argv[5], 1, &window->on_move);
  napi_create_reference(env, argv[6], 1, &window->on_close);

  float x = bounds[0];
  float y = bounds[1];
  float width = bounds[2];
  float height = bounds[3];

  fx_view_init(app->app, x, y, width, height, &window->view);

  fx_window_init(app->app, window->view, x, y, width, height, &window->window);

  fx_set_window_data(window->window, (void *) window);

  fx_on_window_resize(window->window, on_window_resize);
  fx_on_window_move(window->window, on_window_move);
  fx_on_window_close(window->window, on_window_close);

  return NULL;
}

NAPI_METHOD(fx_napi_window_destroy) {
  NAPI_ARGV(1)
  NAPI_ARGV_BUFFER_CAST(fx_napi_window_t *, window, 0)

  fx_window_destroy(window->window);

  napi_delete_reference(env, window->on_resize);
  napi_delete_reference(env, window->on_move);
  napi_delete_reference(env, window->on_close);
  napi_delete_reference(env, window->ctx);

  return NULL;
}

NAPI_METHOD(fx_napi_get_window_bounds) {
  NAPI_ARGV(2)
  NAPI_ARGV_BUFFER_CAST(fx_napi_window_t *, window, 0)
  NAPI_ARGV_BUFFER_CAST(float *, bounds, 1)

  float *x = &bounds[0];
  float *y = &bounds[1];
  float *width = &bounds[2];
  float *height = &bounds[3];

  fx_get_window_bounds(window->window, x, y, width, height);

  return NULL;
}

NAPI_METHOD(fx_napi_show_window) {
  NAPI_ARGV(1)
  NAPI_ARGV_BUFFER_CAST(fx_napi_window_t *, window, 0)

  fx_show_window(window->window);

  return NULL;
}

NAPI_METHOD(fx_napi_hide_window) {
  NAPI_ARGV(1)
  NAPI_ARGV_BUFFER_CAST(fx_napi_window_t *, window, 0)

  fx_hide_window(window->window);

  return NULL;
}

#endif // FX_NATIVE_WINDOW_H
