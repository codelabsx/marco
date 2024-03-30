//在ast中还引入了bpf.h
#include <lib/bpf.h>

//遍历node, 这个node是一个列表
#define node_foreach(_n, _in) for((_n) = (_in); (_n); (_n) = (_n)->next)

//操作定义参数是_type, 第二个参数是bpf_type, 第三个是类型的名称
#define OP(_type, _bpf_type, _typestr) _type = _bpf_type,


#define 

#define OP_TABLE				\
	OP(OP_OR,  BPF_OR,            "|" )	\
	OP(OP_XOR, BPF_XOR,           "^" )	\
	OP(OP_AND, BPF_AND,           "&" )	\
	OP(OP_EQ,  BPF_JEQ  | OP_JMP, "==")	\
	OP(OP_NE,  BPF_JNE  | OP_JMP, "!=")	\
	OP(OP_GE,  BPF_JSGE | OP_JMP, ">=")	\
	OP(OP_GT,  BPF_JSGT | OP_JMP, ">" )	\
	OP(OP_LSH, BPF_LSH,           "<<")	\
	OP(OP_RSH, BPF_RSH,           ">>")	\
	OP(OP_ADD, BPF_ADD,           "+" )	\
	OP(OP_SUB, BPF_SUB,           "-" )	\
	OP(OP_MUL, BPF_MUL,           "*" )	\
	OP(OP_DIV, BPF_DIV,           "/" )	\
	OP(OP_MOD, BPF_MOD,           "%" )

static inline const char *node_str(const node_t *node)
{
	static char buf[8];

	if (node->string)
		return node->string; //如果一个字符不为空, 那么就直接打印这个字符串

	snprintf(buf, sizeof(buf), "<%s>", type_str(node->type));
	return buf;
}



/*
op(OP_OR, BPF_OR, "|") -> OP_OR = BPF_OR

那么我们可以定义我们的op
if (OP == 1) {

}
*/
typedef enum op {
	OP_TABLE
} op_t;


typedef enum loc {
	LOC_NOWHERE,
	LOC_VIRTUAL,
	LOC_REG,    //
	LOC_STACK, //栈
} loc_t;


/*
unroll: UNROLL '(' INT ')' stmt
*/

typedef struct unroll {

} unroll_t;


typedef struct probe {
    node_t* pred;
    node_t* stmt;
} probe; //表示对应的探针


typdef struct call {
    char* module;
    int n_vargs;
    node_t* vargs;
} call_t;





typedef struct dyn {
    type_t type;
    size_t size;
    loc_t loc; //这个可能是程序的位置
    int reg; //这个是寄存器吗

};



typedef struct script {
    node_t* probes;
} script;


typedef struct node_t {
    union
    {
        script_t
    };
    
} node_t;



struct dyn {
	type_t type;
	size_t size;

	loc_t   loc;
	int     reg;
	ssize_t addr;

	union {
		struct {
			mdumper_t dump;
			cmper_t cmp;
		} map;

		struct {
			const func_t *func;
		} call;

		struct {
			struct bpf_insn *jmp;
		} iff;

		struct {
			struct bpf_insn *start;
		} unroll;

		struct {
			pvdr_t *pvdr;
			void   *pvdr_priv;

			ssize_t sp;
			int     dyn_regs;
			int     stat_regs;
		} probe;

		struct {
			symtable_t *st;
			evpipe_t   *evp;
		} script;
	};
};