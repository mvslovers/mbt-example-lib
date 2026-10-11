/* mvsinfo.h -- MVS system information, from C, assembler and COBOL
**
** Every function is a member of its own (autocall), and its external
** name is set with asm() so that it fits in eight characters.
*/
#ifndef MVSINFO_H
#define MVSINFO_H

#include <stddef.h>

/* C: control blocks */
const char *mi_sysid(void) asm("MISYSID");     /* SMF system id, 4 characters  */
unsigned mi_ipldate(void) asm("MIIPLDT");      /* CVTDATE, 0CYYDDDF packed     */

/* C: a hex and EBCDIC dump, 16 bytes a line */
int mi_hexline(char *out, const void *p, size_t n, size_t off) asm("MIHEXLIN");
void mi_hexdump(const void *p, size_t n) asm("MIHEXDMP");

/* Assembler: they take pointers only and drop the high-order bit, so C,
** COBOL and assembler call them alike. */
int mi_jobname(char name[8]) asm("MIJOBN");                    /* from the TIOT */
int mi_time(unsigned *hhmmssth, unsigned *yyddd) asm("MITIME"); /* TIME DEC    */

/* C wrappers around the COBOL formatters MIFMTD and MIFMTN, which expect
** the OS convention (addresses, the last one flagged). */
char *mi_fmtdate(unsigned date, char out[9]) asm("MIFMTDAT");  /* "YYYY.DDD"    */
char *mi_fmtnum(int n, char out[13]) asm("MIFMTNUM");          /* "Z,ZZZ,ZZ9-"  */

#endif
