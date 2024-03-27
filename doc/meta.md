
C语言关于内存操作的元函数:
```c
sizeof
offsetof
memset(&queue, sizeof(queue), 0);

//元数据类型
uniptr_t
usize
```



C语言中我们如果做好抽象:

1. 使用宏去做一些基本的操作级别template抽象
    ```c
    //因为C语言中, 你是无法直接写出块操作的
    #define QUEUE_INSERT(H) do{\

    }while(0)\
    ```

    同时我们可以使用宏去做元操作, 比如: 代码中大量出现了关于队列的操作
    那我们完全可以将其抽象为一个宏

2. 可以使用指针去做关联对象关系, 指针可以关联的东西很多, 这里仅仅列举一些常见的, 但是容易忽略的
    -  我们可以通过指针去做一些callback操作, 比如 uv__io_cb, int fd
    -  我们定义了一个值之后, 我们为它建立起关联对象
    ```c
    struct A1{}; 
    struct A2{struct A1* a1}
    ```



3. 可以使用结构体去做一个抽象, 因为C语言是面向过程的编程语言, 
    - 所以我们直接构造与过程适配的数据结构就可以了
    - C语言也可以使用关联对象做聚合
    ```c
    struct B0{};
    struct B1{};
    struct B2{ 
        struct B1* b1;
        struct B0* b0;
    };

    //聚合函数, 
    //看到这个函数我们就知道, 
    void set_b(B0* b0; B2* B2) {
        B0->b0;
    }
    ```


4. 其次C语言是根植于linux的, 我们完全可以把linux看成是一个巨大的编程语言库来使用



```c
//在结构体中写一个队列
typedef struct queue_t_{void* queue[2]};

//在另外一个结构体中写一个队列
//这样我们可以通过queue->queue[2]插入到系统中的模块中的event_t的队列中
typedef struct event_t_{void* queue[2]};
```
