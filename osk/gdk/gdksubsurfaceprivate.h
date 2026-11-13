/* OSK - the Ocimum Scene Kit
 *
 * GTK 4's GdkSubsurface (Wayland offloading) has no X11 counterpart: on XLibre
 * OSK never creates subsurfaces, so a GskSubsurfaceNode only draws its child.
 * The type and accessors exist so GSK's code builds unchanged
 * (gdk/osksubsurface.c).
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */
#pragma once

#include "gdktypes.h"
#include "gdkdihedralprivate.h"

G_BEGIN_DECLS

GDK_DECLARE_INTERNAL_TYPE (GdkSubsurface, gdk_subsurface, GDK, SUBSURFACE, GObject)

struct _GdkSubsurface
{
  GObject parent_instance;

  GdkSurface *parent;
};

struct _GdkSubsurfaceClass
{
  GObjectClass parent_class;
};

GdkSurface *    gdk_subsurface_get_parent          (GdkSubsurface         *subsurface);
void            gdk_subsurface_detach              (GdkSubsurface         *subsurface);
GdkTexture *    gdk_subsurface_get_texture         (GdkSubsurface         *subsurface);
gboolean        gdk_subsurface_is_above_parent     (GdkSubsurface         *subsurface);
gboolean        gdk_subsurface_get_background_rect (GdkSubsurface         *subsurface,
                                                    graphene_rect_t       *rect);
void            gdk_subsurface_get_bounds          (GdkSubsurface         *subsurface,
                                                    graphene_rect_t       *bounds);

G_END_DECLS
