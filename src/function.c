#if 0

#include <stdlib.h>
#include <string.h>
#include "function.h"
#include "globals.h"

struct object_s* evaluate(struct object_s *f) {
    struct object_s *tmp;
    uint32_t tref;
    switch (f->type) {
    case OBJ_ALI:
        return evaluate(f->detail.alias);
    case OBJ_FUN:
        if (f->detail.fun.args == 0) {
            tref = f->refs;
            tmp = f->detail.fun.fun(NULL);
        }
    }
    // what could go wrong?
    return f->fun(f->objs);
}
#endif

typedef int keep_compiler_happy;
