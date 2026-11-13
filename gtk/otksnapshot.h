/* OTK - The Ocimum Toolkit
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */
#ifndef __OTK_SNAPSHOT_H__
#define __OTK_SNAPSHOT_H__

#if !defined (__GTK_H_INSIDE__) && !defined (GTK_COMPILATION)
#error "Only <gtk/gtk.h> can be included directly."
#endif

/* GtkSnapshot, for GtkWidgetClass.snapshot (OTK 2).
 *
 * GtkSnapshot belongs to OSK: widgets that create render nodes include
 * <osk/osk.h> and use pkg-config osk-3.0.  This typedef is the same as OSK's.
 * The header is not introspected; GtkSnapshot is Osk.Snapshot. */
#ifndef __OSK_GTK_SNAPSHOT_TYPEDEF__
#define __OSK_GTK_SNAPSHOT_TYPEDEF__
typedef struct _GdkSnapshot GtkSnapshot;
#endif

#endif /* __OTK_SNAPSHOT_H__ */
