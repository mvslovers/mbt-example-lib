/* mi_ipldate -- the date in the CVT, 0CYYDDDF packed decimal */
#include <ibm/mvs/cvt.h>
#include "mvsinfo.h"

unsigned mi_ipldate(void)
{
    return CVTPTR->cvtdate;
}
