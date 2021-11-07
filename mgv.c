#include "mgv.h"
#include "mgv-rend.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

static mgv_frame_t* frame_;
static mgv_pipeline_t* pipeline_;

static SDL_PixelFormat* sdl_pixel_format_;

// TODO: move dput or whatever (cast_color_, change mgv_clear) to a separate file.
static uint32_t cast_color_(fv4 color)
{
    return SDL_MapRGBA(
        sdl_pixel_format_,
        color[0] * 255,
        color[1] * 255,
        color[2] * 255,
        color[3] * 255
    );
}

void mgv_clear(fv4 color)
{
    uint32_t col = cast_color_(color);
    for(uint32_t i = 0; i < frame_->width_ * frame_->height_; ++i)
    {
        frame_->pbuf_[i] = col;
        frame_->zbuf_[i] = INFINITY;
    }
}

void mgv_destroy_buffer(mgv_buffer_t* buf) { free(buf); }
void mgv_load_buffer_data(mgv_buffer_t* buf, size_t off, size_t sz, void* data) { memcpy((uint8_t*)buf->data_ + off, data, sz); }
void mgv_create_buffer(mgv_buffer_t** buf, size_t sz, size_t st)
{
    *buf = malloc(sizeof(mgv_buffer_t));
    (*buf)->data_ = NULL;
    (*buf)->size_ = sz;
    (*buf)->stride_ = st;
    (*buf)->data_ = malloc(sz);
}

void mgv_bind_pipeline(mgv_pipeline_t* pipeline) { pipeline_ = pipeline; }
void mgv_destroy_pipeline(mgv_pipeline_t* pl) { free(pl); }
void mgv_create_pipeline(mgv_pipeline_t** pl, mgv_pipeline_shader_info_t* si)
{
    *pl = malloc(sizeof(mgv_pipeline_t));
    (*pl)->frag_out_size_ = si->fragment_output_buffer_size;
    (*pl)->vert_out_size_ = si->vertex_output_buffer_size;
    (*pl)->frag_usr_size_ = si->fragment_user_buffer_size;
    (*pl)->vert_usr_size_ = si->vertex_user_buffer_size;
    (*pl)->frag_prog_ = si->fragment_program;
    (*pl)->vert_prog_ = si->vertex_progam;
    // TODO: allocate buffers.
}

void mgv_bind_frame(mgv_frame_t* f) { frame_ = f; }
void mgv_destroy_frame(mgv_frame_t* f) { free(f->pbuf_); free(f->zbuf_); free(f); }
void mgv_create_frame(mgv_frame_t** f, uint32_t width, uint32_t height)
{
    *f = malloc(sizeof(mgv_frame_t));
    (*f)->width_ = width;
    (*f)->height_ = height;
    (*f)->pbuf_ = malloc(width * height * sizeof(uint32_t));
    (*f)->zbuf_ = malloc(width * height * sizeof(float));
}

static mgv_render_color_val_t frag_color_func() {
    fv4 out;
    bool no_discard = pipeline_->frag_prog_(out, NULL, NULL, NULL);
    return (mgv_render_color_val_t){ 0xF8B3EAFF, !no_discard };
}

void mgv_draw_buffer(mgv_buffer_t* buf)
{
    uint32_t tri_count = buf->size_ / buf->stride_;

    iv2 tri[3];
    uint32_t tri_added = 0;
    for(uint32_t i = 0; i < tri_count; ++i)
    {
        fv4 out;
        pipeline_->vert_prog_(out, (uint8_t*)buf->data_ + buf->stride_ * i, NULL, NULL);
        tri[tri_added][0] = (out[0] * 0.5 + 0.5) * frame_->width_;
        tri[tri_added][1] = (out[1] * 0.5 + 0.5) * frame_->height_;
        ++tri_added;
        
        if(tri_added == 3)
        {
            mgv_rend_dtri(frame_, &frag_color_func, tri);
            tri_added = 0;
        }
    }
}

static void write_texture(SDL_Texture* texture) {
    uint8_t* texture_data;
    int texture_pitch;
    SDL_LockTexture(texture, NULL, (void**)&texture_data, &texture_pitch);

    for(uint32_t y = 0; y < frame_->height_; ++y)
    {
        uint32_t *ptr = (uint32_t*)(texture_data + texture_pitch * y);
        for(uint32_t x = 0; x < frame_->width_; ++x)
        {
            *ptr = frame_->pbuf_[y * frame_->width_ + x];
            ++ptr;
        }
    }

    SDL_UnlockTexture(texture);
}

void mgv_load()
{
    pipeline_ = NULL;
    frame_ = NULL;
}

void mgv_unload()
{
    pipeline_ = NULL;
    frame_ = NULL;
}

#define MGV_MULT 3
void mgv_start(const char* title, mgv_update_func_t update)
{
    SDL_Window* window = NULL;
    SDL_Texture* texture = NULL;
    SDL_Renderer* renderer = NULL;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) { printf("Failed to initialize: %s\n", SDL_GetError()); exit(1); }
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, frame_->width_*MGV_MULT, frame_->height_*MGV_MULT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, frame_->width_, frame_->height_);

    sdl_pixel_format_ = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);

    SDL_Event event;
    while(1)
    {
        SDL_PollEvent(&event);
        if(event.type == SDL_QUIT) break;

        update();
        write_texture(texture);

        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    free(sdl_pixel_format_);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
