/* mi_hexline -- one dump line: offset, 16 bytes in hex, the same as text */
#include <ctype.h>
#include <stdio.h>
#include "mvsinfo.h"

int mi_hexline(char *out, const void *p, size_t n, size_t off)
{
    const unsigned char *b = p;
    size_t i;
    int len = sprintf(out, "%06X ", (unsigned)off);

    for (i = 0; i < 16; i++)
        len += i < n ? sprintf(out + len, "%02X%s", b[i], i % 4 == 3 ? " " : "")
                     : sprintf(out + len, "  %s", i % 4 == 3 ? " " : "");
    out[len++] = '*';
    for (i = 0; i < n && i < 16; i++)
        out[len++] = isprint(b[i]) ? (char)b[i] : '.';
    out[len++] = '*';
    out[len] = '\0';
    return len;
}
