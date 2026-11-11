# OTK, the Ocimum Toolkit

OTK is the GUI toolkit of [TulsiOS](https://github.com/lukskrp/tulsipkgs) and its desktop,
[Ocimum Desktop](https://github.com/lukskrp/ocimum-desktop). It is a fork of GTK 3.24 that
is **allowed to break GTK 3's binary interface (ABI)** to gain extra GUI options and
agentic, CLI-driven control.

Its ABI-compatible sibling is GTK3-O, which is grafted under every GTK 3 app in TulsiOS.
OTK is for applications that are built against it on purpose.

## Side by side with GTK 3

OTK never replaces GTK 3. Everything that is ABI-specific has its own name, so both
can be installed together. Stock GTK 3 apps (Firefox, GIMP, …) never load OTK.

| | GTK 3 | OTK |
|---|---|---|
| Libraries | `libgtk-3.so.0`, `libgdk-3.so.0`, `libgailutil-3.so.0` | `libotk-3.so.0`, `libodk-3.so.0`, `libotk-gailutil-3.so.0` |
| pkg-config | `gtk+-3.0`, `gdk-3.0`, `gtk+-x11-3.0`, `gail-3.0`, … | `otk-3.0`, `odk-3.0`, `otk-x11-3.0`, `otk-gail-3.0`, … |
| Headers | `include/gtk-3.0/gtk/gtk.h` | `include/otk-3.0/gtk/gtk.h` (same `#include <gtk/gtk.h>`) |
| Introspection | `Gtk-3.0`, `Gdk-3.0`, `GdkX11-3.0` | `Otk-3.0`, `Odk-3.0`, `OdkX11-3.0` (types are still `Gtk*`) |
| Modules (input methods, print backends) | `lib/gtk-3.0/3.0.0/…` | `lib/otk-3.0/3.0.0/…` |
| Input method cache | `GTK_IM_MODULE_FILE`, `etc/gtk-3.0/immodules.cache` | `OTK_IM_MODULE_FILE`, `etc/otk-3.0/immodules.cache` |
| GSettings schemas | `org.gtk.Settings.*` | `org.otk.Settings.*` (OTK can add its own keys) |
| Data, compose cache | `share/gtk-3.0`, `~/.cache/gtk-3.0` | `share/otk-3.0`, `~/.cache/otk-3.0` |
| Translations | `gtk30`, `gtk30-properties` | `otk30`, `otk30-properties` |
| Tools | `gtk-builder-tool`, `gtk-launch`, … | `otk-builder-tool`, `otk-launch`, … |

**Deliberately shared**, so OTK apps look and behave like the rest of the desktop:
themes (`share/themes/<name>/gtk-3.0/`), `settings.ini`, bookmarks and other files in
`~/.config/gtk-3.0`, and environment variables such as `GTK_THEME`, `GDK_SCALE`,
`GDK_BACKEND`. `GTK_PATH` is shared too, but OTK only looks under `otk-3.0` inside it,
so it can't pick up GTK 3's modules.

One rule: **one toolkit per process.** A program loads either GTK 3 or OTK, never both,
because the C type names (`GtkWidget`, …) are the same.

## Porting an application to OTK

The API starts out identical to GTK 3.24.

- **C / meson**: `dependency('otk-3.0')` instead of `dependency('gtk+-3.0')`. Sources are unchanged.
- **Python (PyGObject)**:
  ```python
  gi.require_version("Otk", "3.0")
  from gi.repository import Otk as Gtk
  Gtk.init(None)
  ```
  PyGObject's Python-side conveniences for `Gtk` (overrides) don't apply to `Otk` yet,
  including the automatic initialization on import, so call `Gtk.init(None)` yourself
  before creating any widget. The plain GObject API works.

## The ABI policy

OTK may change anything GTK 3 promised stays stable: struct layouts, signatures,
enum values, removed symbols. Every such change bumps the OTK version. Applications
are always rebuilt against the OTK they ship with, which tulsipkgs guarantees.

## Branches

| Branch | Contents |
|---|---|
| `main` | OTK development |
| `gtk-3-24` | Upstream GTK 3.24, unmodified. Merge it into `main` to take upstream fixes: `git merge gtk-3-24`. |

## License

LGPL-2.1-or-later, like GTK (see COPYING).
