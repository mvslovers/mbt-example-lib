/* mi_fmtnum -- C face of the COBOL formatter MIFMTN */
#include "mvsinfo.h"

extern int mifmtn(const void *num, void *text) asm("MIFMTN");
#define VL(p) ((void *)((unsigned)(p) | 0x80000000))

char *mi_fmtnum(int n, char out[13])
{
    mifmtn(&n, VL(out));
    out[12] = '\0';
    return out;
}
