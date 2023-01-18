#include <napi-macros.h>

#include "src/app.h"
#include "src/node.h"
#include "src/text.h"
#include "src/view.h"
#include "src/web-view.h"
#include "src/window.h"

NAPI_INIT() {
  NAPI_EXPORT_SIZEOF(fx_napi_t)
  NAPI_EXPORT_SIZEOF(fx_napi_dispatch_t)
  NAPI_EXPORT_SIZEOF(fx_napi_window_t)
  NAPI_EXPORT_SIZEOF(fx_napi_view_t)
  NAPI_EXPORT_SIZEOF(fx_napi_text_t)
  NAPI_EXPORT_SIZEOF(fx_napi_text_span_t)
  NAPI_EXPORT_SIZEOF(fx_napi_web_view_t)

  NAPI_EXPORT_FUNCTION(fx_napi_init)
  NAPI_EXPORT_FUNCTION(fx_napi_destroy)
  NAPI_EXPORT_FUNCTION(fx_napi_run)
  NAPI_EXPORT_FUNCTION(fx_napi_terminate)
  NAPI_EXPORT_FUNCTION(fx_napi_is_main)
  NAPI_EXPORT_FUNCTION(fx_napi_dispatch)
  NAPI_EXPORT_FUNCTION(fx_napi_broadcast)

  NAPI_EXPORT_FUNCTION(fx_napi_set_child)
  NAPI_EXPORT_FUNCTION(fx_napi_unset_child)

  NAPI_EXPORT_FUNCTION(fx_napi_window_init)
  NAPI_EXPORT_FUNCTION(fx_napi_window_destroy)
  NAPI_EXPORT_FUNCTION(fx_napi_get_window_bounds)
  NAPI_EXPORT_FUNCTION(fx_napi_show_window)
  NAPI_EXPORT_FUNCTION(fx_napi_hide_window)

  NAPI_EXPORT_FUNCTION(fx_napi_view_init)
  NAPI_EXPORT_FUNCTION(fx_napi_view_destroy)
  NAPI_EXPORT_FUNCTION(fx_napi_get_view_bounds)
  NAPI_EXPORT_FUNCTION(fx_napi_set_view_bounds)

  NAPI_EXPORT_FUNCTION(fx_napi_text_init)
  NAPI_EXPORT_FUNCTION(fx_napi_text_destroy)
  NAPI_EXPORT_FUNCTION(fx_napi_get_text_bounds)
  NAPI_EXPORT_FUNCTION(fx_napi_get_text_bounds_used)
  NAPI_EXPORT_FUNCTION(fx_napi_set_text_bounds)
  NAPI_EXPORT_FUNCTION(fx_napi_append_text_span)

  NAPI_EXPORT_FUNCTION(fx_napi_web_view_init)
  NAPI_EXPORT_FUNCTION(fx_napi_web_view_destroy)
  NAPI_EXPORT_FUNCTION(fx_napi_get_web_view_bounds)
  NAPI_EXPORT_FUNCTION(fx_napi_set_web_view_bounds)
  NAPI_EXPORT_FUNCTION(fx_napi_web_view_post_message)
  NAPI_EXPORT_FUNCTION(fx_napi_web_view_load_url)
  NAPI_EXPORT_FUNCTION(fx_napi_web_view_load_html)
}
