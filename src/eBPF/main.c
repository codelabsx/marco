#include <linux/bpf.h>

int bpf(int cmd, union bpf_attr* attr, unsigned int size);

enum cmd {
    BPF_MAP_CREATE,         //创建一个map, 返回一个文件描述符
    BPF_MAP_LOOKUP_ELEM,    //从map中找到对应的value
    BPF_MAP_UPDATE_ELEM,    //更新一个BPF
    BPF_MAP_DELETE_ELEM,
    BPF_MAP_GET_EXIT_KEY,
    BPF_PROG_LOAD,          //验证和加载eBPF程序, 返回一个新的文件描述符
};

//bpf_attr 是一个匿名的结构体 
union bpf_attr {
    struct {
        __u32 map_type;   
        __u32 key_size; 
        __u32 value_size;
        __u32 max_entries;
    };
    /* Used by BPF_MAP_*_ELEM and BPF_MAP_GET_NEXT_KEYcommands */
     struct {                          
        __u32  map_fd;
        __aligned_u64 key;
        union {
            __aligned_u64 value;
            __aligned_u64 next_key;
        };
        __u64  flags;
    };

    struct {
        __u32 prog_type;
        __u32 insn_cnt;
        __aligned_u64 insns;

    };


};