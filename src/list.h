#ifndef LIST_H
#define LIST_H

struct object_s;

extern struct object_s null;
extern struct object_s mempty;
extern struct object_s head;
extern struct object_s tail;
extern struct object_s take;
extern struct object_s drop;
extern struct object_s map;
extern struct object_s foldl;
extern struct object_s sum;
extern struct object_s all_ct;
extern struct object_s dec;
extern struct object_s from_array;
extern struct object_s ufrom_array;
extern struct object_s putStr;
extern struct object_s zip;
extern struct object_s length;
extern struct object_s list_eq;
extern struct object_s iterate;
extern struct object_s fib;
extern struct object_s at;
extern struct object_s index;
extern struct object_s take_while;

#endif
