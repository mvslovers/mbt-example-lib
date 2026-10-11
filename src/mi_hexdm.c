/* mi_hexdump -- dump storage to stdout, 16 bytes a line */
#include <stdio.h>
#include "mvsinfo.h"

void mi_hexdump(const void *p, size_t n)
{
    const unsigned char *b = p;
    char line[80];
    size_t off;

    for (off = 0; off < n; off += 16) {
        mi_hexline(line, b + off, n - off < 16 ? n - off : 16, off);
        puts(line);
    }
}
