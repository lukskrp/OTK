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
| Libraries | `libgtk-3.so.0`, `libgdk-3.so.0`, `libgailutil-3.so.0` | `libotk-3.so.1`, `libodk-3.so.0`, `libotk-gailutil-3.so.0`, `libosk-3.so.0` |
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

## Beyond GTK 3

API that OTK adds. It is marked `GDK_AVAILABLE_IN_OTK_<n>` in the headers and documented
"Since: OTK <n>". Code that also builds against stock GTK 3 can test `#ifdef OTK_API_VERSION`
(`OTK_API_VERSION >= 2` for widget snapshots).

| Since | API | What it does |
|---|---|---|
| OTK 1 | `gdk_display_get_monitors()` | The display's monitors as a `GListModel` of `GdkMonitor`; emits `items-changed` when a monitor is added or removed, after its properties are set |
| OTK 1 | `gdk_monitor_get_connector()`, `GdkMonitor:connector` | Connector name, such as `DP-1` (RandR monitor or output name on X11) |
| OTK 1 | `gdk_monitor_get_scale()`, `GdkMonitor:scale` | Scale from logical to device pixels as a `double`; equals the scale factor until a backend reports fractional scales |
| OTK 1 | `g_autoptr()` for `GdkMonitor`, `GdkSeat`, `GdkDeviceTool`, `GdkDrawingContext` | Automatic cleanup, as for the other GDK objects |
| OTK 1 | `gtk_disable_portals()` | Call before `gtk_init()`: OTK makes no `org.freedesktop.portal.*` calls (dialogs, inhibit, file transfer, app registration, settings), overriding `GTK_USE_PORTAL` |
| OTK 2 | `GtkWidgetClass.snapshot`, `gtk_widget_snapshot()`, `gtk_widget_snapshot_child()` | Widgets that draw with OSK render nodes; see [Widgets with render nodes](#widgets-with-render-nodes) |
| OTK 2 | `OTK_RENDERER=legacy\|cairo\|gl` | How windows reach the screen; see below |

These follow the GTK 4 API of the same name, so code moving from GTK 4 keeps working.

## Widgets with render nodes

Since OTK 2 a widget class can implement `GtkWidgetClass.snapshot` instead of `::draw`,
and describe its contents as OSK render nodes (GTK 4's model). This changed the layout
of `GtkWidgetClass`, so `libotk-3` is `.so.1` from OTK 2 on.

```c
#include <gtk/gtk.h>
#include <osk/osk.h>          /* GtkSnapshot; pkg-config osk-3.0 */

static void
my_widget_snapshot (GtkWidget *widget, GtkSnapshot *snapshot)
{
  int width = gtk_widget_get_allocated_width (widget);
  int height = gtk_widget_get_allocated_height (widget);

  gtk_snapshot_append_color (snapshot, &(GdkRGBA) { 0.2, 0.5, 0.3, 1 },
                             &GRAPHENE_RECT_INIT (0, 0, width, height));
  /* a container adds its children with gtk_widget_snapshot_child (widget, child, snapshot) */
}
```

In Python, override `do_snapshot(self, snapshot)`; `snapshot` is an `Osk.Snapshot`.

- A widget whose class implements `snapshot` is drawn from its nodes everywhere, also by
  `gtk_widget_draw()` and the legacy renderer, and `::draw` is not emitted for it.
- Every other widget keeps drawing with `::draw`. When something snapshots it, it becomes
  a cairo node in which it draws itself and its children; `gtk_widget_snapshot()` works
  on any widget.
- `gtk_widget_set_opacity()` applies as before.

`OTK_RENDERER` chooses how windows reach the screen:

| Value | |
|---|---|
| `legacy` (default) | GTK 3's path: each window is drawn with cairo through `::draw` |
| `cairo` | Each toplevel is snapshotted into a render-node tree and painted by OSK's Cairo renderer |
| `gl` | OSK's GL renderer, once it exists (stage 3); until then the same as `cairo` |

Both give the same pixels for today's widgets; `cairo` is the path that render-node
widgets and the coming GL renderer build on. `GtkGLArea` is best used with `legacy` until
the GL renderer arrives.

## OSK, the Ocimum Scene Kit

OSK is GTK 4's rendering engine as a separate OTK library, `libosk-3`. It is OTK's own
copy of that engine, so TulsiOS can tune and extend it. It is built from GTK 4.24.0's
`gsk/` and the GTK 4 GDK types it uses; `osk/UPSTREAM` lists the files and how to merge
a newer GTK.

| | |
|---|---|
| Library | `libosk-3.so.0` (links `libodk-3`; does not need `libotk-3`) |
| pkg-config | `osk-3.0` |
| Header | `#include <osk/osk.h>` |
| Introspection | `Osk-3.0` (`Osk.RenderNode`, `Osk.Snapshot`, `Osk.CairoRenderer`, `Osk.Texture`, …) |
| Build option | `-Dosk=auto\|enabled\|disabled`; needs graphene, libpng, libtiff, libjpeg, harfbuzz-subset |

What it provides, under GTK 4's names so GTK 4 rendering code ports with few edits:

- **Render nodes** (`GskRenderNode` and all node types), `GskTransform`, `GskPath`,
  `GskStroke`, `GskRoundedRect`, and the `.node` text format
  (`gsk_render_node_serialize()` / `_deserialize()`), including fonts embedded in it.
- **Renderers**: `GskCairoRenderer`. `gsk_renderer_render_texture()` needs no window.
  `gsk_renderer_realize()` takes an ODK `GdkWindow` (OSK's `GdkSurface` is a `GdkWindow`),
  and `gsk_renderer_render()` paints into it. `GSK_RENDERER` selects the renderer as in
  GTK 4. The GL renderer is not there yet; `GSK_RENDERER=gl` falls back to Cairo with a
  warning.
- **Textures and paintables**: `GdkTexture`, `GdkMemoryTexture` (+ builder),
  `GdkTextureDownloader`, `GdkColorState`, `GdkCicpParams`, `GdkPaintable`; loading and
  saving PNG, TIFF and JPEG.
- **`GtkSnapshot`**, for building node trees (and for `GtkWidgetClass.snapshot`):
  transforms, clips, opacity, blurs, shadows, masks, gradients, text from a
  `PangoLayout` (`gtk_snapshot_append_layout()`), cairo nodes, and
  `gtk_snapshot_to_paintable()`.

Differences from GTK 4:

- `GdkRGBA` is ODK's, with `double` components (GTK 4: `float`). The API is the same;
  code that casts a `GdkRGBA *` to `float *` must copy instead.
- No subsurfaces (Wayland offloading) and no dmabuf textures yet.
- `GdkSnapshot` and `GtkSnapshot` are one type (`Osk.Snapshot`). GTK 4 keeps them apart
  only so that GDK does not depend on GTK; OSK has both in one library.
- Text appended with `gtk_snapshot_append_layout()` uses the layout's own attributes;
  GTK 4's text-view colours and CSS text shadows are not part of OSK.

The stages: (1) this core and the Cairo renderer — done; (2) `GtkSnapshot` and the widget
`snapshot` vfunc, with `OTK_RENDERER` — done; (3) GSK's GL renderer on X11; (4) Vulkan,
widgets moving from `::draw` to `snapshot`, and TulsiOS's own tuning.

Tests: GTK 4's GSK suite (`osk/testsuite`, from `testsuite/gsk`) runs against OSK with
the Cairo renderer: render-node comparisons in all variants (including `replay`, which
rebuilds every node through `GtkSnapshot`), `.node` parser and serializer tests:
`meson test --suite osk --no-suite failing`. Widget snapshots run under X11 with both
renderers: `meson test --suite otk-snapshot`.

## The ABI policy

OTK may change anything GTK 3 promised stays stable: struct layouts, signatures,
enum values, removed symbols. Every such change bumps the OTK version, and the
soname of the library it changes. Applications are always rebuilt against the OTK
they ship with, which tulsipkgs guarantees.

| OTK API | ABI change | Library |
|---|---|---|
| 2 | `GtkWidgetClass` gained `snapshot` | `libotk-3.so.1` |

## Branches

| Branch | Contents |
|---|---|
| `main` | OTK development |
| `gtk-3-24` | Upstream GTK 3.24, unmodified. Merge it into `main` to take upstream fixes: `git merge gtk-3-24`. |

## License

LGPL-2.1-or-later, like GTK (see COPYING).
