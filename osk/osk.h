/* OSK - the Ocimum Scene Kit
 *
 * GTK 4's rendering engine (GSK render nodes, transforms, paths, renderers,
 * GdkTexture, GdkPaintable and GtkSnapshot) as an OTK module.  The C API keeps GTK 4's
 * gsk_* and gdk_texture_* names, so GTK 4 rendering code ports with few edits.
 *
 * Include this header and use pkg-config osk-3.0.
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

#pragma once

#define __OSK_H_INSIDE__

#include <gdk/oskgdk.h>
#include <gsk/gsk.h>
#include <gtk/gtksnapshot.h>

/* The error domains of gsk_render_node_deserialize() */
#include <gtk/css/gtkcss.h>

/* 1: OSK core (render nodes, textures, Cairo renderer)
 * 2: GtkSnapshot; osk_set_snapshot_funcs() removed (libotk no longer needs it) */
#define OSK_API_VERSION 2

#undef __OSK_H_INSIDE__
