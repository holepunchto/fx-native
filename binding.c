#include <napi-macros.h>

#include "src/app.h"
#include "src/window.h"

NAPI_INIT() {
  NAPI_EXPORT_SIZEOF(fx_napi_t)
  NAPI_EXPORT_SIZEOF(fx_napi_send_t)
  NAPI_EXPORT_SIZEOF(fx_napi_window_t)

  NAPI_EXPORT_FUNCTION(fx_napi_init)
  NAPI_EXPORT_FUNCTION(fx_napi_run)
  NAPI_EXPORT_FUNCTION(fx_napi_stop)
  NAPI_EXPORT_FUNCTION(fx_napi_terminate)
  NAPI_EXPORT_FUNCTION(fx_napi_is_main)
  NAPI_EXPORT_FUNCTION(fx_napi_send)

  NAPI_EXPORT_FUNCTION(fx_napi_window_init)
}
