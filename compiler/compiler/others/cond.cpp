#include <cstdlib>
#include "cond.hpp"
#include "../debugger/debugger.hpp"
#include "../debugger/warnings.hpp"

cond_type* cond_alloc() {
    cond_type* cond = (cond_type*)malloc(sizeof(cond_type));
    DBG_COND_ALLOC(cond);
    CHECK_COND(cond);
    return cond;
}

void cond_free(cond_type* cond) {
    DBG_COND_FREE(cond);
    free(cond);
}