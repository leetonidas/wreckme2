#include "factory.h"
#include "function.h"
#include <stdlib.h>
#include <stdarg.h>

struct object_s *new_base() {
    struct object_s *ret = calloc(1, sizeof(struct object_s));
    ret->refs = 0;
    return ret;
}

struct object_s *new_fun(struct object_s *(*fun)(struct object_s **), uint32_t num_args) {
    struct object_s *ret = new_base();
    ret->type = OBJ_FUN;
    ret->detail.fun.fun = fun;
    ret->detail.fun.args = num_args;
    return ret;
}

struct object_s *new_unsigned(uint32_t val) {
    struct object_s *ret = new_base();
    ret->type = OBJ_VAL;
    ret->detail.val.type = VAL_UNSIGNED;
    ret->detail.val.detail.uns = val;
    return ret;
}

struct object_s *new_signed(int32_t val) {
    struct object_s *ret = new_base();
    ret->type = OBJ_VAL;
    ret->detail.val.type = VAL_SIGNED;
    ret->detail.val.detail.sig = val;
    return ret;
}

struct object_s *new_char(char val) {
    struct object_s *ret = new_base();
    ret->type = OBJ_VAL;
    ret->detail.val.type = VAL_CHAR;
    ret->detail.val.detail.chr = val;
    return ret;
}

struct object_s *new_byte(uint8_t val) {
    struct object_s *ret = new_base();
    ret->type = OBJ_VAL;
    ret->detail.val.type = VAL_BYTE;
    ret->detail.val.detail.byte = val;
    return ret;
}

struct object_s *new_bool(int val) {
    struct object_s *ret = new_base();
    ret->type = OBJ_VAL;
    ret->detail.val.type = VAL_BOOL;
    ret->detail.val.detail.bool = val;
    return ret;
}

struct object_s *new_ptr(void *val) {
    struct object_s *ret = new_base();
    ret->type = OBJ_VAL;
    ret->detail.val.type = VAL_PTR;
    ret->detail.val.detail.ptr = val;
    return ret;
}

struct object_s *new_constucted(enum constr cst, uint32_t num) {
    struct object_s *ret = new_base();
    ret->type = OBJ_VAL;
    ret->detail.val.type = VAL_CONSTRUCT;
    ret->detail.val.detail.con.c = cst;
    ret->detail.val.detail.con.num = 0;
    ret->detail.val.detail.con.objs = calloc(num, sizeof(struct object_s *));
    return ret;
}

void apply_constructed(struct object_s *restrict tar, uint32_t num, ...) {
    va_list al;
    va_start(al, num);
    uint32_t offset = tar->detail.val.detail.con.num;
    for (uint32_t i = 0; i < num; i++) {
        tar->detail.val.detail.con.objs[offset + i] =
            copy(va_arg(al, struct object_s *));
    }
    tar->detail.val.detail.con.num = offset + num;
}

struct object_s *apply_function(struct object_s *restrict tar, uint32_t num, ...) {
    
    struct object_s **args = calloc(num, sizeof(struct object_s *));
    struct object_s *ret;
    
    va_list al;
    va_start(al, num);
    for (uint32_t i = 0; i < num; i++) {
        args[i] = va_arg(al, struct object_s *);
    }
    va_end(al);

    ret = apply_function_fa(tar, num, args);
    free(args);
    return ret;
}

struct object_s *apply_function_fa(struct object_s *restrict tar, uint32_t num,
                                   struct object_s **args) {
    struct object_s *ret = new_base();
    ret->type = OBJ_APPL;
    ret->detail.app.num_args = num;
    ret->detail.app.fun = copy(tar);
    ret->detail.app.args = calloc(num, sizeof(struct object_s *));

    for (uint32_t i = 0; i < num; i++) {
        ret->detail.app.args[i] = copy(args[i]);
    }

    return ret;
}
