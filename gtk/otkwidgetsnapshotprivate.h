/* OTK - The Ocimum Toolkit
 *
 * Between gtkwidget.c and otkwidgetsnapshot.c (GtkWidgetClass.snapshot).
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */
#pragma once

#include "gtkwidget.h"

G_BEGIN_DECLS

/* Sets the default GtkWidgetClass.snapshot (a cairo node drawn with ::draw) */
void            _otk_widget_class_init_snapshot (GtkWidgetClass       *klass);

#ifdef OTK_HAVE_OSK
/* TRUE if @widget's class implements GtkWidgetClass.snapshot itself */
gboolean        _otk_widget_has_snapshot        (GtkWidget            *widget);
/* Draws @widget's render nodes to @cr (the legacy renderer) */
void            _otk_widget_draw_snapshot       (GtkWidget            *widget,
                                                 cairo_t              *cr);
/* TRUE if OTK_RENDERER renders @window of @widget through OSK */
gboolean        _otk_widget_wants_gsk_render    (GtkWidget            *widget,
                                                 GdkWindow            *window);
/* Renders @widget into @window through OSK; FALSE if that is not possible */
gboolean        _otk_widget_render              (GtkWidget            *widget,
                                                 GdkWindow            *window,
                                                 const cairo_region_t *region,
                                                 int                   x,
                                                 int                   y);
void            _otk_widget_unrealize_renderer  (GtkWidget            *widget);
#endif

G_END_DECLS
