#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdint.h>

enum obj_type { OBJ_FUN, OBJ_VAL, OBJ_ALI, OBJ_APPL };
enum val_type { VAL_CHAR, VAL_UNSIGNED, VAL_SIGNED, VAL_BYTE, VAL_BOOL, VAL_CONSTRUCT, VAL_PTR };

struct object_s;

struct function_s {
    struct object_s *(*fun)(struct object_s **);
    uint32_t args;
};

struct application_s {
    struct object_s *fun;
    uint32_t num_args;
    struct object_s **args;
};

enum constr {
    C_LIST_NULL,
    C_LIST_ELE,
    C_TUPLE
};

struct constr_s {
    enum constr c;
    uint32_t num;
    struct object_s **objs;
};

struct val_s {
    enum val_type type;
    union{
        char chr;
        uint64_t uns;
        int64_t sig;
        uint8_t byte;
        int bool;
        struct constr_s con;
        void *ptr;
    } detail;
};

struct object_s {
    enum obj_type type;
    uint32_t refs;
    union {
        struct function_s fun;
        struct val_s val;
        struct object_s *alias;
        struct application_s app;
    } detail;
};



struct object_s *copy(struct object_s *);
struct val_s *get_val(struct object_s *);
void del(struct object_s *);
#endif
