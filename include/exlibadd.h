/* exlibadd.h — example library public header */
#ifndef EXLIBADD_H
#define EXLIBADD_H

/* return the sum of a and b */
int exlib_add(int a, int b) asm("EXLIBADD");

#endif /* EXLIBADD_H */
