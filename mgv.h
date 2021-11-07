#ifndef MGV_H
#define MGV_H
#include <stdint.h>
#include <stddef.h>

#include "vecmath.h"

#ifndef MIKE_VECMATH_DEFAULT_TYPES_CALLED
#define MIKE_VECMATH_DEFAULT_TYPES_CALLED
MIKE_VECMATH_DEFAULT_TYPES()
#endif

// immutable.
typedef struct
{
    uint32_t *pbuf_;
    float *zbuf_;
    uint32_t width_, height_;
} mgv_frame_t;

typedef struct
{
    uint32_t size_;
    uint32_t stride_;
    void* data_;
} mgv_buffer_t;

/**
 * dont_discard(bool) shader_program(                    -- if dont_discard == 0 then <fragment or vertex is discarded>;
 *     output_value[pos|color](xyzw|rgba),               -- if <is frag program> then must{output_value.any in [0;1]};
 *     input_buffer[vertbuf_data|vertprog_out](any*N),   -- true{N == <previous program's M>};
 *     user_buffer[?reserved?](any*),                    -- any{user_buffer};
 *     output_buffer[vertprog_out|?fragprog_out?](any*M) -- any{M}; tmp{if <is frag program> then true{M == 0}};
 * )
 **/
typedef int (*mgv_program_t)(fv4, void*, void*, void*);
typedef struct
{
    size_t vert_out_size_, frag_out_size_;
    size_t vert_usr_size_, frag_usr_size_;
    mgv_program_t vert_prog_, frag_prog_;
} mgv_pipeline_t;

typedef struct
{
    size_t vertex_output_buffer_size, fragment_user_buffer_size;
    size_t fragment_output_buffer_size, vertex_user_buffer_size;
    mgv_program_t vertex_progam, fragment_program;
} mgv_pipeline_shader_info_t;
void mgv_create_pipeline(mgv_pipeline_t** pipeline, mgv_pipeline_shader_info_t* info);
void mgv_destroy_pipeline(mgv_pipeline_t* pipeline);

typedef void (*mgv_update_func_t)();
void mgv_load();
void mgv_start(const char* title, mgv_update_func_t update);
void mgv_unload();

void mgv_create_buffer(mgv_buffer_t** buffer, size_t size, size_t stride);
void mgv_load_buffer_data(mgv_buffer_t* buffer, size_t offset, size_t size, void* data);
void mgv_destroy_buffer(mgv_buffer_t* buffer);

void mgv_create_frame(mgv_frame_t** frame, uint32_t width, uint32_t height);
void mgv_destroy_frame(mgv_frame_t* frame);

void mgv_clear(fv4 color);
void mgv_bind_frame(mgv_frame_t* frame);
void mgv_bind_pipeline(mgv_pipeline_t* pipeline);
void mgv_draw_buffer(mgv_buffer_t* buffer);
void mgv_set_frame(mgv_frame_t* frame);

#endif
