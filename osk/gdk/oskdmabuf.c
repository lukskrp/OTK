/* OSK - the Ocimum Scene Kit
 *
 * From GTK 4's gdk/gdkdmabuf.c: the memory layout of a linear dmabuf, which the
 * .node parser uses for "dmabuf" textures loaded as memory textures.
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */
#include "config.h"

#include "gdkdmabufprivate.h"
#include "gdkdmabuffourccprivate.h"
#include "gdkmemoryformatprivate.h"

gboolean
gdk_memory_layout_init_from_dmabuf (GdkMemoryLayout *self,
                                    const GdkDmabuf *dmabuf,
                                    gboolean         premultiplied,
                                    gsize            width,
                                    gsize            height)
{
  gboolean is_yuv;
  gsize i;

  if (dmabuf->modifier != DRM_FORMAT_MOD_LINEAR)
    return FALSE;

  if (!gdk_memory_format_find_by_dmabuf_fourcc (dmabuf->fourcc, premultiplied, &self->format, &is_yuv))
    return FALSE;

  if (!gdk_memory_format_is_block_boundary (self->format, width, height))
    return FALSE;

  g_return_val_if_fail (dmabuf->n_planes == gdk_memory_format_get_n_planes (self->format), FALSE);

  self->width = width;
  self->height = height;

  for (i = 0; i < dmabuf->n_planes; i++)
    {
      self->planes[i].offset = dmabuf->planes[i].offset;
      self->planes[i].stride = dmabuf->planes[i].stride;
    }

  self->size = self->planes[dmabuf->n_planes - 1].offset + 
               (self->height - 1) / gdk_memory_format_get_plane_block_height (self->format, dmabuf->n_planes - 1)
                                  * self->planes[dmabuf->n_planes - 1].stride +
               self->width / gdk_memory_format_get_plane_block_width (self->format, dmabuf->n_planes - 1)
                           * gdk_memory_format_get_plane_block_bytes (self->format, dmabuf->n_planes - 1);

  return TRUE;
}
