#ifndef NUM_H
#define NUM_H

struct object_s;

extern struct object_s zero;
extern struct object_s one;
extern struct object_s true;
extern struct object_s false;
extern struct object_s add;
extern struct object_s sub;
extern struct object_s band;
extern struct object_s bor;
extern struct object_s bnot;
extern struct object_s cxor;
extern struct object_s cnst;
extern struct object_s teq;
extern struct object_s eq;
extern struct object_s neq;
extern struct object_s dec;
extern struct object_s compose;
extern struct object_s putChar;
extern struct object_s gray_inc;
extern struct object_s rem;
extern struct object_s flip;
extern struct object_s to_unsigned;
extern struct object_s to_char;

#endif
