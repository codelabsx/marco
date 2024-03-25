/*
libuv的handle有ref和active两个状态, 当一个handle调用xxx_init函数的时候
*/


//libuv初始化操作
#define uv_handle_init(loop_, h, type_)
    do{
        (h) -> loop = (loop_); 
        (h) -> type = (type_);
        (h) -> flags = UV_HANDLE_REF;
        QUEUE_INSERT_TAIL(&(loop_)->handle_queue, &(h)->handle_queue); //插入到队列的尾部
    }
    while(0)


#define uv__handle_start(h)           
    do {                           
        if (((h)->flags & UV_HANDLE_ACTIVE) != 0) break;        //1 & 1 = 1, 1!=0 表示当前状态为active           
        (h)->flags |= UV_HANDLE_ACTIVE;                         //置1操作, 将原来的位设置成1, 设置成为active
        if (((h)->flags & UV_HANDLE_REF) != 0)                  //1 & 1 = 1, 
            (h)->loop->active_handles++;                        //将活跃的handle数量加1
    }                             
    while (0)


#define uv__handle_stop(h)           
  do {                         
    if (((h)->flags & UV_HANDLE_ACTIVE) == 0) break;         //0 & 1, 直接返回
    (h)->flags &= ~UV_HANDLE_ACTIVE;                         //& =~ 将原来的active变成ref
    if (((h)->flags & UV_HANDLE_REF) != 0) uv__active_handle_rm(h);  //1 & 1, 移除活跃的handle
  }                              
  while (0)  


#define uv__handle_ref(h)
    do {
        if ((h)->flags & UV_HANDLE_REF == 0) break;
        (h)->flags |= UV_HANDLE_ACTIVE;                         //置1操作, 将原来的ref变成0
        if (((h)->flags & UV_HANDLE_CLOSING) != 0) break;       //如果已经是close了
        if (((h)->flags & UV_HANDLE_ACTIVE) != 0) uv__active_handle_rm(h); 
    }
    while(0)


#define uv__req_init(loop, req, typ)
    do{
        (req)->type = (typ);                                   //类型
        (loop)->active_reqs.count++;                           //表示请求加1
    }
    while (0)

#define uv__req_unregister(loop, req)
    do{
        (loop)->active_reqs.count--;
    }
    while(0);