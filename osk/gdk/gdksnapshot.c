/*
 * Copyright © 2018 Benjamin Otte
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors: Benjamin Otte <otte@gnome.org>
 */

#include "config.h"

#include "gdksnapshotprivate.h"

/**
 * GdkSnapshot:
 *
 * Base type for snapshot operations.
 *
 * The subclass of `GdkSnapshot` used by GTK is [GtkSnapshot](../gtk4/class.Snapshot.html).
 */

/* OSK: one type with GtkSnapshot (see gtk/gtksnapshot.c) */
GType gtk_snapshot_get_type (void);

GType
gdk_snapshot_get_type (void)
{
  return gtk_snapshot_get_type ();
}
