/* exlib.h — example library public header */
#ifndef EXLIB_H
#define EXLIB_H

/* return the sum of a and b */
int exlib_add(int a, int b) asm("EXLIBADD");

#endif /* EXLIB_H */
