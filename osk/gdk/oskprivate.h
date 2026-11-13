/* OSK - the Ocimum Scene Kit
 *
 * The parts of GTK 4's gdk/gdkprivate.h the rendering engine uses.
 * GTK 4's gdkprivate.h is not imported: ODK has its own of that name.
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

#pragma once

#include "gdktypes.h"
#include "gdkdebugprivate.h"

G_BEGIN_DECLS

/* Translations: OSK's strings are few; they go through GLib's gettext domain
 * handling like GTK 4's do. */
#include <glib/gi18n-lib.h>

#define I_(string) g_intern_static_string (string)

G_END_DECLS
