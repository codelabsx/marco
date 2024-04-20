/*
这个函数用来生成一个ebpf指令
*/
void ebpf_emit(ebpf_t* e, struct bpf_insn insn) {
    *(e->ip)++ = insn;
}

/*
在寄存器列表中找到一个可以使用的寄存器
*/
reg_t* ebpf_reg_get(ebpf_t* e) {
    reg_t* r, *r_aged = NULL;
    //找到一个可以使用寄存器
}

/*
如果是比较大的数据比如字符串, 然后需要放到栈上面
*/
int ebpf_push(ebpf_t* e, ssize_t at, void* data, size_t size) {
    
    //首先将数据转换成为无符号32位的数据
    uint32_t* wdata = data;
    
    size_t left = size / sizeof(*wdata);

    //at表示偏移量, -5 + 5
    for (; left; left--, wdata++, at += sizeof(*wdata)) {
        //生成存储指令, 存储的寄存器,  存储的栈大小, 存储的数据,
        ebpf_emit(e, STW_IMM(BPF_REG_10, at, *wdata));
    }
}

/*
可以根据一个对象来查找到它对应的寄存器
如果当前对象是一个符号的话, 那么首先需要找到这个符号
*/
reg_t* ebpf_find(ebpf_t* e, node_t* n) {
    reg_t* r;
    if (n->type == TYPE_VAR) {
        //1. 首先找到这个符号对象
        sym = st_get(e->st, n->name);
    }

    //如果不是一个符号的话, 我们需要跟去reg中的对象来进行比较
    for (r = e->st->reg[BPF_REG_0]; r <= &e->st->reg[BPF_REG_9]; r++) {
        //比较e->st->reg[BPF_REG_0]中存储的寄存器中存储的对象是否和obj一样
        //这一点和函数返回值是一样的, 比如我们将R0与函数调用进行绑定
        if (r->type == type && r->obj == obj)
            return r;
    }

    return NULL;
}

/*
这个函数是用来bind寄存器和对应的node的
*/
reg_t* ebpf_bind(ebpf_t* e, reg_t* r, node_t* n) {
    //如果node是一个符号, 那么需要从符号表中把对象给取出来
    if (is_sym(n)) {
        
    } else {
        
    }
}

/*
将对应的值加载到对应的寄存器中
*/
int ebpf_reg_load(ebpf_t* e, reg_t* r, node_t* n) {
    if (n->type == TYPE_INT) {
        r->type = REG_NODE;
        r->n = n;
        ebpf_emit(e, MOV_IMM(r->reg, n->integer));
        return 0;
    }
}