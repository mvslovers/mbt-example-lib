# mbt-example-lib

Example library for the [mbt](https://github.com/mvslovers/mbt) build system,
demonstrating how to build an MVS 3.8j C library with dependencies,
multiple modules, and proper linker symbol management.

The library provides MVS system information utilities:

| Module | Member | Functions | Description |
|--------|--------|-----------|-------------|
| `hexdump.c` | HEXDUMP | `hexdump()` | Hex + EBCDIC memory dump |
| `sysinfo.c` | SYSINFO | `sysinfo_jobname()`, `sysinfo_sysid()`, `sysinfo_ipldate()` | MVS control block queries |
| `jesinf.c` | JESINF | `jesinf_count()`, `jesinf_list()` | JES2 job queue queries |

## Building

```sh
git clone --recurse-submodules https://github.com/mvslovers/mbt-example-lib.git
cd mbt-example-lib
cp .env.example .env        # enter your MVS connection details (host, port, credentials)
make bootstrap               # download crent370 dependency
make build                   # cross-compile and assemble on MVS
make package                 # package artifacts for local cache
```

## Understanding Autocall

When linking a load module on MVS, the linkage editor (IEWL) resolves
external symbols by searching the SYSLIB concatenation. This mechanism
is called **autocall**: the linker sees an unresolved symbol name, looks
for a PDS member with the same name, and automatically includes it.

This works perfectly when **each object member exports exactly one
function whose name matches the member name**:

```
Member HEXDUMP  →  exports symbol HEXDUMP  →  autocall resolves it ✓
```

It breaks when a member exports **multiple functions** whose names
differ from the member name:

```
Member SYSINFO  →  exports SYSIFJOB, SYSIFSID, SYSIFDTI
                    linker looks for member SYSIFJOB → not found ✗
```

### How mbt Handles This

In `project.toml`, a library declares whether its members follow the
autocall convention:

```toml
[link]
autocall = false    # default is true
```

When `autocall = false`, the consuming application must explicitly list
which members to pull in via `dep_includes`:

```toml
[link.module.dep_includes]
"mvslovers/mbt-example-lib" = "*"           # include all members
# or selectively:
# "mvslovers/mbt-example-lib" = ["SYSINFO", "HEXDUMP"]
```

This generates explicit `INCLUDE` statements in the link JCL, so the
linker pulls in those members regardless of symbol names.

### When to Use Which

| Pattern | `autocall` | Example |
|---------|-----------|---------|
| One function per file, name matches member | `true` (default) | crent370, most system libs |
| Multiple functions per file | `false` | This library, lua370 |
| Mixed (some match, some don't) | `false` | Safe choice — explicit is always correct |

### The `asm()` Directive

MVS member and symbol names are limited to 8 uppercase characters.
The S/370 assembler automatically uppercases all symbols, so a C
function named `hexdump` produces the symbol `HEXDUMP` — no special
handling needed.

The `asm()` directive is only required when the C function name
**exceeds 8 characters** or otherwise wouldn't produce a valid MVS
symbol:

```c
/* autocall-compatible: no asm() needed — hexdump → HEXDUMP */
void hexdump(const void *addr, unsigned len);

/* non-autocall: asm() required — function name > 8 chars */
const char *sysinfo_jobname(void) asm("SYSIFJOB");
const char *sysinfo_sysid(void)   asm("SYSIFSID");
```

Without `asm()`, GCC would emit the full C function name (e.g.
`sysinfo_jobname`), which exceeds the 8-character limit and would be
silently truncated by the assembler — causing link failures.

## Project Structure

```
mbt-example-lib/
├── project.toml          # mbt project definition
├── Makefile              # 2-line mbt include
├── .env.example          # MVS connection template
├── include/              # public headers (shipped in release)
│   ├── hexdump.h
│   ├── sysinfo.h
│   └── jesinf.h
├── src/                  # C sources
│   ├── hexdump.c         # autocall-compatible module
│   ├── sysinfo.c         # non-autocall module
│   └── jesinf.c          # non-autocall module
└── mbt/                  # build system (git submodule)
```

## See Also

- [mbt-example-app](https://github.com/mvslovers/mbt-example-app) — batch
  application that uses this library
- [mbt](https://github.com/mvslovers/mbt) — MVS Build Tools
- [crent370](https://github.com/mvslovers/crent370) — C runtime for MVS 3.8j
