#ifndef FX_NATIVE_NODE_H
#define FX_NATIVE_NODE_H

#include <fx.h>
#include <napi-macros.h>
#include <node_api.h>
#include <uv.h>

#include "app.h"

NAPI_METHOD(fx_napi_set_child) {
  NAPI_ARGV(3)
  NAPI_ARGV_BUFFER_CAST(fx_node_t **, parent, 0)
  NAPI_ARGV_BUFFER_CAST(fx_node_t **, child, 1)
  NAPI_ARGV_UINT32(index, 2)

  fx_set_child(*parent, *child, index);

  return NULL;
}

NAPI_METHOD(fx_napi_unset_child) {
  NAPI_ARGV(3)
  NAPI_ARGV_BUFFER_CAST(fx_node_t **, parent, 0)
  NAPI_ARGV_BUFFER_CAST(fx_node_t **, child, 1)
  NAPI_ARGV_UINT32(index, 2)

  fx_unset_child(*parent, *child, index);

  return NULL;
}

#endif // FX_NATIVE_TEXT_H
