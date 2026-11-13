/* OSK - the Ocimum Scene Kit
 *
 * The GdkDmabuf description from GTK 4's gdkdmabufprivate.h.  OSK builds
 * without dmabuf textures (no HAVE_DMABUF) until the GL renderer; the .node
 * parser then loads "dmabuf" textures as memory textures.
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */
#pragma once

#include "gdkmemorylayoutprivate.h"

#define GDK_DMABUF_MAX_PLANES 4

typedef struct _GdkDmabuf GdkDmabuf;

struct _GdkDmabuf
{
  guint32 fourcc;
  guint64 modifier;
  unsigned int n_planes;
  struct {
    int fd;
    unsigned int stride;
    unsigned int offset;
  } planes[GDK_DMABUF_MAX_PLANES];
};

gboolean gdk_memory_layout_init_from_dmabuf (GdkMemoryLayout *self,
                                             const GdkDmabuf *dmabuf,
                                             gboolean         premultiplied,
                                             gsize            width,
                                             gsize            height);
