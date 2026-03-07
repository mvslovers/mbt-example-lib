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
cp .env.example .env        # edit with your MVS connection
make bootstrap               # download crent370 dependency
make build                   # cross-compile and assemble on MVS
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

Regardless of autocall, every exported function needs an `asm()`
directive in its header to control the external symbol name. MVS
member names are limited to 8 uppercase characters:

```c
/* autocall-compatible: symbol == member name */
void hexdump(const void *addr, unsigned len) asm("HEXDUMP");

/* non-autocall: symbol != member name, but asm() is still needed
   to produce a valid 8-char MVS external name */
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
