#include "cond.h"
#include <stdlib.h>
#include "../debugger/debugger.h"
#include "../debugger/warnings.h"

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