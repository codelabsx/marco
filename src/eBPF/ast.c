const char* strs() {
    #define TYPE(_type) _type = _typestr,
        static const char* strs[] = {
            OP_TABLE
        };
    #undef TYPE
}

const char* loc_str(loc_t loc) {
    
}