/* OSK - the Ocimum Scene Kit
 *
 * GtkSnapshot is OTK's (libotk).  GdkTexture and GdkPaintable call into it
 * through these functions, which libotk registers when it loads.
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */
#pragma once

#include "gdktypes.h"

G_BEGIN_DECLS

typedef struct _OskSnapshotFuncs OskSnapshotFuncs;

struct _OskSnapshotFuncs
{
  GdkSnapshot *  (* snapshot_new)          (void);
  GdkPaintable * (* free_to_paintable)     (GdkSnapshot           *snapshot,
                                            const graphene_size_t *size);
  void           (* append_texture)        (GdkSnapshot           *snapshot,
                                            GdkTexture            *texture,
                                            const graphene_rect_t *bounds);
  void           (* push_debug)            (GdkSnapshot           *snapshot,
                                            const char            *message);
  void           (* pop)                   (GdkSnapshot           *snapshot);
};

OSK_AVAILABLE_IN_ALL
void            osk_set_snapshot_funcs     (const OskSnapshotFuncs *funcs);

G_END_DECLS
