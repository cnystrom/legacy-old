# legacy-old

Older and miscellaneous trees from Chris Nystrom's personal source
archive:

- **old/** — a large historical scratch tree (older NIO, nlogin, ssh_lib,
  demos, and other work-in-progress copies)
- **test/**, **test2/** — small socket/buffer test programs
- **scripts/** — build and install helper shell scripts
- **inf/** — leftover packaging notes and an NIO 0.0.1 announcement
  (the original `inf/README` is a directory map for an NIO tree)

## Origin

From Chris Nystrom's personal source archive (the hallie tree), posted
publicly at his request. Years in headers vary; much of the NIO-related
material is 2002–2005.

## License

Mixed. Many files use Chris's GPL or LGPL headers. `inf/COPYING` and a
COPYING under `old/nio.old` are the standard GNU GPL text. Some older
files have no license paragraph.

## Third-party files removed

The same third-party set found in the NIO/d0 trees, in their older
copies under `old/`:

- Todd C. Miller strlcat/strlcpy (not present under these particular
  older paths once omitted elsewhere)
- Bob Pendleton font/text/misc/image files
- Ryan McGuigan SDL_prim
- David Olofson speaker
- Eric S. Raymond playlib
- Sun / Tcl-Tk colors and xcolors
- Sam Lantinga SDL `nio_types.h` copies
- GNU FreeFont documentation directories

Binaries, media, and backup files were stripped.

## Build

These are historical copies, not a single buildable project. `test` and
`test2` are small C programs; they were not the focus of the compile
pass. A hardcoded test-login credential in the older `client.c`, `test1.c`, and `test2.c` copies under `old/` was replaced with the placeholder CHANGEME. Leftover vim swap files were omitted. No other source was modified.
