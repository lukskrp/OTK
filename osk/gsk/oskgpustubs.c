/* OSK - the Ocimum Scene Kit
 *
 * Until the GPU renderer is imported (OTK milestone 3c) the render nodes'
 * occlusion hooks, which only the GPU renderer calls, link against these.
 * gsk/gpu/gskgpuocclusionprivate.h declares them as GTK 4 does.
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

#include "config.h"

#include "gpu/gskgpuocclusionprivate.h"
#include "gpu/gskgpuframeprivate.h"
#include "gpu/gskgpurenderpassprivate.h"

void
gsk_gpu_render_pass_set_transform (GskGpuRenderPass *self,
                                   GskGpuTransform  *transform)
{
  g_return_if_reached ();
}

GdkDrawContext *
gsk_gpu_frame_get_context (GskGpuFrame *self)
{
  g_return_val_if_reached (NULL);
}

GdkSurface *
gdk_draw_context_get_surface (GdkDrawContext *context)
{
  g_return_val_if_reached (NULL);
}

GskGpuFrame *
gsk_gpu_occlusion_get_frame (GskGpuOcclusion *self)
{
  g_return_val_if_reached (NULL);
}

gboolean
gsk_gpu_occlusion_push_clip (GskGpuOcclusion       *self,
                             const graphene_rect_t *clip,
                             GskRectSnap            snap,
                             cairo_rectangle_int_t *out_save)
{
  g_return_val_if_reached (FALSE);
}

void
gsk_gpu_occlusion_pop_clip (GskGpuOcclusion             *self,
                            const cairo_rectangle_int_t *saved)
{
  g_return_if_reached ();
}

gboolean
gsk_gpu_occlusion_push_transform (GskGpuOcclusion *self,
                                  GskTransform    *transform,
                                  GskGpuTransform *out_save)
{
  g_return_val_if_reached (FALSE);
}

void
gsk_gpu_occlusion_pop_transform (GskGpuOcclusion       *self,
                                 const GskGpuTransform *saved)
{
  g_return_if_reached ();
}

GskGpuRenderPass *
gsk_gpu_occlusion_begin_rendering_whatever (GskGpuOcclusion *self)
{
  g_return_val_if_reached (NULL);
}

GskGpuRenderPass *
gsk_gpu_occlusion_begin_rendering_transparent (GskGpuOcclusion *self)
{
  g_return_val_if_reached (NULL);
}

GskGpuRenderPass *
gsk_gpu_occlusion_begin_rendering_color (GskGpuOcclusion *self,
                                         const GdkColor  *color)
{
  g_return_val_if_reached (NULL);
}

GskGpuRenderPass *
gsk_gpu_occlusion_try_node (GskGpuOcclusion *self,
                            GskRenderNode   *node,
                            gsize            pos)
{
  g_return_val_if_reached (NULL);
}

GskGpuRenderPass *
gsk_gpu_occlusion_try_node_untracked (GskGpuOcclusion *self,
                                      GskRenderNode   *node)
{
  g_return_val_if_reached (NULL);
}

GskGpuRenderPass *
gsk_container_node_occlusion (GskRenderNode   *node,
                              GskGpuOcclusion *occlusion)
{
  g_return_val_if_reached (NULL);
}

GskGpuRenderPass *
gsk_render_node_default_occlusion (GskRenderNode   *self,
                                   GskGpuOcclusion *occlusion)
{
  return NULL;
}
