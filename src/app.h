#ifndef FX_NATIVE_APP_H
#define FX_NATIVE_APP_H

#include <fx.h>
#include <napi-macros.h>
#include <node_api.h>
#include <uv.h>

#include "shared.h"

typedef struct {
  fx_t *app;

  napi_env env;
  napi_ref ctx;

  napi_ref on_launch;
  napi_ref on_message;
} fx_napi_t;

typedef struct {
  fx_send_t req;

  napi_env env;
  napi_ref ctx;

  uv_buf_t message;

  napi_ref on_delivered;
} fx_napi_send_t;

static void
on_launch (fx_t *fx_app) {
  fx_napi_t *app;

  fx_get_data(fx_app, (void **) &app);

  napi_env env = app->env;

  FX_NAPI_CALLBACK(app, app->on_launch, {
    NAPI_MAKE_CALLBACK(env, NULL, ctx, callback, 0, NULL, NULL);
  })
}

static void
on_message (fx_t *fx_app, void *message, fx_t *sender) {
  fx_napi_t *app;

  fx_get_data(fx_app, (void **) &app);

  napi_env env = app->env;

  uv_buf_t *buf = (uv_buf_t *) message;

  FX_NAPI_CALLBACK(app, app->on_message, {
    napi_value argv[1];
    napi_create_buffer_copy(env, buf->len, buf->base, NULL, &argv[0]);
    NAPI_MAKE_CALLBACK(env, NULL, ctx, callback, 1, argv, NULL);
  })
}

NAPI_METHOD(fx_napi_init) {
  NAPI_ARGV(5)
  NAPI_ARGV_BUFFER_CAST(fx_napi_t *, app, 0)

  app->env = env;

  napi_create_reference(env, argv[1], 1, &app->ctx);
  napi_create_reference(env, argv[2], 1, &app->on_launch);
  napi_create_reference(env, argv[3], 1, &app->on_message);

  uv_loop_t *loop;
  napi_get_uv_event_loop(env, &loop);

  fx_init(loop, &app->app);

  fx_set_data(app->app, (void *) app);

  fx_on_launch(app->app, on_launch);
  fx_on_message(app->app, on_message);

  return NULL;
}

NAPI_METHOD(fx_napi_run) {
  NAPI_ARGV(1)
  NAPI_ARGV_BUFFER_CAST(fx_napi_t *, app, 0)

  fx_run(app->app);

  return NULL;
}

NAPI_METHOD(fx_napi_stop) {
  NAPI_ARGV(1)
  NAPI_ARGV_BUFFER_CAST(fx_napi_t *, app, 0)

  fx_stop(app->app);

  return NULL;
}

NAPI_METHOD(fx_napi_terminate) {
  NAPI_ARGV(1)
  NAPI_ARGV_BUFFER_CAST(fx_napi_t *, app, 0)

  fx_terminate(app->app);

  return NULL;
}

NAPI_METHOD(fx_napi_is_main) {
  NAPI_ARGV(1)
  NAPI_ARGV_BUFFER_CAST(fx_napi_t *, app, 0)

  NAPI_RETURN_UINT32(fx_is_main(app->app))
}

static void
on_delivered (fx_send_t *fx_req) {
  fx_napi_send_t *req = (fx_napi_send_t *) fx_req;

  napi_env env = req->env;

  FX_NAPI_CALLBACK(req, req->on_delivered, {
    NAPI_MAKE_CALLBACK(env, NULL, ctx, callback, 0, NULL, NULL);
  })

  napi_delete_reference(env, req->on_delivered);
  napi_delete_reference(env, req->ctx);
}

NAPI_METHOD(fx_napi_send) {
  NAPI_ARGV(5)
  NAPI_ARGV_BUFFER_CAST(fx_napi_t *, app, 0)
  NAPI_ARGV_BUFFER_CAST(fx_napi_send_t *, req, 1)
  NAPI_ARGV_BUFFER(message, 2)

  req->env = env;

  napi_create_reference(env, argv[3], 1, &req->ctx);
  napi_create_reference(env, argv[4], 1, &req->on_delivered);

  req->message = uv_buf_init(message, message_len);

  req->req.data = (void *) req;

  fx_send(app->app, &req->req, &req->message, on_delivered);

  return NULL;
}

#endif // FX_NATIVE_APP_H
