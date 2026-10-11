/* TSTHEX -- mi_hexline: offset, hex, text, short last line */
#include <string.h>
#include <mbtcheck.h>
#include "mvsinfo.h"

int main(void)
{
    char line[80];
    const char data[] = "ABCDEFGHIJKLMNOPQR";

    mi_hexline(line, data, 16, 0);
    CHECK(strncmp(line, "000000 ", 7) == 0, "first line starts at offset 0");
    CHECK(strstr(line, "*ABCDEFGHIJKLMNOP*") != NULL, "16 bytes as text");
    mi_hexline(line, data + 16, 2, 16);
    CHECK(strncmp(line, "000010 ", 7) == 0, "second line at offset 16");
    CHECK(strstr(line, "*QR*") != NULL, "a short last line");
    return mbt_test_summary("TSTHEX");
}
