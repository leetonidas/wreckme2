#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "list.h"
#include "factory.h"
#include "num.h"

uint32_t ref[] = {183, 12, 12,  233, 18, 23, 29, 34, 15, 23,  9,  106, 15,
                  12,  12, 233, 90,  22, 50, 34, 15, 29, 15,  23, 82,  74,
                  15,  84, 15,  50,  15, 23, 82, 74, 35, 173, 64, 34};

int main() {
    char val;
    struct object_s *list = copy(new_constucted(C_LIST_NULL, 0));

    struct object_s *fibs = copy(apply_function(&take, 2, new_unsigned(10000), apply_function(&fib, 2, &one, &zero)));

    while (scanf("%c", &val) && val != '\n') {
        struct object_s *ele = new_constucted(C_LIST_ELE, 2);
        struct object_s *tmp = copy(new_char(val));
        apply_constructed(ele, 2, tmp, list);
        del(tmp);
        del(list);
        list = copy(ele);
    }

    struct object_s *tmp, *tmp2;
    tmp = new_constucted(C_LIST_ELE, 2);
    apply_constructed(tmp, 2, new_char('\n'), &mempty);
    tmp2 = new_constucted(C_LIST_ELE, 2);
	apply_constructed(
		tmp2, 2,
		apply_function(
			&compose, 3, apply_function(&add, 1, new_char('(')), &to_char,
			apply_function(
				&list_eq, 2,
				apply_function(&ufrom_array, 2,
					new_unsigned(sizeof(ref) /
						sizeof(ref[0])),
					new_ptr(ref)),
				apply_function(&map, 2, apply_function(&flip, 2, &index, fibs),
					apply_function(&map, 2, &to_unsigned, list)))),
		tmp);
    del(fibs);
    del(list);
    tmp = new_constucted(C_LIST_ELE, 2);
    apply_constructed(tmp, 2, new_char(':'), tmp2);
    tmp2 = copy(apply_function(&putStr, 1, tmp));
    get_val(tmp2);
    del(tmp2);

    return 0;
}