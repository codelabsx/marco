int uv_run(uv_loop_t* loop, uv_run_mode mode) {
    int timeout;
    int r;
    int ren_padding;

    while (r != 0 && loop->stop_flag == 0) {
        //更新当前时间, 因为我们可能提交定时任务: setTimeout(() => {}, 1000);
        uv_update_time(loop);

        //执行定时器回调, ()=>{}
        uv_run_timers(loop);

        //执行padding
        uv_run_padding(loop);

        //执行队列
        uv_run_idle(loop);

        uv_run_prepare(loop);

        timeout = 0;

        //计算poll IO阻塞时间
        timeout = uv_backend_timeout(loop);

        //poll Io timeout是epoll_wait等待的时间
        uv__io_poll(loop, timeout);

        //继续执行各种队列
        uv_run_check(loop);
        uv_run_closing_handles(loop);

        //是否还有活跃任务, 有就继续
        r = uv__loop_alive(loop);
    }

}

static int uv__loop_alive(const uv_loop_t* loop) {
    return uv_has_active_handles(loop) || uv_has_active_reqs(loop) || loop->closing_handles != NULL;
}


void uv_run_idle(uv_loop_t* loop) {
    uv_prepare_t* h;
    QUEUE queue;
    QUEUE* q;

    //1. 首先将队列中的handles, 取下来放到队列中
    QUEUE_MOVE(&loop->idle_handles, &queue);

    //2. queue已经是将我们的handles给移进去了
    while (!QUEUE_EMPTY(&queue)) {
        //3.搞出队列的头
        q = QUEUE_HEAD(&queue);

        //4. 取得改节点对应整个结构体的基地址, 通过结构体成员取得结构体的首地址
        h = QUEUE_DATA(q, uv_idle_t, queue);

        QUEUE_REMOVE(q);

        //c
    }
}

int uv_idle_stop() {
    
}