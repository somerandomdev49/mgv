#ifndef MIKE_VECMATH_H
#define MIKE_VECMATH_H

#ifndef MIKE_VECMATH_NO_STDBOOL
#  include <stdbool.h>
#  define MIKE_VECMATH_BOOL bool
#else
#  ifndef MIKE_VECMATH_BOOL
#    define MIKE_VECMATH_BOOL char
#  endif
#endif

// TODO?: allow complex types for `VAL`?

#ifndef MIKE_VECMATH_OWN_ABS
#  define MIKE_VECMATH_OWN_ABS(x) (x<<1)>>1
#endif

#define MIKE_VECMATH_V1_INIT_OPS(TYPE, VAL) \
    typedef VAL (*TYPE##_unop_t)(VAL); \
    static inline void TYPE##_nil(TYPE v) { v[0] = 0; } \
    static inline void TYPE##_cpy(TYPE dst, const TYPE src) { dst[0] = src[0]; } \
    static inline void TYPE##_val(TYPE dst, VAL x) { dst[0] = x; } \
    static inline void TYPE##_map(TYPE src, TYPE##_unop_t f) { src[0] = f(src[0]); } \
    static inline MIKE_VECMATH_BOOL TYPE##_eql(const TYPE a, const TYPE b) { return a[0] == b[0]; }

#define MIKE_VECMATH_V1_BASE_OPS(TYPE, VAL, FVAL) \
    static inline VAL clamp_##VAL(VAL v, VAL mn, VAL mx) { return v < mn ? mn : v > mx ? mx : v; } \
    static inline FVAL lerp_##VAL(VAL a, VAL b, FVAL t) { return a + (b - a) * t; } \
    static inline void TYPE##_clamp(TYPE dst, VAL mn, VAL mx){dst[0] = clamp_##VAL(dst[0],mn,mx);} \
    static inline void TYPE##_add_##TYPE(TYPE src, const TYPE v) { src[0] += v[0]; } \
    static inline void TYPE##_sub_##TYPE(TYPE src, const TYPE v) { src[0] -= v[0]; } \
    static inline void TYPE##_mul(TYPE src, const VAL v) { src[0] *= v; }

#define MIKE_VECMATH_V1_DUP_OPS(TYPE, VAL) \
    static inline void TYPE##_##TYPE##_sub_##TYPE(TYPE out, const TYPE src, const TYPE v) { TYPE##_cpy(out, src); TYPE##_sub_##TYPE(out, v); } \
    static inline void TYPE##_##TYPE##_mul(TYPE out, const TYPE src, const VAL v) { TYPE##_cpy(out, src); TYPE##_mul(out, v); }

#define MIKE_VECMATH_V1_COMMON_OPS(TYPE, VAL)




#define MIKE_VECMATH_V2_INIT_OPS(TYPE, VAL) \
    typedef VAL (*TYPE##_unop_t)(VAL); \
    static inline void TYPE##_nil(TYPE v) { v[0] = 0; v[1] = 0; } \
    static inline void TYPE##_cpy(TYPE dst, const TYPE src) { dst[0] = src[0]; dst[1] = src[1]; } \
    static inline void TYPE##_val(TYPE dst, VAL x, VAL y) { dst[0] = x; dst[1] = y; } \
    static inline void TYPE##_map(TYPE src, TYPE##_unop_t f) { src[0] = f(src[0]); src[1] = f(src[1]); } \
    static inline MIKE_VECMATH_BOOL TYPE##_eql(const TYPE a, const TYPE b) { return a[0] == b[0] && a[1] == b[1]; }

#define MIKE_VECMATH_V2_BASE_OPS(TYPE, VAL, TYPE1) \
    static inline void TYPE##_clamp(TYPE dst, VAL mn, VAL mx){TYPE1##_clamp(&dst[0],mn,mx);TYPE1##_clamp(&dst[1],mn,mx);} \
    static inline void TYPE##_add_##TYPE(TYPE src, const TYPE v) { src[0] += v[0]; src[1] += v[1]; } \
    static inline void TYPE##_sub_##TYPE(TYPE src, const TYPE v) { src[0] -= v[0]; src[1] -= v[1]; } \
    static inline void TYPE##_mul(TYPE src, const VAL v) { src[0] *= v; src[1] *= v; } \
    static inline void TYPE##_mul_##TYPE1(TYPE src, const TYPE1 v) { TYPE##_mul(src, v[0]); }

#define MIKE_VECMATH_V2_DUP_OPS(TYPE, VAL) \
    static inline void TYPE##_##TYPE##_sub_##TYPE(TYPE out, const TYPE src, const TYPE v) { TYPE##_cpy(out, src); TYPE##_sub_##TYPE(out, v); } \
    static inline void TYPE##_##TYPE##_mul(TYPE out, const TYPE src, const VAL v) { TYPE##_cpy(out, src); TYPE##_mul(out, v); }

#define MIKE_VECMATH_V2_COMMON_OPS(TYPE, VAL) \
    // static inline VAL TYPE##_dot_##TYPE(TYPE a, TYPE b) { return a[0] * b[0] + a[1] * b[1] + a[2] * b[2]; }




#define MIKE_VECMATH_V3_INIT_OPS(TYPE, VAL) \
    typedef VAL (*TYPE##_unop_t)(VAL); \
    static inline void TYPE##_nil(TYPE v) { v[0] = 0; v[1] = 0; v[2] = 0; } \
    static inline void TYPE##_cpy(TYPE dst, const TYPE src) { dst[0] = src[0]; dst[1] = src[1]; dst[2] = src[2]; } \
    static inline void TYPE##_val(TYPE dst, VAL x, VAL y, VAL z) { dst[0] = x; dst[1] = y; dst[2] = z; } \
    static inline void TYPE##_map(TYPE src, TYPE##_unop_t f) { src[0] = f(src[0]); src[1] = f(src[1]); src[2] = f(src[2]); } \
    static inline MIKE_VECMATH_BOOL TYPE##_eql(const TYPE a, const TYPE b) { return a[0] == b[0] && a[1] == b[1] && a[2] == b[2]; }

#define MIKE_VECMATH_V3_BASE_OPS(TYPE, VAL, TYPE2, TYPE1) \
    static inline void TYPE##_clamp(TYPE dst, VAL mn, VAL mx){TYPE2##_clamp(&dst[0],mn,mx);TYPE1##_clamp(&dst[2],mn,mx);} \
    static inline void TYPE##_add_##TYPE(TYPE src, const TYPE v) { src[0] += v[0]; src[1] += v[1]; src[2] += v[2]; } \
    static inline void TYPE##_sub_##TYPE(TYPE src, const TYPE v) { src[0] -= v[0]; src[1] -= v[1]; src[2] -= v[2]; } \
    static inline void TYPE##_mul(TYPE src, const VAL v) { src[0] *= v; src[1] *= v; src[2] *= v; } \
    static inline void TYPE##_mul_##TYPE1(TYPE src, const TYPE1 v) { TYPE##_mul(src, v[0]); }

#define MIKE_VECMATH_V3_DUP_OPS(TYPE, VAL) \
    static inline void TYPE##_##TYPE##_sub_##TYPE(TYPE out, const TYPE src, const TYPE v) { TYPE##_cpy(out, src); TYPE##_sub_##TYPE(out, v); } \
    static inline void TYPE##_##TYPE##_mul(TYPE out, const TYPE src, const VAL v) { TYPE##_cpy(out, src); TYPE##_mul(out, v); }

#define MIKE_VECMATH_V3_COMMON_OPS(TYPE, VAL) \
    static inline VAL TYPE##_dot_##TYPE(TYPE a, TYPE b) { return a[0] * b[0] + a[1] * b[1] + a[2] * b[2]; }



#define MIKE_VECMATH_V4_INIT_OPS(TYPE, VAL) \
    typedef VAL (*TYPE##_unop_t)(VAL); \
    static inline void TYPE##_nil(TYPE v) {v[0]=0;v[1]=0;v[2]=0;v[3]=0;} \
    static inline void TYPE##_cpy(TYPE dst, const TYPE src){dst[0]=src[0];dst[1]=src[1];dst[2]=src[2];dst[3]=src[3];} \
    static inline void TYPE##_val(TYPE dst, VAL x, VAL y, VAL z, VAL w) {dst[0]=x;dst[1]=y;dst[2]=z;dst[3]=w;} \
    static inline void TYPE##_map(TYPE src, TYPE##_unop_t f) {src[0]=f(src[0]);src[1]=f(src[1]);src[2]=f(src[2]);src[3]=f(src[3]);} \
    static inline MIKE_VECMATH_BOOL TYPE##_eql(const TYPE a, const TYPE b) {return a[0]==b[0]&&a[1]==b[1]&&a[2]==b[2]&&a[3]==b[3];}

#define MIKE_VECMATH_V4_BASE_OPS(TYPE, VAL, TYPE2, TYPE1) \
    static inline void TYPE##_clamp(TYPE dst, VAL mn, VAL mx){TYPE2##_clamp(&dst[0],mn,mx);TYPE2##_clamp(&dst[2],mn,mx);} \
    static inline void TYPE##_add_##TYPE(TYPE src, const TYPE v) {src[0]+=v[0];src[1]+=v[1];src[2]+=v[2];src[3]+=v[3];} \
    static inline void TYPE##_sub_##TYPE(TYPE src, const TYPE v) {src[0]-=v[0];src[1]-=v[1];src[2]-=v[2];src[3]-=v[3];} \
    static inline void TYPE##_mul(TYPE src, const VAL v) {src[0]*=v;src[1]*=v;src[2]*=v;src[3]*=v;} \
    static inline void TYPE##_mul_##TYPE1(TYPE src, const TYPE1 v) { TYPE##_mul(src, v[0]); }

#define MIKE_VECMATH_V4_DUP_OPS(TYPE, VAL) \
    static inline void TYPE##_##TYPE##_sub_##TYPE(TYPE out, const TYPE src, const TYPE v) { TYPE##_cpy(out, src); TYPE##_sub_##TYPE(out, v); } \
    static inline void TYPE##_##TYPE##_mul(TYPE out, const TYPE src, const VAL v) { TYPE##_cpy(out, src); TYPE##_mul(out, v); }

#define MIKE_VECMATH_V4_COMMON_OPS(TYPE, VAL)
    // static inline VAL TYPE##_dot_##TYPE(TYPE a, TYPE b) { return a[0] * b[0] + a[1] * b[1] + a[2] * b[2]; }



#define MIKE_VECMATH_DEFAULT_TYPES() \
    typedef int32_t i32; \
    typedef uint32_t u32; \
    typedef float fv1[1]; \
    typedef i32   iv1[1]; \
    typedef u32   uv1[1]; \
    typedef float fv2[2]; \
    typedef i32   iv2[2]; \
    typedef u32   uv2[2]; \
    typedef float fv3[3]; \
    typedef i32   iv3[3]; \
    typedef u32   uv3[3]; \
    typedef float fv4[4]; \
    typedef i32   iv4[4]; \
    typedef u32   uv4[4]; \
    \
    MIKE_VECMATH_V1_INIT_OPS(fv1, float) \
    MIKE_VECMATH_V1_BASE_OPS(fv1, float, float) \
    MIKE_VECMATH_V1_COMMON_OPS(fv1, float) \
    \
    MIKE_VECMATH_V2_INIT_OPS(fv2, float) \
    MIKE_VECMATH_V2_BASE_OPS(fv2, float, fv1) \
    MIKE_VECMATH_V2_DUP_OPS(fv2, float) \
    MIKE_VECMATH_V2_COMMON_OPS(fv2, float) \
    \
    MIKE_VECMATH_V3_INIT_OPS(fv3, float) \
    MIKE_VECMATH_V3_BASE_OPS(fv3, float, fv2, fv1) \
    MIKE_VECMATH_V3_DUP_OPS(fv3, float) \
    MIKE_VECMATH_V3_COMMON_OPS(fv3, float) \
    \
    MIKE_VECMATH_V4_INIT_OPS(fv4, float) \
    MIKE_VECMATH_V4_BASE_OPS(fv4, float, fv2, fv1) \
    MIKE_VECMATH_V4_DUP_OPS(fv4, float) \
    MIKE_VECMATH_V4_COMMON_OPS(fv4, float) \
    \
    \
    MIKE_VECMATH_V1_INIT_OPS(uv1, u32) \
    MIKE_VECMATH_V1_BASE_OPS(uv1, u32, float) \
    MIKE_VECMATH_V1_COMMON_OPS(uv1, u32) \
    \
    MIKE_VECMATH_V2_INIT_OPS(uv2, u32) \
    MIKE_VECMATH_V2_BASE_OPS(uv2, u32, uv1) \
    MIKE_VECMATH_V2_DUP_OPS(uv2, u32) \
    MIKE_VECMATH_V2_COMMON_OPS(uv2, u32) \
    \
    MIKE_VECMATH_V3_INIT_OPS(uv3, u32) \
    MIKE_VECMATH_V3_BASE_OPS(uv3, u32, uv2, uv1) \
    MIKE_VECMATH_V3_DUP_OPS(uv3, u32) \
    MIKE_VECMATH_V3_COMMON_OPS(uv3, u32) \
    \
    MIKE_VECMATH_V4_INIT_OPS(uv4, u32) \
    MIKE_VECMATH_V4_BASE_OPS(uv4, u32, uv2, uv1) \
    MIKE_VECMATH_V4_DUP_OPS(uv4, u32) \
    MIKE_VECMATH_V4_COMMON_OPS(uv4, u32) \
    \
    \
    MIKE_VECMATH_V1_INIT_OPS(iv1, i32) \
    MIKE_VECMATH_V1_BASE_OPS(iv1, i32, float) \
    MIKE_VECMATH_V1_COMMON_OPS(iv1, i32) \
    \
    MIKE_VECMATH_V2_INIT_OPS(iv2, i32) \
    MIKE_VECMATH_V2_BASE_OPS(iv2, i32, iv1) \
    MIKE_VECMATH_V2_DUP_OPS(iv2, i32) \
    MIKE_VECMATH_V2_COMMON_OPS(uv2, i32) \
    \
    MIKE_VECMATH_V3_INIT_OPS(iv3, i32) \
    MIKE_VECMATH_V3_BASE_OPS(iv3, i32, iv2, iv1) \
    MIKE_VECMATH_V3_DUP_OPS(iv3, i32) \
    MIKE_VECMATH_V3_COMMON_OPS(iv3, i32) \
    \
    MIKE_VECMATH_V4_INIT_OPS(iv4, i32) \
    MIKE_VECMATH_V4_BASE_OPS(iv4, i32, iv2, iv1) \
    MIKE_VECMATH_V4_DUP_OPS(iv4, i32) \
    MIKE_VECMATH_V4_COMMON_OPS(iv4, i32)

#endif // MIKE_VECMATH_H
