/* jesinf.h — query JES2 job queue information
**
** This module is NOT autocall-compatible: it exports multiple functions
** from a single object member (JESINF). Consumers must use dep_includes
** in project.toml to pull this member explicitly.
**
** Requires crent370 JES2 support (clibjes2.h).
*/
#ifndef JESINF_H
#define JESINF_H

/* job queue entry returned by jesinf_list() */
typedef struct jesinf_entry JESINF_ENTRY;

struct jesinf_entry {
    char            jobname[9];     /* job name, NUL-terminated         */
    char            jobid[9];       /* job identifier, NUL-terminated   */
    char            owner[9];       /* owner userid, NUL-terminated     */
    unsigned char   status;         /* job status, see JESINF_ST_*      */
};

#define JESINF_ST_INPUT     1       /* job on input queue               */
#define JESINF_ST_EXEC      2       /* job executing                    */
#define JESINF_ST_OUTPUT    3       /* job on output queue              */

/*
** jesinf_count() — return the number of jobs on the JES2 queue.
**
** Returns -1 on error (JES not available).
*/
int jesinf_count(void) asm("JESINFCT");

/*
** jesinf_list() — return an array of job queue entries.
**
** Allocates an array of JESINF_ENTRY structs and sets *count to the
** number of entries. The caller must free the returned pointer.
** Returns NULL on error.
*/
JESINF_ENTRY *jesinf_list(int *count) asm("JESINFLST");

#endif /* JESINF_H */
