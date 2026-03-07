/* hexdump.c — format memory as hex + EBCDIC dump
**
** Autocall-compatible: one function (hexdump), one member (HEXDUMP).
*/
#include <stdio.h>
#include "hexdump.h"

/* is_printable() — check if an EBCDIC byte is printable.
** Uses character range checks instead of hardcoded code points
** to remain EBCDIC-safe.
*/
static int is_printable(unsigned char c)
{
    if (c >= 'A' && c <= 'Z') return 1;
    if (c >= 'a' && c <= 'z') return 1;
    if (c >= '0' && c <= '9') return 1;
    if (c == ' ' || c == '.' || c == ',' || c == '-') return 1;
    if (c == '(' || c == ')' || c == '+' || c == '*') return 1;
    if (c == '/' || c == '&' || c == '=' || c == ':') return 1;
    if (c == ';' || c == '!' || c == '@' || c == '#') return 1;
    if (c == '$' || c == '%' || c == '_' || c == '?') return 1;
    if (c == '\'' || c == '"') return 1;
    return 0;
}

void hexdump(const void *addr, unsigned len)
{
    const unsigned char *p = (const unsigned char *)addr;
    unsigned off;
    unsigned i;
    char hex[50];
    char asc[18];
    int hpos, apos;

    for (off = 0; off < len; off += 16) {
        hpos = 0;
        apos = 0;

        for (i = 0; i < 16 && (off + i) < len; i++) {
            unsigned char b = p[off + i];

            /* hex nibbles */
            hex[hpos++] = "0123456789ABCDEF"[(b >> 4) & 0x0F];
            hex[hpos++] = "0123456789ABCDEF"[b & 0x0F];

            /* space after every 4 bytes */
            if ((i & 3) == 3) {
                hex[hpos++] = ' ';
            }

            /* EBCDIC character or dot */
            asc[apos++] = is_printable(b) ? (char)b : '.';
        }

        hex[hpos] = '\0';
        asc[apos] = '\0';

        printf("  %08X  %-36s *%-16s*\n",
               (unsigned)((const char *)addr + off), hex, asc);
    }
}
