/* jesinf.c — query JES2 job queue information
**
** NOT autocall-compatible: two functions in one member (JESINF).
** Uses the crent370 JES2 API to enumerate jobs on the queue.
*/
#include <stdlib.h>
#include <string.h>
#include <clibjes2.h>
#include "jesinf.h"

/* map JES queue type to our status constants */
static unsigned char map_status(unsigned char q_type)
{
    /* JQETYPE values from haspjqe.h:
    ** 1 = input, 2 = executing, 3 = output/purge
    */
    switch (q_type) {
    case 1:  return JESINF_ST_INPUT;
    case 2:  return JESINF_ST_EXEC;
    default: return JESINF_ST_OUTPUT;
    }
}

int jesinf_count(void)
{
    JES *jes;
    JESJOB **jobs;
    int count;
    int i;

    jes = jesopen();
    if (jes == 0) {
        return -1;
    }

    jobs = jesjob(jes, "*", FILTER_JOBNAME, 0);
    if (jobs == 0) {
        jesclose(&jes);
        return 0;
    }

    /* count entries in NULL-terminated array */
    count = 0;
    for (i = 0; jobs[i] != 0; i++) {
        count++;
    }

    jesjobfr(&jobs);
    jesclose(&jes);

    return count;
}

JESINF_ENTRY *jesinf_list(int *count)
{
    JES *jes;
    JESJOB **jobs;
    JESINF_ENTRY *list;
    int njobs;
    int i;

    *count = 0;

    jes = jesopen();
    if (jes == 0) {
        return 0;
    }

    jobs = jesjob(jes, "*", FILTER_JOBNAME, 0);
    if (jobs == 0) {
        jesclose(&jes);
        return 0;
    }

    /* count jobs */
    njobs = 0;
    for (i = 0; jobs[i] != 0; i++) {
        njobs++;
    }

    list = (JESINF_ENTRY *)malloc(njobs * sizeof(JESINF_ENTRY));
    if (list == 0) {
        jesjobfr(&jobs);
        jesclose(&jes);
        return 0;
    }

    for (i = 0; i < njobs; i++) {
        memcpy(list[i].jobname, jobs[i]->jobname, 9);
        memcpy(list[i].jobid, jobs[i]->jobid, 9);
        memcpy(list[i].owner, jobs[i]->owner, 9);
        list[i].status = map_status(jobs[i]->q_type);
    }

    *count = njobs;

    jesjobfr(&jobs);
    jesclose(&jes);

    return list;
}
