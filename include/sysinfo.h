/* sysinfo.h — query MVS system information from control blocks
**
** This module is NOT autocall-compatible: it exports multiple functions
** from a single object member (SYSINFO). The linker cannot resolve
** individual symbols via autocall — the consuming project must use
** dep_includes in project.toml to generate explicit INCLUDE statements.
**
** See the README for an explanation of autocall vs non-autocall modules.
*/
#ifndef SYSINFO_H
#define SYSINFO_H

/*
** sysinfo_jobname() — return the current job name from the TIOT.
**
** Navigates PSA -> TCB -> TIOT -> TIOCNJOB.
** Returns a pointer to a static 9-byte buffer (8 chars + NUL).
** The returned string is space-padded and NUL-terminated.
*/
const char *sysinfo_jobname(void) asm("SYSIFJOB");

/*
** sysinfo_sysid() — return the SMF system identifier.
**
** Navigates CVT -> SMCA -> SMCASID (4 bytes).
** Returns a pointer to a static 5-byte buffer (4 chars + NUL).
*/
const char *sysinfo_sysid(void) asm("SYSIFsid");

/*
** sysinfo_ipldate() — return the IPL date as packed decimal.
**
** Reads CVT -> CVTDATE (offset 0x38).
** Returns the raw packed decimal value 0x0CYYDDDF.
*/
unsigned sysinfo_ipldate(void) asm("SYSIFDTI");

#endif /* SYSINFO_H */
