/* mi_sysid -- the SMF system id: CVT -> SMCA -> SMCASID */
#include <string.h>
#include <ibm/mvs/cvt.h>
#include <mvs/smf.h>
#include "mvsinfo.h"

const char *mi_sysid(void)
{
    static char sid[5];
    SMCA *smca = (SMCA *)CVTPTR->cvtsmca;

    if (smca == NULL)
        return "????";
    memcpy(sid, smca->smcasid, 4);
    sid[4] = '\0';
    return sid;
}
