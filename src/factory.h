#ifndef FACTORY_H
#define FACTORY_H

#include <stdint.h>
#include "globals.h"

struct object_s *new_fun(struct object_s *(*fun)(struct object_s **), uint32_t num_args);
struct object_s *new_unsigned(uint32_t val);
struct object_s *new_signed(int32_t val);
struct object_s *new_char(char val);
struct object_s *new_byte(uint8_t val);
struct object_s *new_bool(int val);
struct object_s *new_ptr(void *val);
struct object_s *new_constucted(enum constr cst, uint32_t num);
void apply_constructed(struct object_s *restrict tar, uint32_t num, ...);
struct object_s *apply_function(struct object_s *restrict tar, uint32_t num, ...);
struct object_s *apply_function_fa(struct object_s *restrict tar, uint32_t num,
                                   struct object_s **args);

#endif
