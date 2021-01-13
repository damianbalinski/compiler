#define PARSE_TREE_DEPTH

#ifdef PARSE_TREE_DEPTH
    #define DEPTH_SIGN "  "
    #define DEPTH_INC() DEPTH++;
    #define DEPTH_DEC() DEPTH--;
    #define DEPTH_PRINT() for(int i=0; i<DEPTH; i++) cout << DEPTH_SIGN;
#else
    #define DEPTH_INC()
    #define DEPTH_DEC()
    #define DEPTH_PRINT()
#endif
