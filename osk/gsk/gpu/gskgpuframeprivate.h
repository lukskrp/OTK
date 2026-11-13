/* OSK - the Ocimum Scene Kit
 *
 * Stand-in for GTK 4's gskgpuframeprivate.h until the GPU renderer is
 * imported (OTK milestone 3c).
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */
#pragma once

#include "gskgputypesprivate.h"

typedef struct _GdkDrawContext GdkDrawContext;

GdkDrawContext * gsk_gpu_frame_get_context    (GskGpuFrame    *self);
GdkSurface *     gdk_draw_context_get_surface (GdkDrawContext *context);
