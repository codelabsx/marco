#define COLORS \
    X(Cred, "red") \
    X(Cblue, "blue") \
    X(Cgreen, "green") \


#define X(a, b) a,
    enum Color {COLORS};
#undef X



