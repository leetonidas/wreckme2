#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "globals.h"
#include "factory.h"

void do_delete(struct object_s *);
void replace(struct object_s *, struct object_s *);

void delete_val(struct val_s *val) {
    if (val->type == VAL_CONSTRUCT) {
        for (uint32_t i = 0; i < val->detail.con.num; ++i) {
            del(val->detail.con.objs[i]);
        }
        free(val->detail.con.objs);
    }
}

struct object_s *find_non_alias(struct object_s* tar) {
    return (tar->type == OBJ_ALI) ? find_non_alias(tar->detail.alias) : tar;
}

void do_delete(struct object_s *tar) {
    uint32_t n;
    switch (tar->type) {
    case OBJ_VAL:
        delete_val(&tar->detail.val);
        break;
    case OBJ_FUN:
        break;
    case OBJ_ALI:
        del(tar->detail.alias);
        break;
    case OBJ_APPL:
        del(tar->detail.app.fun);
        for (n = 0; n < tar->detail.app.num_args; ++n) {
            del(tar->detail.app.args[n]);
        }
        free(tar->detail.app.args);
    }
}

struct object_s *copy(struct object_s *tar) {
    if (tar->type == OBJ_ALI) {
        struct object_s *ret = find_non_alias(tar->detail.alias);
        ++ret->refs;
        return ret;
    } else {
        tar->refs += 1;
        return tar;
    }
}

void replace(struct object_s *tar, struct object_s *src) {
    uint32_t refs = tar->refs;
    do_delete(tar);
    memcpy(tar, src, sizeof(*tar));
    tar->refs = refs;
}

int suf_supplied(struct object_s *tar) {
    struct object_s *cur = tar;
    uint32_t args = 0;
    while(cur->type != OBJ_FUN) {
        switch(cur->type) {
        case OBJ_ALI:
            cur = cur->detail.alias;
            break;
        case OBJ_APPL:
            args += cur->detail.app.num_args;
            cur = cur->detail.app.fun;
            break;
        default:
            //fputs("suf_supplied", stderr);
            exit(1);
        }
    }
    return args >= cur->detail.fun.args;
}

struct apply {
    struct function_s *fun;
    uint32_t num_args;
    struct object_s **args;
};

struct apply *partial_eval(struct object_s *tar) {
    struct apply *ret;
    struct object_s *tmp;
    uint32_t i;
    switch (tar->type) {
    case OBJ_ALI:
        tmp = copy(find_non_alias(tar));
        del(tar->detail.alias);
        tar->detail.alias = tmp;
        return partial_eval(tmp);
    case OBJ_FUN:
        ret = calloc(1, sizeof(struct apply));
        ret->args = calloc(tar->detail.fun.args, sizeof(struct object_s *));
        ret->fun = &tar->detail.fun;
        return ret;
    case OBJ_APPL:
        ret = partial_eval(tar->detail.app.fun);
        for (i = 0; i < tar->detail.app.num_args; i++)
            ret->args[ret->num_args++] = tar->detail.app.args[i];
        return ret;
    default:
        //fputs("partial_eval", stderr);
        exit(1);
    }
}

struct object_s *eval(struct object_s *tar) {
    struct object_s *r, *x;
    struct apply *aps;
    uint32_t m, i;
    switch (tar->type) {
    case OBJ_ALI:
        r = eval(find_non_alias(tar->detail.alias));
        if (tar->detail.alias != r) {
            r = copy(r);
            del(tar->detail.alias);
            tar->detail.alias = r;
            return eval(tar);
        }
        return r;
    case OBJ_FUN:
        if (tar->detail.fun.args == 0) {
            return tar->detail.fun.fun(NULL);
        } else {
            return tar;
        }
    case OBJ_APPL:
        if (suf_supplied(tar->detail.app.fun)) {
            r = copy(eval(tar->detail.app.fun));
            del(tar->detail.app.fun);
            tar->detail.app.fun = r;
            return eval(tar);
        }
        if (!suf_supplied(tar))
            return tar;
        
        aps = partial_eval(tar->detail.app.fun);
        m = aps->fun->args - aps->num_args;
        for (i = 0; i < m; ++i)
            aps->args[aps->num_args++] = tar->detail.app.args[i];
        r = copy(aps->fun->fun(aps->args));
        free(aps->args);
        if (tar->detail.app.num_args == m) {
            free(aps);
            do_delete(tar);
            tar->type = OBJ_ALI;
            tar->detail.alias = r;
            return eval(tar);
        }
        free(aps);

        x = copy(apply_function_fa(r, tar->detail.app.num_args - m,
                                   tar->detail.app.args + m));
        del(r);

        do_delete(tar);
        tar->type = OBJ_ALI;
        tar->detail.alias = x;
        return eval(x);
    default:
        return tar;
    }
}

struct val_s *get_val(struct object_s *tar) {
    struct object_s *ret;
    switch (tar->type) {
    case OBJ_FUN:
        if (tar->detail.fun.args != 0) {
 //           fputs("get_val", stderr);
            abort();
        }
        tar->type = OBJ_ALI;
        tar->detail.alias = copy(tar->detail.fun.fun(NULL));
        return get_val(tar->detail.alias);
    case OBJ_APPL:
        eval(tar);
        return get_val(tar);
    case OBJ_VAL:
        return &tar->detail.val;
    case OBJ_ALI:
        ret = copy(find_non_alias(tar->detail.alias));
        del(tar->detail.alias);
        tar->detail.alias = ret;
        return get_val(ret);
    }
}

void del(struct object_s *tar) {
    if (--tar->refs == 0) {
        do_delete(tar);
        free(tar);
    }
}
