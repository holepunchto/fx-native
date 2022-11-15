#ifndef FX_NATIVE_SHARED_H
#define FX_NATIVE_SHARED_H

#include <node_api.h>

#define FX_NAPI_CALLBACK(self, fn, src) \
  { \
    napi_handle_scope scope; \
    napi_open_handle_scope(env, &scope); \
    napi_value ctx; \
    napi_get_reference_value(env, self->ctx, &ctx); \
    napi_value callback; \
    napi_get_reference_value(env, fn, &callback); \
    src; \
    napi_close_handle_scope(env, scope); \
  }

#endif // FX_NATIVE_SHARED_H
