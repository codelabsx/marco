struct uv_loop_t {
    //基本处理对象
    uv_handle_t* t; 
    void* queue[2];

    //聚合所有阶段的对象
    void* prepare_handles[2];

    uv__io_watcher* watcher;

}