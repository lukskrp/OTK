/* OSK - the Ocimum Scene Kit
 *
 * See osksnapshot.h.
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */
#include "config.h"

#include "osksnapshot.h"
#include "gdkpaintable.h"

#include <stdarg.h>

static const OskSnapshotFuncs *snapshot_funcs;

/**
 * osk_set_snapshot_funcs: (skip)
 * @funcs: the snapshot implementation; must stay valid
 *
 * Called by libotk to provide GtkSnapshot to GdkTexture and GdkPaintable.
 */
void
osk_set_snapshot_funcs (const OskSnapshotFuncs *funcs)
{
  snapshot_funcs = funcs;
}

/* The gtk_snapshot_*() calls of GTK 4's gdk/ code (internal to libosk) */

GdkSnapshot *   gtk_snapshot_new                (void);
GdkPaintable *  gtk_snapshot_free_to_paintable  (GdkSnapshot           *snapshot,
                                                 const graphene_size_t *size);
void            gtk_snapshot_append_texture     (GdkSnapshot           *snapshot,
                                                 GdkTexture            *texture,
                                                 const graphene_rect_t *bounds);
void            gtk_snapshot_push_debug         (GdkSnapshot           *snapshot,
                                                 const char            *message,
                                                 ...) G_GNUC_PRINTF (2, 3);
void            gtk_snapshot_pop                (GdkSnapshot           *snapshot);

GdkSnapshot *
gtk_snapshot_new (void)
{
  g_return_val_if_fail (snapshot_funcs != NULL, NULL);

  return snapshot_funcs->snapshot_new ();
}

GdkPaintable *
gtk_snapshot_free_to_paintable (GdkSnapshot           *snapshot,
                                const graphene_size_t *size)
{
  g_return_val_if_fail (snapshot_funcs != NULL, NULL);

  return snapshot_funcs->free_to_paintable (snapshot, size);
}

void
gtk_snapshot_append_texture (GdkSnapshot           *snapshot,
                             GdkTexture            *texture,
                             const graphene_rect_t *bounds)
{
  g_return_if_fail (snapshot_funcs != NULL);

  snapshot_funcs->append_texture (snapshot, texture, bounds);
}

void
gtk_snapshot_push_debug (GdkSnapshot *snapshot,
                         const char  *message,
                         ...)
{
  va_list args;
  char *str;

  g_return_if_fail (snapshot_funcs != NULL);

  va_start (args, message);
  str = g_strdup_vprintf (message, args);
  va_end (args);

  snapshot_funcs->push_debug (snapshot, str);
  g_free (str);
}

void
gtk_snapshot_pop (GdkSnapshot *snapshot)
{
  g_return_if_fail (snapshot_funcs != NULL);

  snapshot_funcs->pop (snapshot);
}
