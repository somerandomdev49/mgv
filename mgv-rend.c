#include "mgv.h"
#include "mgv-rend.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

static void dput(mgv_frame_t* f, uint32_t col, const iv2 loc)
{
    if(loc[0] < 0 || loc[1] < 0 || loc[0] >= f->width_ || loc[1] >= f->height_) return;
    uint32_t i = loc[1] * f->width_ + loc[0];
    f->pbuf_[i] = col;
}

// Bresenham line drawing algorithm implementation.
static void dline(
    mgv_frame_t* f,
    mgv_rend_color_func_t col_func,
    const iv2 a,
    const iv2 b
) {
    iv2 delta; iv2_iv2_sub_iv2(delta, b, a); iv2_map(delta, abs);
    delta[1] = -delta[1];
    iv2 slope = { a[0] < b[0] ? 1 : -1, a[1] < b[1] ? 1 : -1 };

    i32 err = delta[0] + delta[1];
    iv2 cur; iv2_cpy(cur, a);

    while(1)
    {
        mgv_render_color_val_t v = col_func(cur);
        if(!v.discard) dput(f, v.value, cur);
        if(cur[0] == b[0] && cur[1] == b[1]) break;

        i32 err2 = err << 1;
        if(err2 >= delta[1]) { err += delta[1]; cur[0] += slope[0]; }
        if(err2 <= delta[0]) { err += delta[0]; cur[1] += slope[1]; }
    }
}

static inline void swap_u8_(uint8_t* a, uint8_t* b)
{
    uint8_t t = *a;
    *a = *b;
    *b =  t;
}

static mgv_render_color_val_t debug_colorgen_(iv2 _) { return (mgv_render_color_val_t){ 0xFF0000FF, false }; }

static void dtri(
    mgv_frame_t* f,
    mgv_rend_color_func_t col_func,
    iv2 tri[3]
) {

    uint8_t ts0 = 0, ts1 = 1, ts2 = 2; // indices
    if(tri[0][1] > tri[1][1] || tri[0][0] > tri[1][0]) swap_u8_(&ts0, &ts1);
    if(tri[1][1] > tri[2][1] || tri[1][0] > tri[2][0]) swap_u8_(&ts1, &ts2);
    if(tri[0][1] > tri[1][1] || tri[0][0] > tri[1][0]) swap_u8_(&ts0, &ts1);

    i32 d1 = tri[ts1][1] - tri[ts0][1], d2 = tri[ts2][1] - tri[ts1][1];

    // bresenham algo's data for long line:
    iv2 Ldelta; iv2_iv2_sub_iv2(Ldelta, tri[ts0], tri[ts2]); iv2_map(Ldelta, abs);
    Ldelta[1] = -Ldelta[1];
    iv2 Lslope = { tri[ts0][0] < tri[ts2][0] ? 1 : -1, 1 };

    i32 Lerr = Ldelta[0] + Ldelta[1];
    iv2 Lcur; iv2_cpy(Lcur, tri[ts0]);

    // long side on the right.
    if(tri[ts1][0] < tri[ts0][0] || tri[ts1][0] < tri[ts2][0])
    {
        { // upper line.
            iv2 delta; iv2_iv2_sub_iv2(delta, tri[ts1], tri[ts0]); iv2_map(delta, abs);
            delta[1] = -delta[1];
            // iv2 slope = { a[0] < b[0] ? 1 : -1, a[1] < b[1] ? 1 : -1 };

            i32 err = delta[0] + delta[1];
            iv2 cur; iv2_cpy(cur, tri[ts0]);

            while(1)
            {
                for(i32 x = cur[0]; x < Lcur[0]; ++x)
                {
                    iv2 ccur = { x, Lcur[1] };
                    mgv_render_color_val_t v = col_func(ccur);
                    if(!v.discard) dput(f, v.value, ccur);
                }
                if(cur[0] == tri[ts1][0] && cur[1] == tri[ts1][1]) break;

                i32 err2 = err << 1;
                if(err2 >= delta[1]) { err += delta[1]; cur[0] -= 1; }
                if(err2 <= delta[0]) { err += delta[0]; cur[1] += 1; }

                err2 = Lerr << 1;
                if(err2 >= Ldelta[1]) { Lerr += Ldelta[1]; Lcur[0] += Lslope[0]; }
                if(err2 <= Ldelta[0]) { Lerr += Ldelta[0]; Lcur[1] += 1; }
            }
        }

        { // lower line.
            iv2 delta; iv2_iv2_sub_iv2(delta, tri[ts2], tri[ts1]); iv2_map(delta, abs);
            delta[1] = -delta[1];
            // iv2 slope = { a[0] < b[0] ? 1 : -1, a[1] < b[1] ? 1 : -1 };

            i32 err = delta[0] + delta[1];
            iv2 cur; iv2_cpy(cur, tri[ts1]);

            while(1)
            {
                for(i32 x = cur[0]; x < Lcur[0]; ++x)
                {
                    iv2 ccur; iv2_val(ccur, x, );
                    mgv_render_color_val_t v = col_func(ccur);
                    if(!v.discard) dput(f, v.value, ccur);
                }

                if(Lcur[0] == tri[ts2][0] && Lcur[1] == tri[ts2][1]) break;
                // if(cur[0] == tri[ts2][0] && cur[1] == tri[ts2][1]) break;

                i32 err2 = err << 1;
                if(err2 >= delta[1]) { err += delta[1]; cur[0] += 1; }
                if(err2 <= delta[0]) { err += delta[0]; cur[1] += 1; }

                i32 Lerr2 = Lerr << 1;
                if(Lerr2 >= Ldelta[1]) { Lerr += Ldelta[1]; Lcur[0] += Lslope[0]; }
                if(Lerr2 <= Ldelta[0]) { Lerr += Ldelta[0]; Lcur[1] += 1; }
            }
        }
    }
    dline(f, debug_colorgen_, tri[0], tri[1]);
    // dline(f, debug_colorgen_, tri[1], tri[2]);
    dline(f, debug_colorgen_, tri[2], tri[0]);
}

static void zline(uint32_t* pbuf, float* zbuf, uint32_t col, uv3 a, uv3 b) { }

void mgv_rend_dline(
    mgv_frame_t* f,
    mgv_rend_color_func_t col,
    const iv2 a,
    const iv2 b
) {
    // iv2 a2 = { a[0] + f->width_/2, a[1] + f->height_/2 };
    // iv2 b2 = { b[0] + f->width_/2, b[1] + f->height_/2 };
    dline(f, col, a, b);
}

void mgv_rend_dtri(
    mgv_frame_t* f,
    mgv_rend_color_func_t col_func,
    iv2 tri[3]
) {
    // iv2 tri2[3] = {
    //     { tri[0][0] + f->width_/2, tri[0][1] + f->height_/2 },
    //     { tri[1][0] + f->width_/2, tri[1][1] + f->height_/2 },
    //     { tri[2][0] + f->width_/2, tri[2][1] + f->height_/2 },
    // };

    dtri(f, col_func, tri);
}
