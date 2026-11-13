/* OSK - the Ocimum Scene Kit
 *
 * OSK renders into ODK windows: GTK 4's GdkSurface is ODK's GdkWindow
 * (see gdktypes.h).  These are the GdkSurface calls GSK makes, so GTK 4
 * rendering code that uses them builds against OSK unchanged.
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */
#pragma once

#include "gdktypes.h"

G_BEGIN_DECLS

#define GDK_TYPE_SURFACE GDK_TYPE_WINDOW
#define GDK_SURFACE(o)   GDK_WINDOW(o)
#define GDK_IS_SURFACE(o) GDK_IS_WINDOW(o)

static inline GdkDisplay *
gdk_surface_get_display (GdkSurface *surface)
{
  return gdk_window_get_display (surface);
}

static inline int
gdk_surface_get_width (GdkSurface *surface)
{
  return gdk_window_get_width (surface);
}

static inline int
gdk_surface_get_height (GdkSurface *surface)
{
  return gdk_window_get_height (surface);
}

static inline int
gdk_surface_get_scale_factor (GdkSurface *surface)
{
  return gdk_window_get_scale_factor (surface);
}

G_END_DECLS
