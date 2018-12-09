#include <stdio.h>
#include <stdlib.h>
#include "num.h"
#include "globals.h"
#include "factory.h"

struct object_s *do_add(struct object_s **);
struct object_s *do_sub(struct object_s **);
struct object_s *do_band(struct object_s **args);
struct object_s *do_bor(struct object_s **args);
struct object_s *do_bnot(struct object_s **args);
struct object_s *do_cxor(struct object_s **args);
struct object_s *do_eq(struct object_s **args);
struct object_s *do_cnst(struct object_s **args);
struct object_s *do_dec(struct object_s **args);
struct object_s *do_compose(struct object_s **args);
struct object_s *do_putChr(struct object_s **args);
struct object_s *do_gray_inc(struct object_s **args);
struct object_s *do_rem(struct object_s **args);
struct object_s *do_flip(struct object_s **args);
struct object_s *do_to_unsigned(struct object_s **args);
struct object_s *do_to_char(struct object_s **args);

struct object_s zero = {.type = OBJ_VAL,
                         .refs = 1,
                         .detail.val.type = VAL_UNSIGNED,
                         .detail.val.detail.uns = 0};

struct object_s one = {.type = OBJ_VAL,
                         .refs = 1,
                         .detail.val.type = VAL_UNSIGNED,
                         .detail.val.detail.uns = 1};

struct object_s true = {.type = OBJ_VAL,
                         .refs = 1,
                         .detail.val.type = VAL_BOOL,
                         .detail.val.detail.bool = 1};

struct object_s false = {.type = OBJ_VAL,
                         .refs = 1,
                         .detail.val.type = VAL_BOOL,
                         .detail.val.detail.bool = 0};

struct object_s compose = {
    .type = OBJ_FUN,
    .refs = 1,
    .detail.fun = {
        .fun = do_compose, 
        .args = 3}
    };

struct object_s add = {
    .type = OBJ_FUN,
    .refs = 1,
    .detail.fun = {
        .fun = do_add, 
        .args = 2}
    };

struct object_s to_unsigned = {
    .type = OBJ_FUN,
    .refs = 1,
    .detail.fun = {
        .fun = do_to_unsigned, 
        .args = 1}
    };

struct object_s to_char = {
    .type = OBJ_FUN,
    .refs = 1,
    .detail.fun = {
        .fun = do_to_char, 
        .args = 1}
    };

struct object_s sub = {
    .type = OBJ_FUN,
    .refs = 1,
    .detail.fun = {
        .fun = do_sub, 
        .args = 2}
    };

struct object_s rem = {
    .type = OBJ_FUN,
    .refs = 1,
    .detail.fun = {
        .fun = do_rem, 
        .args = 2}
    };

struct object_s flip = {
    .type = OBJ_FUN,
    .refs = 1,
    .detail.fun = {
        .fun = do_flip, 
        .args = 3}
    };

struct object_s band = {
    .type = OBJ_FUN,
    .refs = 1,
    .detail.fun = {
        .fun = do_band, 
        .args = 2}
    };

struct object_s bor = {
    .type = OBJ_FUN,
    .refs = 1,
    .detail.fun = {
        .fun = do_bor, 
        .args = 2}
    };

struct object_s bnot = {
	.type = OBJ_FUN,
	.refs = 1,
	.detail.fun = {
		.fun = do_bnot,
		.args = 1}
};

struct object_s eq = {
    .type = OBJ_FUN,
    .refs = 1,
    .detail.fun = {
        .fun = do_eq, 
        .args = 2}
    };

struct object_s *neq_hlp_list[1] = { &bnot };

struct object_s neq_hlp = {
		.type = OBJ_APPL,
		.refs = 1,
		.detail.app = {
			.fun = &compose,
			.num_args = 1,
			.args = neq_hlp_list
		}
};

struct object_s *neq_list[2] = { &neq_hlp, &eq };

struct object_s neq = {
	.type = OBJ_APPL,
	.refs = 1,
	.detail.app = {
		.fun = &compose,
		.num_args = 2,
		.args = neq_list
	}
};

struct object_s cnst = {
    .type = OBJ_FUN,
    .refs = 1,
    .detail.fun = {
        .fun = do_cnst, 
        .args = 2}
    };

struct object_s cxor = {
    .type = OBJ_FUN,
    .refs = 1,
    .detail.fun = {
        .fun = do_cxor, 
        .args = 2}
    };

struct object_s dec = {
    .type = OBJ_FUN,
    .refs = 1,
    .detail.fun = {
        .fun = do_dec, 
        .args = 1}
    };


struct object_s gray_inc = {
    .type = OBJ_FUN,
    .refs = 1,
    .detail.fun = {
        .fun = do_gray_inc, 
        .args = 1}
    };

struct object_s putChar = {
    .type = OBJ_FUN,
    .refs = 1,
    .detail.fun = {
        .fun = do_putChr, 
        .args = 1}
    };

struct object_s *do_add(struct object_s **args) {
    struct val_s *l = get_val(args[0]);
    struct val_s *r = get_val(args[1]);
    
    if (r->type == VAL_CONSTRUCT || l->type == VAL_CONSTRUCT || r->type != l->type)
        abort();

    switch (r->type) {
    case VAL_CHAR:
        return new_char(l->detail.chr + r->detail.chr);
    case VAL_BYTE:
        return new_byte(l->detail.byte + r->detail.byte);
    case VAL_SIGNED:
        return new_signed(l->detail.sig + r->detail.sig);
    case VAL_UNSIGNED:
        //printf("%lx + %lx\n", l->detail.uns, r->detail.uns);
        return new_unsigned(l->detail.uns + r->detail.uns);
    default:
        return args[0];
    }
}

struct object_s *do_sub(struct object_s **args) {
    struct val_s *l = get_val(args[0]);
    struct val_s *r = get_val(args[1]);
    
    if (r->type == VAL_CONSTRUCT || l->type == VAL_CONSTRUCT || r->type != l->type) {
        abort();
    }
    
    switch (r->type) {
    case VAL_CHAR:
        return new_char(l->detail.chr - r->detail.chr);
    case VAL_BYTE:
        return new_byte(l->detail.byte - r->detail.byte);
    case VAL_SIGNED:
        return new_signed(l->detail.sig - r->detail.sig);
    case VAL_UNSIGNED:
        return new_unsigned(l->detail.uns - r->detail.uns);
    default:
        return args[0];
    }
}

struct object_s *do_band(struct object_s **args) {
    int a = get_val(args[0])->detail.bool;
    int b = get_val(args[1])->detail.bool;
    if (a && b)
        return &true;
    else
        return &false;
}

struct object_s *do_bor(struct object_s **args) {
    return new_bool(
        get_val(args[0])->detail.bool || get_val(args[1])->detail.bool);
}

struct object_s *do_bnot(struct object_s **args) {
	if (get_val(args[0])->detail.bool)
		return &false;
	else
		return &true;
}

struct object_s *do_cxor(struct object_s **args) {
    return new_bool(
        get_val(args[0])->detail.bool ^ get_val(args[1])->detail.bool);
}

struct object_s *do_dec(struct object_s **args) {
    struct object_s *t = copy(apply_function(&cxor, 2, args[0], new_char(' ')));
    char v = get_val(t)->detail.chr ^ 0x20;
    del(t);
    if (v >= 'A' && v <= 'Z') {
        return new_char(26 - (v - 'A') + 'A');
    } else if (v >= 'a' && v <= 'z') {
        return new_char(26 - (v - 'a') + 'a');
    }
    return args[0];
}

struct object_s *do_compose(struct object_s **args) {
    return apply_function(args[0], 1, apply_function(args[1], 1, args[2]));
}

struct object_s *do_putChr(struct object_s **args) {
    putc(get_val(args[0])->detail.chr, stdout);
    return &one;
}

struct object_s *do_cnst(struct object_s **args) {
    return args[0];
}

struct object_s *do_eq(struct object_s **args) {
    struct val_s *l = get_val(args[0]);
    struct val_s *r = get_val(args[1]);
    if (r->type != l->type)
        abort();
    if (r->type == VAL_CONSTRUCT || l->type == VAL_CONSTRUCT)
        return &false;
    switch (r->type) {
    case VAL_BOOL:
        return (l->detail.bool == r->detail.bool) ? &true : &false;
    case VAL_CHAR:
        return (l->detail.chr == r->detail.chr) ? &true : &false;
    case VAL_BYTE:
        return (l->detail.byte == r->detail.byte) ? &true : &false;
    case VAL_PTR:
        return (l->detail.ptr == r->detail.ptr) ? &true : &false;
    case VAL_SIGNED:
        return (l->detail.sig == r->detail.sig) ? &true : &false;
    case VAL_UNSIGNED:
        return (l->detail.uns == r->detail.uns) ? &true : &false;
    }
    return &false;
}

struct object_s *do_gray_inc(struct object_s **args) {
    struct val_s *l = get_val(args[0]);
    register unsigned x = l->detail.uns;
    return new_unsigned(x ^ (x & 1 ? (x & (-x)) < 1 : 1));
}

struct object_s *do_rem(struct object_s **args) {
    struct val_s *l = get_val(args[0]);
    struct val_s *r = get_val(args[1]);
    return new_unsigned(l->detail.uns % r->detail.uns);
}

struct object_s *do_flip(struct object_s **args) {
    return apply_function(args[0], 2, args[2], args[1]);
}

struct object_s *do_to_unsigned(struct object_s **args) {
    struct val_s *l = get_val(args[0]);
    switch (l->type) {
    case VAL_BOOL:
        return new_unsigned((uint32_t) l->detail.bool);
    case VAL_CHAR:
        return new_unsigned((uint32_t) l->detail.chr );
    case VAL_BYTE:
        return new_unsigned((uint32_t) l->detail.byte);
    case VAL_PTR:
        return new_unsigned((uint32_t) l->detail.ptr );
    case VAL_SIGNED:
        return new_unsigned((uint32_t) l->detail.sig );
    case VAL_UNSIGNED:
        return new_unsigned((uint32_t) l->detail.uns );
    default:
        return &zero;
    }
}

struct object_s *do_to_char(struct object_s **args) {
    struct val_s *l = get_val(args[0]);
    switch (l->type) {
    case VAL_BOOL:
        return new_char((char) l->detail.bool);
    case VAL_CHAR:
        return new_char((char) l->detail.chr );
    case VAL_BYTE:
        return new_char((char) l->detail.byte);
    case VAL_PTR:
        return new_char((char) l->detail.ptr );
    case VAL_SIGNED:
        return new_char((char) l->detail.sig );
    case VAL_UNSIGNED:
        return new_char((char) l->detail.uns );
    default:
        return new_char('\0');
    }
}
