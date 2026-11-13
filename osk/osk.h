/* OSK - the Ocimum Scene Kit
 *
 * GTK 4's rendering engine (GSK render nodes, transforms, paths, renderers,
 * GdkTexture and GdkPaintable) as an OTK module.  The C API keeps GTK 4's
 * gsk_* and gdk_texture_* names, so GTK 4 rendering code ports with few edits.
 *
 * Include this header and use pkg-config osk-3.0.
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

#pragma once

#include <gdk/oskgdk.h>
#include <gsk/gsk.h>

/* The error domains of gsk_render_node_deserialize() */
#include <gtk/css/gtkcss.h>

/* The error domains of gsk_render_node_deserialize() */
#include <gtk/css/gtkcss.h>

#define OSK_API_VERSION 1
