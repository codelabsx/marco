#include <stdio.h>

typedef struct heap_t_ {
    void* value;
    heap_t* child;      //子节点
    heap_t* sibling;    //兄弟节点
} heap_t;


heap_t* meld(heap_t* x, heap_t* y) {
    if (x->value > y->value) {
        //交换两个值
        void* temp = x->value;
        x->value = y->value;
        y->value = temp;

        y->sibling = x->child;
        x->child = y;
    }
}


heap_t* merage(heap_t* x) {
    if (x == NULL || x->sibling == NULL) {
        return x;
    }

    heap_t* y = x->sibling; //x的兄弟节点
    heap_t* c = y->sibling; //x兄弟节点的兄弟节点

    x->sibling = y->sibling = NULL; //拆散

    return meld(merage(c), meld(x, y));
}



int main() {


    return 0;
}