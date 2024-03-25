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
    //防止回调导致出现死循环
    QUEUE_MOVE(&loop->idle_handles, &queue);

    //2. queue已经是将我们的handles给移进去了
    while (!QUEUE_EMPTY(&queue)) {
        //3.搞出队列的头
        q = QUEUE_HEAD(&queue);

        //4. 取得改节点对应整个结构体的基地址, 通过结构体成员取得结构体的首地址
        h = QUEUE_DATA(q, uv_idle_t, queue);

        //5. 将这个节点从队列queue中移除
        QUEUE_REMOVE(q);

        //直接插入原来的队列
        QUEUE_INSERT_TAIL(&loop—>idle_handles, q);

        //执行回调函数
        h->idle_cb(h);
    }
}


int uv_idle_stop(uv_idle_t* handle) {
    if (!uv__is_active(handle)) return 0;

    //把handle从idle队列中移除, 但是还是挂载到handle_queue中
    QUEUE_REMOVE(&handle->queue);
    
    //将handle_stop
    uv__handle_stop(handle);

    return 0;
}

static int uv__run_pending(uv_loop_t* loop) {
    QUEUE* q;
    QUEUE pq;

    uv_io_t* w;
    
    if (QUEUE_EMPTY(&pq)) {return 0;}
    
    QUEUE_REMOVE(&loop->pending_queue, &pq);
    
    //遍历pq队列
    while (!QUEUE_EMPTY(&pq)) {
        //取出当前需要处理的节点移除队列
        q = QUEUE_HEAD(&pq);
        //将当前需要处理的节点移除队列
        QUEUE_REMOVE(q);

        //重置一下prev和next指针
        QUEUE_INIT(q);

        w = QUEUE_DATA(q, uv__io_t, pending_queue);

        //执行回调
        w->cb(loop, w, POLLOUT);
    }
}


void close(uv_handle_t* handle, uv_close_cb close_cb) {
    //正在关闭, 但是还没有执行回调
}