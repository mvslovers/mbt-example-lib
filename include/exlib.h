/* exlib.h — example library public header */
#ifndef EXLIB_H
#define EXLIB_H

/* return the sum of a and b */
int exlib_sub(int a, int b) asm("EXLIBSUB");
void exlib_hello(char *message) asm("EXLIBHEL");

#endif /* EXLIB_H */
