/* OSK - the Ocimum Scene Kit
 *
 * Stand-in for GTK 4's gskgpurenderpassprivate.h until the GPU renderer is
 * imported (OTK milestone 3c): only what the render nodes' occlusion hooks use.
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */
#pragma once

#include "gskgputypesprivate.h"
#include "gskgputransformprivate.h"

void gsk_gpu_render_pass_set_transform (GskGpuRenderPass *self,
                                        GskGpuTransform  *transform);
