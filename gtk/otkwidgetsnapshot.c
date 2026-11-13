/* OTK - The Ocimum Toolkit
 *
 * GtkWidgetClass.snapshot: widgets drawn with OSK render nodes, and the
 * OTK_RENDERER switch that renders toplevels through OSK.
 *
 * This file is the only part of libotk that sees OSK's headers; gtkwidget.c
 * calls it through otkwidgetsnapshotprivate.h.
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

#include "config.h"

#include "gtkwidgetprivate.h"
#include "otkwidgetsnapshotprivate.h"

#ifdef OTK_HAVE_OSK

#include <osk/osk.h>

typedef enum
{
  OTK_RENDERER_LEGACY,
  OTK_RENDERER_CAIRO,
} OtkRenderer;

static GQuark quark_renderer;

/* OTK_RENDERER, read once:
 *   legacy  every widget draws with cairo through ::draw, as in GTK 3 (default)
 *   cairo   toplevels are snapshotted into render nodes and rendered by OSK's
 *           Cairo renderer
 *   gl      OSK's GL renderer (OTK milestone 3c); until then the same as cairo
 */
static OtkRenderer
otk_get_renderer (void)
{
  static gsize renderer = 0; /* OtkRenderer + 1 */

  if (g_once_init_enter (&renderer))
    {
      const char *env = g_getenv ("OTK_RENDERER");
      gsize value = OTK_RENDERER_LEGACY + 1;

      if (env == NULL || *env == '\0' || g_ascii_strcasecmp (env, "legacy") == 0)
        ;
      else if (g_ascii_strcasecmp (env, "cairo") == 0)
        value = OTK_RENDERER_CAIRO + 1;
      else if (g_ascii_strcasecmp (env, "gl") == 0)
        {
          g_message ("OTK_RENDERER=gl: OSK has no GL renderer yet; using cairo");
          value = OTK_RENDERER_CAIRO + 1;
        }
      else
        g_warning ("Unknown OTK_RENDERER \"%s\" (use legacy, cairo or gl); using legacy", env);

      g_once_init_leave (&renderer, value);
    }

  return (OtkRenderer) (renderer - 1);
}

/* While a toplevel renders, its own fallback node covers only the area being
 * painted, so that cairo drawing outside it is culled as in the legacy path. */
static GtkWidget *paint_clip_widget;
static cairo_rectangle_int_t paint_clip;

/* The default GtkWidgetClass.snapshot: a cairo node in which the widget draws
 * itself (and its children) through ::draw, exactly as gtk_widget_draw(). */
static void
otk_widget_real_snapshot (GtkWidget   *widget,
                          GtkSnapshot *snapshot)
{
  GtkAllocation allocation, clip;
  cairo_rectangle_int_t area;
  cairo_t *cr;

  _gtk_widget_get_allocation (widget, &allocation);
  gtk_widget_get_clip (widget, &clip);

  area.x = clip.x - allocation.x;
  area.y = clip.y - allocation.y;
  area.width = clip.width;
  area.height = clip.height;

  if (widget == paint_clip_widget &&
      !gdk_rectangle_intersect (&area, &paint_clip, &area))
    return;

  if (area.width <= 0 || area.height <= 0)
    return;

  cr = gtk_snapshot_append_cairo (snapshot,
                                  &GRAPHENE_RECT_INIT (area.x, area.y, area.width, area.height));
  gtk_widget_draw (widget, cr);
  cairo_destroy (cr);
}

void
_otk_widget_class_init_snapshot (GtkWidgetClass *klass)
{
  if (quark_renderer == 0)
    quark_renderer = g_quark_from_static_string ("otk-widget-renderer");

  klass->snapshot = otk_widget_real_snapshot;
}

gboolean
_otk_widget_has_snapshot (GtkWidget *widget)
{
  GtkWidgetClass *klass = GTK_WIDGET_GET_CLASS (widget);

  return klass->snapshot != NULL && klass->snapshot != otk_widget_real_snapshot;
}

void
_otk_widget_draw_snapshot (GtkWidget *widget,
                           cairo_t   *cr)
{
  GtkSnapshot *snapshot;
  GskRenderNode *node;

  snapshot = gtk_snapshot_new ();
  GTK_WIDGET_GET_CLASS (widget)->snapshot (widget, snapshot);
  node = gtk_snapshot_free_to_node (snapshot);

  if (node != NULL)
    {
      cairo_save (cr);
      gsk_render_node_draw (node, cr);
      cairo_restore (cr);
      gsk_render_node_unref (node);
    }
}

static gboolean
otk_widget_uses_group_opacity (GtkWidget *widget)
{
  /* As gtk_widget_draw_internal(): a toplevel without an RGBA visual gets its
   * opacity from the window manager. */
  return widget->priv->alpha != 255 &&
         (!_gtk_widget_is_toplevel (widget) ||
          gtk_widget_get_visual (widget) == gdk_screen_get_rgba_visual (gtk_widget_get_screen (widget)));
}

/**
 * gtk_widget_snapshot:
 * @widget: a #GtkWidget
 * @snapshot: the #GtkSnapshot to append @widget's render nodes to
 *
 * Appends the render nodes of @widget, at the current origin of @snapshot.
 *
 * Widgets that implement #GtkWidgetClass.snapshot add their nodes; the others
 * are drawn into a cairo node through #GtkWidget::draw, together with their
 * children. Nothing is added for a widget that is not drawable.
 *
 * Since: OTK 2
 */
void
gtk_widget_snapshot (GtkWidget   *widget,
                     GtkSnapshot *snapshot)
{
  GtkWidgetClass *klass;
  gboolean opacity;

  g_return_if_fail (GTK_IS_WIDGET (widget));
  g_return_if_fail (snapshot != NULL);

  if (!_gtk_widget_is_drawable (widget))
    return;

  klass = GTK_WIDGET_GET_CLASS (widget);
  if (klass->snapshot == NULL)
    return;

  /* the fallback applies the opacity itself, through gtk_widget_draw() */
  opacity = klass->snapshot != otk_widget_real_snapshot &&
            otk_widget_uses_group_opacity (widget);

  if (opacity)
    gtk_snapshot_push_opacity (snapshot, widget->priv->alpha / 255.0);

  klass->snapshot (widget, snapshot);

  if (opacity)
    gtk_snapshot_pop (snapshot);
}

/**
 * gtk_widget_snapshot_child:
 * @widget: a #GtkWidget
 * @child: a child of @widget
 * @snapshot: the #GtkSnapshot passed to @widget's #GtkWidgetClass.snapshot
 *
 * Appends the render nodes of @child, at its position in @widget.
 *
 * A widget that implements #GtkWidgetClass.snapshot calls this for each child
 * it shows; it is the snapshot counterpart of gtk_container_propagate_draw().
 *
 * Since: OTK 2
 */
void
gtk_widget_snapshot_child (GtkWidget   *widget,
                           GtkWidget   *child,
                           GtkSnapshot *snapshot)
{
  GtkAllocation allocation;
  GdkWindow *window, *w;
  int x, y;

  g_return_if_fail (GTK_IS_WIDGET (widget));
  g_return_if_fail (GTK_IS_WIDGET (child));
  g_return_if_fail (_gtk_widget_get_parent (child) == widget);
  g_return_if_fail (snapshot != NULL);

  if (!_gtk_widget_is_drawable (child))
    return;

  /* The origin of @child in @widget's coordinates, as in
   * gtk_container_propagate_draw() */
  if (!_gtk_widget_get_has_window (widget))
    {
      _gtk_widget_get_allocation (widget, &allocation);
      x = -allocation.x;
      y = -allocation.y;
    }
  else
    {
      x = 0;
      y = 0;
    }

  window = _gtk_widget_get_window (widget);

  for (w = _gtk_widget_get_window (child); w && w != window; w = gdk_window_get_parent (w))
    {
      int wx, wy;
      gdk_window_get_position (w, &wx, &wy);
      x += wx;
      y += wy;
    }

  if (w == NULL)
    {
      x = 0;
      y = 0;
    }

  if (!_gtk_widget_get_has_window (child))
    {
      _gtk_widget_get_allocation (child, &allocation);
      x += allocation.x;
      y += allocation.y;
    }

  gtk_snapshot_save (snapshot);
  gtk_snapshot_translate (snapshot, &GRAPHENE_POINT_INIT (x, y));
  gtk_widget_snapshot (child, snapshot);
  gtk_snapshot_restore (snapshot);
}

gboolean
_otk_widget_wants_gsk_render (GtkWidget *widget,
                              GdkWindow *window)
{
  return otk_get_renderer () != OTK_RENDERER_LEGACY &&
         _gtk_widget_is_toplevel (widget) &&
         window == _gtk_widget_get_window (widget);
}

static void
otk_renderer_free (gpointer data)
{
  GskRenderer *renderer = data;

  if (gsk_renderer_is_realized (renderer))
    gsk_renderer_unrealize (renderer);
  g_object_unref (renderer);
}

static GskRenderer *
otk_widget_get_renderer (GtkWidget *widget,
                         GdkWindow *window)
{
  GskRenderer *renderer;
  GError *error = NULL;

  renderer = g_object_get_qdata (G_OBJECT (widget), quark_renderer);
  if (renderer != NULL && gsk_renderer_get_surface (renderer) == window)
    return renderer;

  renderer = gsk_cairo_renderer_new ();
  if (!gsk_renderer_realize (renderer, window, &error))
    {
      g_warning ("OTK_RENDERER: could not realize OSK's Cairo renderer: %s", error->message);
      g_error_free (error);
      g_object_unref (renderer);
      g_object_set_qdata (G_OBJECT (widget), quark_renderer, NULL);
      return NULL;
    }

  g_object_set_qdata_full (G_OBJECT (widget), quark_renderer, renderer, otk_renderer_free);

  return renderer;
}

gboolean
_otk_widget_render (GtkWidget            *widget,
                    GdkWindow            *window,
                    const cairo_region_t *region,
                    int                   x,
                    int                   y)
{
  GskRenderer *renderer;
  GtkSnapshot *snapshot;
  GskRenderNode *node;
  cairo_rectangle_int_t extents;

  renderer = otk_widget_get_renderer (widget, window);
  if (renderer == NULL)
    return FALSE;

  /* (x, y) is @widget's translation to @window, as in gtk_widget_render() */
  cairo_region_get_extents (region, &extents);
  paint_clip_widget = widget;
  paint_clip.x = extents.x + x;
  paint_clip.y = extents.y + y;
  paint_clip.width = extents.width;
  paint_clip.height = extents.height;

  snapshot = gtk_snapshot_new ();
  gtk_snapshot_translate (snapshot, &GRAPHENE_POINT_INIT (-x, -y));
  gtk_widget_snapshot (widget, snapshot);
  node = gtk_snapshot_free_to_node (snapshot);

  paint_clip_widget = NULL;

  if (node == NULL)
    node = gsk_container_node_new (NULL, 0);

  gsk_renderer_render (renderer, node, region);
  gsk_render_node_unref (node);

  return TRUE;
}

void
_otk_widget_unrealize_renderer (GtkWidget *widget)
{
  if (quark_renderer != 0)
    g_object_set_qdata (G_OBJECT (widget), quark_renderer, NULL);
}

#else /* !OTK_HAVE_OSK */

/* OTK built without OSK: GtkWidgetClass.snapshot exists (the ABI does not
 * depend on the build) but nothing calls it, and there is no GtkSnapshot to
 * pass to these functions. */

void
_otk_widget_class_init_snapshot (GtkWidgetClass *klass)
{
  const char *env = g_getenv ("OTK_RENDERER");

  if (env != NULL && *env != '\0' && g_ascii_strcasecmp (env, "legacy") != 0)
    g_warning ("OTK_RENDERER=%s needs OTK built with OSK; using legacy", env);

  klass->snapshot = NULL;
}

void
gtk_widget_snapshot (GtkWidget   *widget,
                     GtkSnapshot *snapshot)
{
  g_warning ("gtk_widget_snapshot(): OTK was built without OSK");
}

void
gtk_widget_snapshot_child (GtkWidget   *widget,
                           GtkWidget   *child,
                           GtkSnapshot *snapshot)
{
  g_warning ("gtk_widget_snapshot_child(): OTK was built without OSK");
}

#endif /* OTK_HAVE_OSK */
