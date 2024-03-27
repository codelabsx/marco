int uv__tcp_connect() {
    do{
        errno = 0;
        //非阻塞方式发起连接
        r = connect(uv__stram_fd(handle), addr, addrlen);
    } while(r == -1 && errno == ENTER);

    //连接失败或没有成功
    if (r == -1 && errno != 0) {
        if (errno == EINPROGRESS);
        else if (errno ==  ECONNREFUSED)
            handle->delayed_error = UV_ERR(ECONNREFUSED);
        else
            return UV_ERR(errno);
    }

    //产生padding任务
    if (handle->delayed_error) {
        uv_io_feed(handle->loop, &handle->io_watcher);
    }

    return 0;
}

void uv__io_feed(uv_loop_t* loop, uv__io_t* w) {
    if (QUEUE_EMPTY(&w->pending_queue)) {
        QUEUE_INSERT_TAIL(&loop->pending_queue, &w->pending_queue);
    }
} 