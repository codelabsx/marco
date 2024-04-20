int uv_async_init(uv_loop_t* loop, uv_async_t* handle, uv_async_cb async_cb) {
    v__async_start(loop); 
}

int uv__async_start(uv_loop_t loop);