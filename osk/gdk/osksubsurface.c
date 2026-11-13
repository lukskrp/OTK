/* OSK - the Ocimum Scene Kit
 *
 * See gdksubsurfaceprivate.h: OSK has no subsurfaces on X11.
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */
#include "config.h"

#include "gdksubsurfaceprivate.h"

G_DEFINE_TYPE (GdkSubsurface, gdk_subsurface, G_TYPE_OBJECT)

static void
gdk_subsurface_class_init (GdkSubsurfaceClass *class)
{
}

static void
gdk_subsurface_init (GdkSubsurface *self)
{
}

GdkSurface *
gdk_subsurface_get_parent (GdkSubsurface *subsurface)
{
  return subsurface->parent;
}

void
gdk_subsurface_detach (GdkSubsurface *subsurface)
{
}

GdkTexture *
gdk_subsurface_get_texture (GdkSubsurface *subsurface)
{
  return NULL;
}

gboolean
gdk_subsurface_is_above_parent (GdkSubsurface *subsurface)
{
  return TRUE;
}

gboolean
gdk_subsurface_get_background_rect (GdkSubsurface   *subsurface,
                                    graphene_rect_t *rect)
{
  return FALSE;
}

void
gdk_subsurface_get_bounds (GdkSubsurface   *subsurface,
                           graphene_rect_t *bounds)
{
  graphene_rect_init (bounds, 0, 0, 0, 0);
}
