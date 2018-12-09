#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdint.h>

struct object_s;
struct val_s;

struct object_s* evaluate(struct object_s *);
void new_func(struct object_s *(*fun)(struct object_s **), uint32_t num_args, struct function_s *);

#endif
