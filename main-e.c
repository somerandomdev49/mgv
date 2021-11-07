# 1 "main.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "main.c"







# 1 "vecmath.h" 1
# 9 "main.c" 2
typedef int32_t i32; typedef uint32_t u32; typedef float fv1[1]; typedef i32 iv1[1]; typedef u32 uv1[1]; typedef float fv2[2]; typedef i32 iv2[2]; typedef u32 uv2[2]; typedef float fv3[3]; typedef i32 iv3[3]; typedef u32 uv3[3]; typedef float (*fv1_unop_t)(float); static inline void fv1_nil(fv1 v) { v[0] = 0; } static inline void fv1_cpy(fv1 dst, const fv1 src) { dst[0] = src[0]; } static inline void fv1_val(fv1 dst, float x) { dst[0] = x; } static inline void fv1_map(fv1 src, fv1_unop_t f) { src[0] = f(src[0]); } static inline bool fv1_eql(const fv1 a, const fv1 b) { return a[0] == b[0]; }; static inline float clamp_float(float v, float mn, float mx) { return v < mn ? mn : v > mx ? mx : v; } static inline float lerp_float(float a, float b, float t) { return a + (b - a) * t; } static inline void fv1_clamp(fv1 dst, float mn, float mx){dst[0] = clamp_float(dst[0],mn,mx);} static inline void fv1_add_fv1(fv1 src, const fv1 v) { src[0] += v[0]; } static inline void fv1_sub_fv1(fv1 src, const fv1 v) { src[0] -= v[0]; } static inline void fv1_mul(fv1 src, const float v) { src[0] *= v; }; ; typedef float (*fv2_unop_t)(float); static inline void fv2_nil(fv2 v) { v[0] = 0; v[1] = 0; } static inline void fv2_cpy(fv2 dst, const fv2 src) { dst[0] = src[0]; dst[1] = src[1]; } static inline void fv2_val(fv2 dst, float x, float y) { dst[0] = x; dst[1] = y; } static inline void fv2_map(fv2 src, fv2_unop_t f) { src[0] = f(src[0]); src[1] = f(src[1]); } static inline bool fv2_eql(const fv2 a, const fv2 b) { return a[0] == b[0] && a[1] == b[1]; }; static inline void fv2_clamp(fv2 dst, float mn, float mx){fv1_clamp(&dst[0],mn,mx);fv1_clamp(&dst[1],mn,mx);} static inline void fv2_add_fv2(fv2 src, const fv2 v) { src[0] += v[0]; src[1] += v[1]; } static inline void fv2_sub_fv2(fv2 src, const fv2 v) { src[0] -= v[0]; src[1] -= v[1]; } static inline void fv2_mul(fv2 src, const float v) { src[0] *= v; src[1] *= v; } static inline void fv2_mul_fv1(fv2 src, const fv1 v) { fv2_mul(src, v[0]); }; static inline void fv2_fv2_sub_fv2(fv2 out, const fv2 src, const fv2 v) { fv2_cpy(out, src); fv2_sub_fv2(out, v); } static inline void fv2_fv2_mul(fv2 out, const fv2 src, const float v) { fv2_cpy(out, src); fv2_mul(out, v); } ; typedef float (*fv3_unop_t)(float); static inline void fv3_nil(fv3 v) { v[0] = 0; v[1] = 0; v[2] = 0; } static inline void fv3_cpy(fv3 dst, const fv3 src) { dst[0] = src[0]; dst[1] = src[1]; dst[2] = src[2]; } static inline void fv3_val(fv3 dst, float x, float y, float z) { dst[0] = x; dst[1] = y; dst[2] = z; } static inline void fv3_map(fv3 src, fv3_unop_t f) { src[0] = f(src[0]); src[1] = f(src[1]); src[2] = f(src[2]); } static inline bool fv3_eql(const fv3 a, const fv3 b) { return a[0] == b[0] && a[1] == b[1] && a[2] == b[2]; }; static inline void fv3_clamp(fv3 dst, float mn, float mx){fv2_clamp(&dst[0],mn,mx);fv1_clamp(&dst[2],mn,mx);} static inline void fv3_add_fv3(fv3 src, const fv3 v) { src[0] += v[0]; src[1] += v[1]; src[2] += v[2]; } static inline void fv3_sub_fv3(fv3 src, const fv3 v) { src[0] -= v[0]; src[1] -= v[1]; src[2] -= v[2]; } static inline void fv3_mul(fv3 src, const float v) { src[0] *= v; src[1] *= v; src[2] *= v; } static inline void fv3_mul_fv1(fv3 src, const fv1 v) { fv3_mul(src, v[0]); }; static inline void fv3_fv3_sub_fv3(fv3 out, const fv3 src, const fv3 v) { fv3_cpy(out, src); fv3_sub_fv3(out, v); } static inline void fv3_fv3_mul(fv3 out, const fv3 src, const float v) { fv3_cpy(out, src); fv3_mul(out, v); } static inline float fv3_dot_fv3(fv3 a, fv3 b) { return a[0] * b[0] + a[1] * b[1] + a[2] * b[2]; }; typedef u32 (*uv1_unop_t)(u32); static inline void uv1_nil(uv1 v) { v[0] = 0; } static inline void uv1_cpy(uv1 dst, const uv1 src) { dst[0] = src[0]; } static inline void uv1_val(uv1 dst, u32 x) { dst[0] = x; } static inline void uv1_map(uv1 src, uv1_unop_t f) { src[0] = f(src[0]); } static inline bool uv1_eql(const uv1 a, const uv1 b) { return a[0] == b[0]; }; static inline u32 clamp_u32(u32 v, u32 mn, u32 mx) { return v < mn ? mn : v > mx ? mx : v; } static inline float lerp_u32(u32 a, u32 b, float t) { return a + (b - a) * t; } static inline void uv1_clamp(uv1 dst, u32 mn, u32 mx){dst[0] = clamp_u32(dst[0],mn,mx);} static inline void uv1_add_uv1(uv1 src, const uv1 v) { src[0] += v[0]; } static inline void uv1_sub_uv1(uv1 src, const uv1 v) { src[0] -= v[0]; } static inline void uv1_mul(uv1 src, const u32 v) { src[0] *= v; }; ; typedef u32 (*uv2_unop_t)(u32); static inline void uv2_nil(uv2 v) { v[0] = 0; v[1] = 0; } static inline void uv2_cpy(uv2 dst, const uv2 src) { dst[0] = src[0]; dst[1] = src[1]; } static inline void uv2_val(uv2 dst, u32 x, u32 y) { dst[0] = x; dst[1] = y; } static inline void uv2_map(uv2 src, uv2_unop_t f) { src[0] = f(src[0]); src[1] = f(src[1]); } static inline bool uv2_eql(const uv2 a, const uv2 b) { return a[0] == b[0] && a[1] == b[1]; }; static inline void uv2_clamp(uv2 dst, u32 mn, u32 mx){uv1_clamp(&dst[0],mn,mx);uv1_clamp(&dst[1],mn,mx);} static inline void uv2_add_uv2(uv2 src, const uv2 v) { src[0] += v[0]; src[1] += v[1]; } static inline void uv2_sub_uv2(uv2 src, const uv2 v) { src[0] -= v[0]; src[1] -= v[1]; } static inline void uv2_mul(uv2 src, const u32 v) { src[0] *= v; src[1] *= v; } static inline void uv2_mul_uv1(uv2 src, const uv1 v) { uv2_mul(src, v[0]); }; static inline void uv2_uv2_sub_uv2(uv2 out, const uv2 src, const uv2 v) { uv2_cpy(out, src); uv2_sub_uv2(out, v); } static inline void uv2_uv2_mul(uv2 out, const uv2 src, const u32 v) { uv2_cpy(out, src); uv2_mul(out, v); } ; typedef u32 (*uv3_unop_t)(u32); static inline void uv3_nil(uv3 v) { v[0] = 0; v[1] = 0; v[2] = 0; } static inline void uv3_cpy(uv3 dst, const uv3 src) { dst[0] = src[0]; dst[1] = src[1]; dst[2] = src[2]; } static inline void uv3_val(uv3 dst, u32 x, u32 y, u32 z) { dst[0] = x; dst[1] = y; dst[2] = z; } static inline void uv3_map(uv3 src, uv3_unop_t f) { src[0] = f(src[0]); src[1] = f(src[1]); src[2] = f(src[2]); } static inline bool uv3_eql(const uv3 a, const uv3 b) { return a[0] == b[0] && a[1] == b[1] && a[2] == b[2]; }; static inline void uv3_clamp(uv3 dst, u32 mn, u32 mx){uv2_clamp(&dst[0],mn,mx);uv1_clamp(&dst[2],mn,mx);} static inline void uv3_add_uv3(uv3 src, const uv3 v) { src[0] += v[0]; src[1] += v[1]; src[2] += v[2]; } static inline void uv3_sub_uv3(uv3 src, const uv3 v) { src[0] -= v[0]; src[1] -= v[1]; src[2] -= v[2]; } static inline void uv3_mul(uv3 src, const u32 v) { src[0] *= v; src[1] *= v; src[2] *= v; } static inline void uv3_mul_uv1(uv3 src, const uv1 v) { uv3_mul(src, v[0]); }; static inline void uv3_uv3_sub_uv3(uv3 out, const uv3 src, const uv3 v) { uv3_cpy(out, src); uv3_sub_uv3(out, v); } static inline void uv3_uv3_mul(uv3 out, const uv3 src, const u32 v) { uv3_cpy(out, src); uv3_mul(out, v); } static inline u32 uv3_dot_uv3(uv3 a, uv3 b) { return a[0] * b[0] + a[1] * b[1] + a[2] * b[2]; }; typedef i32 (*iv1_unop_t)(i32); static inline void iv1_nil(iv1 v) { v[0] = 0; } static inline void iv1_cpy(iv1 dst, const iv1 src) { dst[0] = src[0]; } static inline void iv1_val(iv1 dst, i32 x) { dst[0] = x; } static inline void iv1_map(iv1 src, iv1_unop_t f) { src[0] = f(src[0]); } static inline bool iv1_eql(const iv1 a, const iv1 b) { return a[0] == b[0]; }; static inline i32 clamp_i32(i32 v, i32 mn, i32 mx) { return v < mn ? mn : v > mx ? mx : v; } static inline float lerp_i32(i32 a, i32 b, float t) { return a + (b - a) * t; } static inline void iv1_clamp(iv1 dst, i32 mn, i32 mx){dst[0] = clamp_i32(dst[0],mn,mx);} static inline void iv1_add_iv1(iv1 src, const iv1 v) { src[0] += v[0]; } static inline void iv1_sub_iv1(iv1 src, const iv1 v) { src[0] -= v[0]; } static inline void iv1_mul(iv1 src, const i32 v) { src[0] *= v; }; ; typedef i32 (*iv2_unop_t)(i32); static inline void iv2_nil(iv2 v) { v[0] = 0; v[1] = 0; } static inline void iv2_cpy(iv2 dst, const iv2 src) { dst[0] = src[0]; dst[1] = src[1]; } static inline void iv2_val(iv2 dst, i32 x, i32 y) { dst[0] = x; dst[1] = y; } static inline void iv2_map(iv2 src, iv2_unop_t f) { src[0] = f(src[0]); src[1] = f(src[1]); } static inline bool iv2_eql(const iv2 a, const iv2 b) { return a[0] == b[0] && a[1] == b[1]; }; static inline void iv2_clamp(iv2 dst, i32 mn, i32 mx){uv1_clamp(&dst[0],mn,mx);uv1_clamp(&dst[1],mn,mx);} static inline void iv2_add_iv2(iv2 src, const iv2 v) { src[0] += v[0]; src[1] += v[1]; } static inline void iv2_sub_iv2(iv2 src, const iv2 v) { src[0] -= v[0]; src[1] -= v[1]; } static inline void iv2_mul(iv2 src, const i32 v) { src[0] *= v; src[1] *= v; } static inline void iv2_mul_uv1(iv2 src, const uv1 v) { iv2_mul(src, v[0]); }; static inline void iv2_iv2_sub_iv2(iv2 out, const iv2 src, const iv2 v) { iv2_cpy(out, src); iv2_sub_iv2(out, v); } static inline void iv2_iv2_mul(iv2 out, const iv2 src, const i32 v) { iv2_cpy(out, src); iv2_mul(out, v); } ; typedef i32 (*iv3_unop_t)(i32); static inline void iv3_nil(iv3 v) { v[0] = 0; v[1] = 0; v[2] = 0; } static inline void iv3_cpy(iv3 dst, const iv3 src) { dst[0] = src[0]; dst[1] = src[1]; dst[2] = src[2]; } static inline void iv3_val(iv3 dst, i32 x, i32 y, i32 z) { dst[0] = x; dst[1] = y; dst[2] = z; } static inline void iv3_map(iv3 src, iv3_unop_t f) { src[0] = f(src[0]); src[1] = f(src[1]); src[2] = f(src[2]); } static inline bool iv3_eql(const iv3 a, const iv3 b) { return a[0] == b[0] && a[1] == b[1] && a[2] == b[2]; }; static inline void iv3_clamp(iv3 dst, i32 mn, i32 mx){iv2_clamp(&dst[0],mn,mx);iv1_clamp(&dst[2],mn,mx);} static inline void iv3_add_iv3(iv3 src, const iv3 v) { src[0] += v[0]; src[1] += v[1]; src[2] += v[2]; } static inline void iv3_sub_iv3(iv3 src, const iv3 v) { src[0] -= v[0]; src[1] -= v[1]; src[2] -= v[2]; } static inline void iv3_mul(iv3 src, const i32 v) { src[0] *= v; src[1] *= v; src[2] *= v; } static inline void iv3_mul_iv1(iv3 src, const iv1 v) { iv3_mul(src, v[0]); }; static inline void iv3_iv3_sub_iv3(iv3 out, const iv3 src, const iv3 v) { iv3_cpy(out, src); iv3_sub_iv3(out, v); } static inline void iv3_iv3_mul(iv3 out, const iv3 src, const i32 v) { iv3_cpy(out, src); iv3_mul(out, v); } static inline i32 uv3_dot_uv3(uv3 a, uv3 b) { return a[0] * b[0] + a[1] * b[1] + a[2] * b[2]; };

const uint32_t WIDTH = 150;
const uint32_t HEIGHT = 100;
const uint32_t WWIDTH = 3*WIDTH;
const uint32_t WHEIGHT = 3*HEIGHT;

void dput(uint32_t* pbuf, uint32_t col, const iv2 loc)
{
    if(loc[0] < 0 || loc[1] < 0 || loc[0] >= WIDTH || loc[1] >= HEIGHT) return;
    uint32_t i = loc[1] * WIDTH + loc[0];
    pbuf[i] = col;
}


void dline(uint32_t* pbuf, uint32_t col, const iv2 a, const iv2 b)
{
    iv2 delta; iv2_iv2_sub_iv2(delta, b, a); iv2_map(delta, abs);
    iv2 slope = { a[0] < b[0] ? 1 : -1, a[1] < b[1] ? 1 : -1 };

    u32 err = delta[0] + delta[1];
    iv2 cur; iv2_cpy(cur, a);
    do {
        dput(pbuf, col, cur);
        u32 err2 = err << 1;
        if(err2 >= delta[1]) { err += delta[1]; cur[0] += slope[0]; }
        if(err2 <= delta[0]) { err += delta[0]; cur[1] += slope[1]; }
    } while((!iv2_eql(cur, b)));
}

void zline(uint32_t* pbuf, float* zbuf, uint32_t col, uv3 a, uv3 b);

void write_texture(SDL_Texture* texture, SDL_PixelFormat *texture_format, uint32_t* data) {
    uint8_t* texture_data;
    int texture_pitch;
    SDL_LockTexture(texture, NULL, (void**)&texture_data, &texture_pitch);

    for(uint32_t y = 0; y < HEIGHT; ++y)
    {
        uint32_t *ptr = (uint32_t*)(texture_data + texture_pitch * y);
        for(uint32_t x = 0; x < WIDTH; ++x)
        {

            *ptr = data[y * WIDTH + x];



            ++ptr;
        }
    }

    SDL_UnlockTexture(texture);
}

int main(int argc, char *argv)
{
    SDL_Window* window = NULL;
    SDL_Texture* texture = NULL;
    SDL_Renderer* renderer = NULL;

    uint32_t* pixel_buffer = malloc(WIDTH * HEIGHT * 4);
    float* depth_buffer = malloc(WIDTH * HEIGHT * sizeof(float));

    memset(pixel_buffer, 0, WIDTH * HEIGHT * 4);
    for(uint32_t i = 0; i < WIDTH * HEIGHT; ++i) depth_buffer[i] = INFINITY;

    iv2 a, b; iv2_val(a, 0, 0); iv2_val(b, 100, 150);
    dline(pixel_buffer, 0xFE98A1FF, a, b);

    if(SDL_Init(SDL_INIT_VIDEO) < 0) { printf("Failed to initialize: %s\n", SDL_GetError()); exit(1); }
    window = SDL_CreateWindow("SHOWCASE-RAST", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WWIDTH, WHEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

    SDL_PixelFormat *texture_format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    write_texture(texture, texture_format, pixel_buffer);

    SDL_Event event;
    while(1)
    {
        SDL_PollEvent(&event);
        if(event.type == SDL_QUIT) break;

        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    free(texture_format);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    free(depth_buffer);
    free(pixel_buffer);
}
