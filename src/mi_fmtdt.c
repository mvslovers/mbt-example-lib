/* mi_fmtdate -- C face of the COBOL formatter MIFMTD */
#include <string.h>
#include "mvsinfo.h"

/* MIFMTD is COBOL: OS linkage, the addresses of the arguments, the last
** one with the high-order bit set. */
extern int mifmtd(const void *date, void *text) asm("MIFMTD");
#define VL(p) ((void *)((unsigned)(p) | 0x80000000))

char *mi_fmtdate(unsigned date, char out[9])
{
    mifmtd(&date, VL(out));
    out[8] = '\0';
    return out;
}
