#include <stdlib.h>
#include "list.h"
#include "globals.h"
#include "factory.h"
#include "num.h"

struct object_s *do_null(struct object_s**);
struct object_s *do_head(struct object_s**);
struct object_s *do_tail(struct object_s**);
struct object_s *do_take(struct object_s**);
struct object_s *do_drop(struct object_s**);
struct object_s *do_map(struct object_s **);
struct object_s *do_foldl(struct object_s **);
struct object_s *do_from_array(struct object_s **);
struct object_s *do_ufrom_array(struct object_s **);
struct object_s *do_zip(struct object_s **);
struct object_s *do_teq(struct object_s **);
struct object_s *do_list_eq(struct object_s **);
struct object_s *do_iterate(struct object_s **);
struct object_s *do_fib(struct object_s **);
struct object_s *do_take_while(struct object_s **);

struct object_s mempty = {
    .type = OBJ_VAL,
    .refs = 1,
    .detail.val.type = VAL_CONSTRUCT,
    .detail.val.detail.con = {.c = C_LIST_NULL, .num = 0, .objs = NULL}};

struct object_s fib = {
    .type = OBJ_FUN,
    .refs = 1,
    .detail.fun = {
        .fun = do_fib,
        .args = 2
    }
};

struct object_s null = {
    .type = OBJ_FUN,
    .refs = 1,
    .detail.fun = {
        .fun = do_null, 
        .args = 1}
    };

struct object_s head = {
    .type = OBJ_FUN,
    .refs = 1,
    .detail.fun = {
        .fun = do_head, 
        .args = 1}
    };

struct object_s tail = {
    .type = OBJ_FUN,
    .refs = 1,
    .detail.fun = {
        .fun = do_tail, 
        .args = 1}
    };

struct object_s take = {
    .type = OBJ_FUN,
    .refs = 1,
    .detail.fun = {
        .fun = do_take, 
        .args = 2}
    };

struct object_s drop = {
    .type = OBJ_FUN,
    .refs = 1,
    .detail.fun = {
        .fun = do_drop, 
        .args = 2}
    };

struct object_s map = {
    .type = OBJ_FUN,
    .refs = 1,
    .detail.fun = {
        .fun = do_map, 
        .args = 2}
    };

struct object_s foldl = {
    .type = OBJ_FUN,
    .refs = 1,
    .detail.fun = {
        .fun = do_foldl, 
        .args = 3}
    };

struct object_s ufrom_array = {
    .type = OBJ_FUN,
    .refs = 1,
    .detail.fun = {
        .fun = do_ufrom_array, 
        .args = 2}
    };

struct object_s from_array = {
    .type = OBJ_FUN,
    .refs = 1,
    .detail.fun = {
        .fun = do_from_array, 
        .args = 2}
    };

struct object_s zip = {
    .type = OBJ_FUN,
    .refs = 1,
    .detail.fun = {
        .fun = do_zip, 
        .args = 2}
    };

struct object_s teq = {
    .type = OBJ_FUN,
    .refs = 1,
    .detail.fun = {
        .fun = do_teq, 
        .args = 1}
    };

struct object_s list_eq = {
    .type = OBJ_FUN,
    .refs = 1,
    .detail.fun = {
        .fun = do_list_eq,
        .args = 2}
    };

struct object_s iterate = {
    .type = OBJ_FUN,
    .refs = 1,
    .detail.fun = {
        .fun = do_iterate,
        .args = 2}
    };

struct object_s *athlp_lst[2] = {&head};

struct object_s addhlp = {
    .type = OBJ_APPL,
    .refs = 1,
    .detail.app = {
        .fun = &compose,
        .num_args = 1,
        .args = athlp_lst
    }
};

struct object_s *at_lst[2] = {&addhlp, &drop};

struct object_s at = {
    .type = OBJ_APPL,
    .refs = 1,
    .detail.app = {
        .fun = &compose,
        .num_args = 2,
        .args = at_lst
    }
};

struct object_s *sum_alist[2] = {&add, &zero};

struct object_s sum = {
    .type = OBJ_APPL,
    .refs = 1,
    .detail.app = {
        .fun = &foldl,
        .num_args = 2,
        .args = sum_alist
    }
};

struct object_s *length_hlp_alist[1] = {&one};

struct object_s length_hlp = {
    .type = OBJ_APPL,
    .refs = 1,
    .detail.app = {
        .fun = &cnst,
        .num_args = 1,
        .args = length_hlp_alist
    }
};

struct object_s *length_hlp2_alist[1] = {&length_hlp};

struct object_s length_hlp2 = {
    .type = OBJ_APPL,
    .refs = 1,
    .detail.app = {
        .fun = &map,
        .num_args = 1,
        .args = length_hlp2_alist
    }
};

struct object_s *length_alist[2] = {&sum, &length_hlp2};

struct object_s length = {
    .type = OBJ_APPL,
    .refs = 1,
    .detail.app = {
        .fun = &compose,
        .num_args = 2,
        .args = length_alist
    }
};

struct object_s *all_ct_alist[2] = {&band, &true};

struct object_s all_ct = {
    .type = OBJ_APPL,
    .refs = 1,
    .detail.app = {
        .fun = &foldl,
        .num_args = 2,
        .args = all_ct_alist
    }
};

struct object_s *putStr_hlp_alist[1] = {&putChar};

struct object_s putStr_hlp = {
    .type = OBJ_APPL,
    .refs = 1,
    .detail.app = {
        .fun = &map,
        .num_args = 1,
        .args = putStr_hlp_alist
    }
};

struct object_s *putStr_alist[2] = {&sum, &putStr_hlp};

struct object_s putStr = {
    .type = OBJ_APPL,
    .refs = 1,
    .detail.app = {
        .fun = &compose,
        .num_args = 2,
        .args = putStr_alist
    }
};

struct object_s take_while = {
	.type = OBJ_FUN,
	.refs = 1,
	.detail.fun = {
		.fun = do_take_while,
		.args = 2
	}
};

struct object_s *index_hlp2list[1] = { &length };

struct object_s index_hlp2 = {
	.type = OBJ_APPL,
	.refs = 1,
	.detail.app = {
		.fun = &compose,
		.num_args = 1,
		.args = index_hlp2list
	}
};

struct object_s *index_hlplist[2] = { &index_hlp2, &take_while };

struct object_s index_hlp = {
	.type = OBJ_APPL,
	.refs = 1,
	.detail.app = {
		.fun = &compose,
		.num_args = 2,
		.args = index_hlplist
	}
};

struct object_s *index_list[2] = { &index_hlp, &neq };

struct object_s index = {
	.type = OBJ_APPL,
	.refs = 1,
	.detail.app = {
		.fun = &compose,
		.num_args = 2,
		.args = index_list
	}
};

struct object_s *do_null(struct object_s **args) {
    struct val_s *v = get_val(args[0]);
    return new_bool(v->detail.con.c == C_LIST_NULL);
}

struct object_s *do_head(struct object_s **args) {
    struct val_s *v = get_val(args[0]);
    return v->detail.con.objs[0];
}

struct object_s *do_tail(struct object_s **args) {
    struct val_s *v = get_val(args[0]);
    return v->detail.con.objs[1];
}

// take Int [a]
struct object_s *do_take(struct object_s **args) {

    struct object_s *in =copy(apply_function(&null, 1, args[1]));
    int b = get_val(in)->detail.bool;
    del(in);

    if (b)
        return &mempty;
    else if (get_val(args[0])->detail.uns == 0)
        return &mempty;
    else {
        struct object_s *ret = new_constucted(C_LIST_ELE, 2);
        // arg1
        struct object_s *l = new_unsigned(get_val(args[0])->detail.uns - 1);
        // arg2
        struct object_s *tl = apply_function(&tail, 1, args[1]);
        // apply
        struct object_s *tk = apply_function(&take, 2, l, tl);
        // cleanup
        struct object_s *hd = apply_function(&head, 1, args[1]);
        apply_constructed(ret, 2, hd, tk);
        return ret;
    }
}

struct object_s *do_drop(struct object_s **args) {

    struct object_s *in =copy(apply_function(&null, 1, args[1]));
    int b = get_val(in)->detail.bool;
    del(in);

    if (b)
        return &mempty;
    else if (get_val(args[0])->detail.uns == 0)
        return args[1];
    else {
        return apply_function(&drop, 2, apply_function(&sub, 2, args[0], &one),
                              apply_function(&tail, 1, args[1]));
    }
}

struct object_s *do_map(struct object_s **args) {
    struct object_s *in = copy(apply_function(&null, 1, args[1]));
    int b = get_val(in)->detail.bool;
    del(in);

    if(b)
        return args[1];
    else {
        struct object_s *ret = new_constucted(C_LIST_ELE, 2);
        struct object_s *old_val = apply_function(&head, 1, args[1]);
        struct object_s *old_tl = apply_function(&tail, 1, args[1]);
        struct object_s *tl =
            apply_function(&map, 2, args[0], old_tl);
        struct object_s *val = apply_function(args[0], 1, old_val);
        apply_constructed(ret, 2, val, tl);
        return ret;
    }
}

struct object_s *do_foldl(struct object_s **args) {
    struct object_s *in = copy(apply_function(&null, 1, args[2]));
    int b = get_val(in)->detail.bool;
    del(in);

    if (b)
        return args[1];

    struct object_s *val = apply_function(&head, 1, args[2]);
    val = apply_function(args[0], 2, args[1], val);
    struct object_s *rec = apply_function(&tail, 1, args[2]);
    return apply_function(&foldl, 3, args[0], val, rec);
}

struct object_s *do_from_array(struct object_s **args) {
    if (get_val(args[0])->detail.uns == 0)
        return &mempty;

    struct object_s *e = new_constucted(C_LIST_ELE, 2);
    struct object_s *v = new_char(*(char *)get_val(args[1])->detail.ptr);
    struct object_s *n = new_ptr(((char *)get_val(args[1])->detail.ptr) + 1);
    struct object_s *l = new_unsigned(get_val(args[0])->detail.uns - 1);
    apply_constructed(e, 2, v, apply_function(&from_array, 2, l, n));
    return e;
}

struct object_s *do_ufrom_array(struct object_s **args) {
    if (get_val(args[0])->detail.uns == 0)
        return new_constucted(C_LIST_NULL, 0);

    struct object_s *e = new_constucted(C_LIST_ELE, 2);
    struct object_s *v = new_unsigned(*(uint32_t *)get_val(args[1])->detail.ptr);
    struct object_s *n = new_ptr(((uint32_t *)get_val(args[1])->detail.ptr) + 1);
    struct object_s *l = apply_function(&sub, 2, args[0], &one);
    apply_constructed(e, 2, v, apply_function(&ufrom_array, 2, l, n));
    return e;
}

struct object_s *do_zip(struct object_s **args) {
    struct object_s *b =
        copy(apply_function(&bor, 2, apply_function(&null, 1, args[0]),
                            apply_function(&null, 1, args[1])));
    int bo = get_val(b)->detail.bool;
    del(b);

    if (bo)
        return &mempty;

    struct object_s *ret = new_constucted(C_LIST_ELE, 2);
    struct object_s *val = new_constucted(C_TUPLE, 2);
    apply_constructed(val, 2, apply_function(&head, 1, args[0]),
                      apply_function(&head, 1, args[1]));
    struct object_s *nxt =
        apply_function(&zip, 2, apply_function(&tail, 1, args[0]),
                       apply_function(&tail, 1, args[1]));
    apply_constructed(ret, 2, val, nxt);
    return ret;
}

struct object_s *do_teq(struct object_s **args) {
    struct val_s *v = get_val(args[0]);
    if (v->type != VAL_CONSTRUCT || v->detail.con.c != C_TUPLE)
        return &false;
    return apply_function(&eq, 2, v->detail.con.objs[0], v->detail.con.objs[1]);
}


struct object_s *do_list_eq(struct object_s **args) {
    struct val_s *l = get_val(args[0]);
    struct val_s *r = get_val(args[1]);
    if (l->type != r->type)
        return &false;
    struct object_s *leq =
        apply_function(&eq, 2, apply_function(&length, 1, args[0]),
                       apply_function(&length, 1, args[1]));
    struct object_s *aeq = apply_function(
        &all_ct, 1,
        apply_function(&map, 2, &teq,
                       apply_function(&zip, 2, args[0], args[1])));
    return apply_function(&band, 2, leq, aeq);
}

struct object_s *do_iterate(struct object_s **args) {
    struct object_s *r = new_constucted(C_LIST_ELE, 2);
    apply_constructed(r, 2, args[1],
                      apply_function(&iterate, 2, args[0],
                                     apply_function(args[0], 1, args[1])));
    return r;
}

struct object_s *do_fib(struct object_s **args) {
    struct object_s *r = new_constucted(C_LIST_ELE, 2);
    struct object_s *nxt = apply_function(&rem, 2, apply_function(&add, 2, args[0], args[1]), new_unsigned(157));
    apply_constructed(r, 2, nxt, apply_function(&fib, 2, args[1], nxt));
    return r;
}

struct object_s *do_take_while(struct object_s **args) {
	struct object_s *t = copy(apply_function(&null, 1, args[1]));
	if (get_val(t)->detail.bool) {
		del(t);
		return &mempty;
	}
	del(t);
	struct object_s *h = copy(apply_function(&head, 1, args[1]));
	struct object_s *b = copy(apply_function(args[0], 1, h));
	struct object_s *r;
	if (get_val(b)->detail.bool) {
		r = new_constucted(C_LIST_ELE, 2);
		apply_constructed(r, 2, h, apply_function(&take_while, 2, args[0], apply_function(&tail, 1, args[1])));
	}
	else {
		r = &mempty;
	}
    del(h);
    del(b);
    return r;
}