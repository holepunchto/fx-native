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
  napi_ref on_terminate;
  napi_ref on_message;
} fx_napi_t;

typedef struct {
  napi_env env;
  napi_ref ctx;

  napi_ref on_dispatch;
} fx_napi_dispatch_t;

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
on_terminate (fx_t *fx_app) {
  fx_napi_t *app;

  fx_get_data(fx_app, (void **) &app);

  fx_read_stop(app->app);

  napi_env env = app->env;

  FX_NAPI_CALLBACK(app, app->on_terminate, {
    NAPI_MAKE_CALLBACK(env, NULL, ctx, callback, 0, NULL, NULL);
  })
}

static void
on_message (fx_t *receiver, const uv_buf_t *buf, fx_t *sender) {
  fx_napi_t *app;

  fx_get_data(receiver, (void **) &app);

  napi_env env = app->env;

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
  napi_create_reference(env, argv[3], 1, &app->on_terminate);
  napi_create_reference(env, argv[4], 1, &app->on_message);

  uv_loop_t *loop;
  napi_get_uv_event_loop(env, &loop);

  fx_init(loop, &app->app);

  fx_set_data(app->app, (void *) app);

  fx_on_launch(app->app, on_launch);
  fx_on_terminate(app->app, on_terminate);

  fx_read_start(app->app, on_message);

  return NULL;
}

NAPI_METHOD(fx_napi_destroy) {
  NAPI_ARGV(1)
  NAPI_ARGV_BUFFER_CAST(fx_napi_t *, app, 0)

  fx_destroy(app->app);

  napi_delete_reference(env, app->on_launch);
  napi_delete_reference(env, app->on_terminate);
  napi_delete_reference(env, app->on_message);
  napi_delete_reference(env, app->ctx);

  return NULL;
}

NAPI_METHOD(fx_napi_run) {
  NAPI_ARGV(1)
  NAPI_ARGV_BUFFER_CAST(fx_napi_t *, app, 0)

  fx_run(app->app);

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
on_dispatch (fx_t *fx_app, void *data) {
  fx_napi_dispatch_t *req = (fx_napi_dispatch_t *) data;

  napi_env env = req->env;

  FX_NAPI_CALLBACK(req, req->on_dispatch, {
    NAPI_MAKE_CALLBACK(env, NULL, ctx, callback, 0, NULL, NULL);
  })

  napi_delete_reference(env, req->on_dispatch);
  napi_delete_reference(env, req->ctx);
}

NAPI_METHOD(fx_napi_dispatch) {
  NAPI_ARGV(3)
  NAPI_ARGV_BUFFER_CAST(fx_napi_dispatch_t *, req, 0)

  req->env = env;

  napi_create_reference(env, argv[1], 1, &req->ctx);
  napi_create_reference(env, argv[2], 1, &req->on_dispatch);

  fx_dispatch(on_dispatch, (void *) req);

  return NULL;
}

NAPI_METHOD(fx_napi_broadcast) {
  NAPI_ARGV(2)
  NAPI_ARGV_BUFFER_CAST(fx_napi_t *, app, 0)
  NAPI_ARGV_BUFFER(message, 1)

  uv_buf_t buf = uv_buf_init(message, message_len);

  fx_broadcast(app->app, &buf);

  return NULL;
}

NAPI_METHOD(fx_napi_read_start) {
  NAPI_ARGV(1)
  NAPI_ARGV_BUFFER_CAST(fx_napi_t *, app, 0)

  return NULL;
}

#endif // FX_NATIVE_APP_H
