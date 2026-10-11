# mbt-example-lib

An example library for [MBT](https://github.com/mvslovers/mbt) (mbt): one
archive, `mvsinfo.a`, built from **C, assembler and COBOL**, each language
doing what it does best. Its companion
[mbt-example-app](https://github.com/mvslovers/mbt-example-app) links it
into programs written in all three.

| Language | Source | External name | What it does |
|---|---|---|---|
| C | `src/mi_sysid.c` | `MISYSID` | the SMF system id (CVT → SMCA) |
| C | `src/mi_ipldt.c` | `MIIPLDT` | the date in the CVT, `0CYYDDDF` |
| C | `src/mi_hexln.c`, `src/mi_hexdm.c` | `MIHEXLIN`, `MIHEXDMP` | a hex and EBCDIC dump |
| C | `src/mi_fmtdt.c`, `src/mi_fmtnm.c` | `MIFMTDAT`, `MIFMTNUM` | C faces of the COBOL formatters |
| Assembler | `asm/mijobn.asm` | `MIJOBN` | the job name (PSATOLD → TCBTIO → TIOT) |
| Assembler | `asm/mitime.asm` | `MITIME` | `TIME DEC` |
| COBOL | `cobol/mifmtd.cbl` | `MIFMTD` | `0CYYDDDF` → `YYYY.DDD` |
| COBOL | `cobol/mifmtn.cbl` | `MIFMTN` | a number → `ZZZ,ZZZ,ZZ9-`, an edited picture |

C callers include `mvsinfo.h`; COBOL callers `COPY MIPARMS`. Both ship in
the archive's `include/`.

## Who calls whom

C and the rest of MVS pass arguments differently:

- **C** (cc370): register 1 addresses the argument *values*; the last one
  is not marked.
- **COBOL and the OS convention**: register 1 addresses the argument
  *addresses*; the last one has its high-order bit set.

The library bridges them in two ways:

- **The assembler routines take pointers only** and drop the high-order
  bit. A pointer passed by C and an address passed by COBOL are then the
  same thing, so C, COBOL and assembler call `MIJOBN` and `MITIME` alike.
- **The COBOL formatters keep the OS convention**, and C reaches them
  through small wrappers (`mi_fmtdate()`, `mi_fmtnum()`) that pass
  addresses and set the bit on the last one.

C → COBOL, C → assembler, COBOL → assembler, assembler → COBOL and COBOL →
COBOL work as they are. **COBOL → C** does not: C expects its own stack in
the caller's save area, which a COBOL save area does not have. A glue
routine for that is being designed in LIBC/370 (libc370#502).

## Building

You need [MBT](https://github.com/mvslovers/mbt) 3, the CC/370 toolchain
(cc370, with LIBC/370 and maclib370), and
[cobc370](https://github.com/brazilofmux/cobc370) on `PATH` (or named in
`MBT_COBC370`):

```sh
mbt build        # the archive build/mvsinfo.a
mbt test         # the host test of the hex dump
mbt package      # dist/mbt-example-lib-<version>-lib.tar.gz
```

The project file is [`mbt.toml`](mbt.toml). A COBOL source in `sources` is
translated by cobc370 into `build/cobol/<stem>.asm` and assembled like any
other assembler source; `[build] cobflags` tells cobc370 where `COPY`
finds its copybooks.
