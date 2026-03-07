/* hexdump.h — format memory regions as hex + EBCDIC dump
**
** This module is autocall-compatible: the member name HEXDUMP matches
** the single exported function hexdump(). The linker can resolve this
** symbol automatically via SYSLIB without an explicit INCLUDE.
*/
#ifndef HEXDUMP_H
#define HEXDUMP_H

/*
** hexdump() — print a hex + EBCDIC dump of a memory region.
**
** Writes to stdout in classic MVS dump format:
**
**   00FD4810  00000000 00FE1234 00054B00 00FDB350  *..........K.....*
**   00FD4820  007FF900 00000000 00000000 00000000  *.?9...............*
**
** addr:  starting address of the memory region
** len:   number of bytes to dump
*/
void hexdump(const void *addr, unsigned len) asm("HEXDUMP");

#endif /* HEXDUMP_H */
