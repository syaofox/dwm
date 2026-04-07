# dwm - Dynamic Window Manager

https://dwm.suckless.org/ | Version: 6.8

## Build & Install

```
make clean install    # may need sudo for /usr/local
make clean            # remove binaries and objects
make dist             # create release tarball
```

- Requires: Xlib headers, Xinerama, fontconfig, libXft
- `config.h` is auto-copied from `config.def.h` on first build. Edit `config.def.h` then `rm config.h` to regenerate.

## Configuration Model

- **All config is compile-time.** Edit `config.def.h`, recompile, restart dwm.
- Key bindings in `keys[]` array. `MODKEY = Mod1Mask` (Alt by default).
- Colors in `colors[][3]` array: `[SchemeNorm]` and `[SchemeSel]`, each with `[fg, bg, border]`.
- Window rules in `rules[]` array: match by WM_CLASS/WM_NAME, set tags, floating, monitor.
- Layouts: `tile` (default), `monocle`, floating (`NULL` arrange func).
- Status bar text comes from `xsetroot -name`. Run a loop in `.xinitrc` to update it.

## Source Structure

| File    | Purpose |
|---------|---------|
| `dwm.c` | Core WM logic (entry point, event loop, layout, key handling) |
| `drw.c` | Drawing library (bar rendering, fonts via Xft) |
| `util.c` | Misc helpers (die, ecalloc, etc.) |
| `config.def.h` | Default configuration template |
| `config.mk` | Build settings (PREFIX, CC, CFLAGS, libs) |
| `transient.c` | Example transient window client |

## Conventions

- Patches from suckless.org are applied as diffs against `dwm.c`. Apply carefully; conflicts are common.
- No runtime config, no tests, no CI. Verification is manual: build, run in X session, test keybindings.
- `CFLAGS` uses `-Os` (optimize for size) by default. Debug builds: uncomment the `-g -O0` line in `config.mk`.
