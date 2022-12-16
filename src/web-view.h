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

  napi_ref on_message;
} fx_napi_web_view_t;

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
  NAPI_ARGV(8)
  NAPI_ARGV_BUFFER_CAST(fx_napi_t *, app, 0)
  NAPI_ARGV_BUFFER_CAST(fx_napi_web_view_t *, web_view, 1)
  NAPI_ARGV_UINT32(x, 2)
  NAPI_ARGV_UINT32(y, 3)
  NAPI_ARGV_UINT32(width, 4)
  NAPI_ARGV_UINT32(height, 5)

  web_view->env = env;

  napi_create_reference(env, argv[6], 1, &web_view->ctx);
  napi_create_reference(env, argv[7], 1, &web_view->on_message);

  fx_web_view_init(app->app, x, y, width, height, &web_view->web_view);

  fx_set_web_view_data(web_view->web_view, (void *) web_view);

  fx_on_web_view_message(web_view->web_view, on_web_view_message);

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
