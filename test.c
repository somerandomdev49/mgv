#include <stdio.h>
#include <math.h>
#include "mgv.h"

mgv_buffer_t* buffer;
mgv_pipeline_t* pipeline;
mgv_frame_t* frame;

float time_passed = 0.0f;
void update()
{
    fv4 c = { 0, 0, 0, 0 }; mgv_clear(c);
    mgv_draw_buffer(buffer);

    time_passed += 0.002f;
}

typedef struct { int idx; fv2 pos; } vertex_t;
vertex_t vertices[] = {
    { /* idx */ 0, /* pos */ { 0.0, -1.0} },
    { /* idx */ 1, /* pos */ {-0.5,  0.0} },
    { /* idx */ 2, /* pos */ {+0.5, +1.0} }
};

int shader_vert(fv4 out_pos, void* data, void* user, void* out)
{
    vertex_t* v = data;
    out_pos[0] = v->pos[0] * 0.5f + cos(time_passed + v->idx * 0.5f) * 0.25f;
    out_pos[1] = v->pos[1] * 0.5f + sin(time_passed + v->idx * 0.5f) * 0.25f;
    out_pos[2] = 0.0f;
    out_pos[3] = 1.0f;

    return true;
}

int shader_frag(fv4 out_col, void* data, void* user, void* out)
{
    out_col[0] = 1.0f;
    out_col[1] = 1.0f;
    out_col[2] = 1.0f;
    out_col[3] = 1.0f;

    return true;
}

int main()
{
    mgv_load();

    mgv_create_frame(&frame, 424, 240);
    mgv_bind_frame(frame);

    mgv_pipeline_shader_info_t shader_info = {
        .vertex_output_buffer_size = 0,
        .vertex_user_buffer_size = 0,
        .fragment_output_buffer_size = 0,
        .fragment_user_buffer_size = 0,
        .vertex_progam = &shader_vert,
        .fragment_program = &shader_frag
    };

    mgv_create_pipeline(&pipeline, &shader_info);
    mgv_bind_pipeline(pipeline);

    mgv_create_buffer(&buffer, sizeof(vertex_t) * 3, sizeof(vertex_t));
    mgv_load_buffer_data(buffer, 0, sizeof(vertex_t) * 3, vertices);

    mgv_start("test", &update);

    mgv_destroy_buffer(buffer);
    mgv_destroy_pipeline(pipeline);
    mgv_destroy_frame(frame);
    mgv_unload();
}
