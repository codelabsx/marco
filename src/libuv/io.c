struct uv__io_s {
    //事件触发之后回调
    uv__id_cb cb;

    //用于插入到底层队列
    void* pending_queue[2];
    void* watcher_queue[2];

    /*
    保存感兴趣的事件, 还没有同步到操作系统
    每次设置时首先保存事件在这个阶段, 

    然后Poll Io阶段再操作事件驱动模块更新到操作系统
    */
    unsigned int pevents;

    /*
    保存当前感兴趣的事件, 每次poll io阶段更新prevents的值
    到操作系统后就把
    */
    unsigned int events;

    /*
    标记对哪个文件描述符事件感兴趣
    */
    int fd;
};


void uv__io_init(uv__io_t* w, uv__io_cb, int fd) {
    QUEUE_INIT(&w->pending_queue); //初始化队列, 回调, 需要监听队列
    QUEUE_INIT(&w->watcher_queue); //初始化队列, 回调, 
    w->cb = cb;
    w->fd = fd;
    w->events = 0;
    w->pevents = 0;
}

/*
1. 设置对应的事件循环
2. 设置观察者对象
3. 设置事件的ID
*/

//设置对应的事件
void uv__in_start(uv_loop_t* loop, uv__io_t* w, unsigned int evnts) {
    //1. 首先设置感兴趣的事件, 但是还是没有同步到操作系统, 等到poll io阶段再去同步
    w->pevents |= events;

    //扩容loop->watchers, 如果需要的话
    maybe_resize(loop, w->fd + 1);

    //IO 观察者如果还没有插入队列, 则插入IO观察者队列, 等待Poll Io阶段的处理
    if (QUERY_EMPTY(&w->watcher->queue))
        QUERY_INSERT_TAIL(&loop->watcher_queue, &w->watcher_queue);

    //保存映射关系:
    if (loop->watchers[w->fd] == NULL) {
        loop->watchers[w->fd] == w;
        loop->nfds++;
    }
}

//注销对应的事件
void uv__io_stop(uv_loop_t* loop, uv__io_t* w, unsigned int events) {
    //首先清除不感兴趣的东西, 使用这个东西置0
    w->prevents &= ~events;

    if (w->pevents == 0) {
        //移除IO观察者队列
        QUEUE_REMOVE(&w->watcher_queue);
        QUEUE_INIT(&w->watcher_queue);
        w->events = 0;
    }
}

//关闭对应io_t
void uv__io_close(uv_loop_t* loop, uv__io_t* w) {
    //注销事件
    uv__io_stop(loop, w, POLLIN, | POLLOUT | UV__ROLLRDHUP | UV__POLLER);

    //移除pending队列, 
    QUEUE_REMOVE(&w->pending_queue);
}

/*
uv_platform_invalidate
*/
void uv__platform_invalidate_fd(uv_loop_t* loop, int fd) {
    struct epoll_event* events;
    struct epoll_event dummy;

    uniptr_t i;
}

//最后一层
int do_epoll_ctl(int epfd, int op, int fd, struct epoll_event) {
    //利用操作系统的一些
}