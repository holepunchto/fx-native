#ifndef FX_NATIVE_WEB_VIEW_H
#define FX_NATIVE_WEB_VIEW_H

#include <fx.h>
#include <napi-macros.h>
#include <node_api.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>

#include "app.h"
#include "shared.h"

typedef struct {
  fx_web_view_t *web_view;

  napi_env env;
  napi_ref ctx;

  napi_ref on_ready;
  napi_ref on_message;
} fx_napi_web_view_t;

static void
on_web_view_ready (fx_web_view_t *fx_web_view, int status) {
  fx_napi_web_view_t *web_view;

  fx_get_web_view_data(fx_web_view, (void **) &web_view);

  napi_env env = web_view->env;

  FX_NAPI_CALLBACK(web_view, web_view->on_ready, {
    NAPI_MAKE_CALLBACK(env, NULL, ctx, callback, 0, NULL, NULL);
  })
}

static void
on_web_view_message (fx_web_view_t *fx_web_view, const char *message) {
  fx_napi_web_view_t *web_view;

  fx_get_web_view_data(fx_web_view, (void **) &web_view);

  napi_env env = web_view->env;

  FX_NAPI_CALLBACK(web_view, web_view->on_message, {
    napi_value argv[1];
    napi_create_string_utf8(env, message, strlen(message), &argv[0]);
    NAPI_MAKE_CALLBACK(env, NULL, ctx, callback, 1, argv, NULL);
  })
}

NAPI_METHOD(fx_napi_web_view_init) {
  NAPI_ARGV(7)
  NAPI_ARGV_BUFFER_CAST(fx_napi_t *, app, 0)
  NAPI_ARGV_BUFFER_CAST(fx_napi_web_view_t *, web_view, 1)
  NAPI_ARGV_UTF8_MALLOC(data_directory, 2)
  NAPI_ARGV_BUFFER_CAST(float *, bounds, 3)

  web_view->env = env;

  napi_create_reference(env, argv[4], 1, &web_view->ctx);
  napi_create_reference(env, argv[5], 1, &web_view->on_ready);
  napi_create_reference(env, argv[6], 1, &web_view->on_message);

  float x = bounds[0];
  float y = bounds[1];
  float width = bounds[2];
  float height = bounds[3];

  fx_web_view_init(app->app, data_directory, x, y, width, height, on_web_view_ready, &web_view->web_view);

  fx_set_web_view_data(web_view->web_view, (void *) web_view);

  fx_on_web_view_message(web_view->web_view, on_web_view_message);

  return NULL;
}

NAPI_METHOD(fx_napi_web_view_destroy) {
  NAPI_ARGV(1)
  NAPI_ARGV_BUFFER_CAST(fx_napi_web_view_t *, web_view, 0)

  fx_web_view_destroy(web_view->web_view);

  napi_delete_reference(env, web_view->on_ready);
  napi_delete_reference(env, web_view->on_message);
  napi_delete_reference(env, web_view->ctx);

  return NULL;
}

NAPI_METHOD(fx_napi_get_web_view_bounds) {
  NAPI_ARGV(2)
  NAPI_ARGV_BUFFER_CAST(fx_napi_web_view_t *, web_view, 0)
  NAPI_ARGV_BUFFER_CAST(float *, bounds, 1)

  float *x = &bounds[0];
  float *y = &bounds[1];
  float *width = &bounds[2];
  float *height = &bounds[3];

  fx_get_web_view_bounds(web_view->web_view, x, y, width, height);

  return NULL;
}

NAPI_METHOD(fx_napi_set_web_view_bounds) {
  NAPI_ARGV(2)
  NAPI_ARGV_BUFFER_CAST(fx_napi_web_view_t *, web_view, 0)
  NAPI_ARGV_BUFFER_CAST(float *, bounds, 1)

  float x = bounds[0];
  float y = bounds[1];
  float width = bounds[2];
  float height = bounds[3];

  fx_set_web_view_bounds(web_view->web_view, x, y, width, height);

  return NULL;
}

NAPI_METHOD(fx_napi_web_view_post_message) {
  NAPI_ARGV(2)
  NAPI_ARGV_BUFFER_CAST(fx_napi_web_view_t *, web_view, 0)
  NAPI_ARGV_UTF8_MALLOC(message, 1)

  fx_web_view_post_message(web_view->web_view, message);

  free(message);

  return NULL;
}

NAPI_METHOD(fx_napi_web_view_load_url) {
  NAPI_ARGV(2)
  NAPI_ARGV_BUFFER_CAST(fx_napi_web_view_t *, web_view, 0)
  NAPI_ARGV_UTF8_MALLOC(url, 1)

  fx_web_view_load_url(web_view->web_view, url, strlen(url));

  free(url);

  return NULL;
}

NAPI_METHOD(fx_napi_web_view_load_html) {
  NAPI_ARGV(2)
  NAPI_ARGV_BUFFER_CAST(fx_napi_web_view_t *, web_view, 0)
  NAPI_ARGV_UTF8_MALLOC(html, 1)

  fx_web_view_load_html(web_view->web_view, html, strlen(html));

  free(html);

  return NULL;
}

#endif // FX_NATIVE_WEB_VIEW_H
