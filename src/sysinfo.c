/* sysinfo.c — query MVS system information from control blocks
**
** NOT autocall-compatible: three functions in one member (SYSINFO).
** Demonstrates navigating MVS control block chains:
**   PSA (addr 0) -> TCB -> TIOT      for job name
**   CVT (addr 16) -> SMCA            for system ID
**   CVT -> CVTDATE                   for IPL date
*/
#include <string.h>
#include <cvt.h>
#include <ieftiot.h>
#include <clibsmf.h>
#include "sysinfo.h"

const char *sysinfo_jobname(void)
{
    static char buf[9];
    TIOT *tiot;

    tiot = get_tiot();
    memcpy(buf, tiot->TIOCNJOB, 8);
    buf[8] = '\0';

    return buf;
}

const char *sysinfo_sysid(void)
{
    static char buf[5];
    CVT *cvt;
    SMCA *smca;

    cvt = CVTPTR;
    smca = (SMCA *)cvt->cvtsmca;

    if (smca != 0) {
        memcpy(buf, smca->smcasid, 4);
        buf[4] = '\0';
    } else {
        memcpy(buf, "????", 5);
    }

    return buf;
}

unsigned sysinfo_ipldate(void)
{
    CVT *cvt;

    cvt = CVTPTR;
    return cvt->cvtdate;
}
