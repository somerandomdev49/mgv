#ifndef MGV_REND_H
#define MGV_REND_H
#include "mgv.h"
#include <stddef.h>
#include <stdbool.h>

typedef struct { uint32_t value; bool discard; } mgv_render_color_val_t;
typedef mgv_render_color_val_t (*mgv_rend_color_func_t)();

void mgv_rend_dline(
    mgv_frame_t* f,
    mgv_rend_color_func_t col,
    const iv2 a,
    const iv2 b
);

void mgv_rend_dtri(
    mgv_frame_t* f,
    mgv_rend_color_func_t col_func,
    iv2 tri[3]
);

#endif
