/* OTK: GtkWidgetClass.snapshot and OTK_RENDERER.
 *
 * Run once per renderer (meson: snapshot-legacy, snapshot-cairo); the results
 * must not depend on it.
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */
#include <gtk/gtk.h>
#include <osk/osk.h>
#include <string.h>

#define RED   0xff0000
#define GREEN 0x00ff00
#define BLUE  0x0000ff

/* ---------------------------------------------------------------- TestColor
 * A widget drawn only with GtkWidgetClass.snapshot: one colour. */

typedef struct { GtkWidget parent; GdkRGBA color; int draws; } TestColor;
typedef struct { GtkWidgetClass parent_class; } TestColorClass;
static GType test_color_get_type (void);
G_DEFINE_TYPE (TestColor, test_color, GTK_TYPE_WIDGET)

static void
test_color_snapshot (GtkWidget   *widget,
                     GtkSnapshot *snapshot)
{
  TestColor *self = (TestColor *) widget;

  gtk_snapshot_append_color (snapshot, &self->color,
                             &GRAPHENE_RECT_INIT (0, 0,
                                                  gtk_widget_get_allocated_width (widget),
                                                  gtk_widget_get_allocated_height (widget)));
}

static gboolean
test_color_draw (GtkWidget *widget,
                 cairo_t   *cr)
{
  ((TestColor *) widget)->draws++;
  return FALSE;
}

static void
test_color_get_preferred_size (GtkWidget *widget,
                               int       *minimum,
                               int       *natural)
{
  *minimum = *natural = 20;
}

static void
test_color_class_init (TestColorClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  widget_class->snapshot = test_color_snapshot;
  widget_class->draw = test_color_draw;
  widget_class->get_preferred_width = test_color_get_preferred_size;
  widget_class->get_preferred_height = test_color_get_preferred_size;
}

static void
test_color_init (TestColor *self)
{
  gtk_widget_set_has_window (GTK_WIDGET (self), FALSE);
  self->color = (GdkRGBA) { 1, 0, 0, 1 };
}

/* ---------------------------------------------------------------- TestFrame
 * A container drawn with snapshot: a blue 10px frame around its child. */

typedef struct { GtkBin parent; } TestFrame;
typedef struct { GtkBinClass parent_class; } TestFrameClass;
static GType test_frame_get_type (void);
G_DEFINE_TYPE (TestFrame, test_frame, GTK_TYPE_BIN)

static void
test_frame_snapshot (GtkWidget   *widget,
                     GtkSnapshot *snapshot)
{
  GtkWidget *child = gtk_bin_get_child (GTK_BIN (widget));

  gtk_snapshot_append_color (snapshot, &(GdkRGBA) { 0, 0, 1, 1 },
                             &GRAPHENE_RECT_INIT (0, 0,
                                                  gtk_widget_get_allocated_width (widget),
                                                  gtk_widget_get_allocated_height (widget)));
  if (child)
    gtk_widget_snapshot_child (widget, child, snapshot);
}

static void
test_frame_size_allocate (GtkWidget     *widget,
                          GtkAllocation *allocation)
{
  GtkWidget *child = gtk_bin_get_child (GTK_BIN (widget));
  GtkAllocation child_allocation;

  gtk_widget_set_allocation (widget, allocation);
  if (child)
    {
      child_allocation.x = allocation->x + 10;
      child_allocation.y = allocation->y + 10;
      child_allocation.width = MAX (allocation->width - 20, 1);
      child_allocation.height = MAX (allocation->height - 20, 1);
      gtk_widget_size_allocate (child, &child_allocation);
    }
}

static void
test_frame_get_preferred_width (GtkWidget *widget,
                                int       *minimum,
                                int       *natural)
{
  GtkWidget *child = gtk_bin_get_child (GTK_BIN (widget));

  *minimum = *natural = 0;
  if (child)
    gtk_widget_get_preferred_width (child, minimum, natural);
  *minimum += 20;
  *natural += 20;
}

static void
test_frame_get_preferred_height (GtkWidget *widget,
                                 int       *minimum,
                                 int       *natural)
{
  GtkWidget *child = gtk_bin_get_child (GTK_BIN (widget));

  *minimum = *natural = 0;
  if (child)
    gtk_widget_get_preferred_height (child, minimum, natural);
  *minimum += 20;
  *natural += 20;
}

static void
test_frame_class_init (TestFrameClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  widget_class->snapshot = test_frame_snapshot;
  widget_class->size_allocate = test_frame_size_allocate;
  widget_class->get_preferred_width = test_frame_get_preferred_width;
  widget_class->get_preferred_height = test_frame_get_preferred_height;
}

static void
test_frame_init (TestFrame *self)
{
  gtk_widget_set_has_window (GTK_WIDGET (self), FALSE);
}

/* ---------------------------------------------------------------- helpers */

static gboolean
renderer_is_cairo (void)
{
  const char *env = g_getenv ("OTK_RENDERER");
  return env != NULL && g_ascii_strcasecmp (env, "cairo") == 0;
}

static gboolean
drawn_cb (GtkWidget *widget,
          cairo_t   *cr,
          gboolean  *drawn)
{
  *drawn = TRUE;
  return FALSE;
}

/* Waits until @window has painted (an expose, through either renderer) and
 * the X server has the result.  gtk_test_widget_wait_for_draw() can return
 * on a frame before the window is mapped. */
static void
wait_for_paint (GtkWidget *window)
{
  gboolean drawn = FALSE;
  gulong id;
  gint64 end = g_get_monotonic_time () + 5 * G_TIME_SPAN_SECOND;

  id = g_signal_connect_after (window, "draw", G_CALLBACK (drawn_cb), &drawn);
  gtk_widget_queue_draw (window);
  while (!drawn && g_get_monotonic_time () < end)
    g_main_context_iteration (NULL, TRUE);
  g_signal_handler_disconnect (window, id);
  g_assert_true (drawn);

  while (g_main_context_iteration (NULL, FALSE))
    ;
  gdk_display_sync (gtk_widget_get_display (window));
}

static GtkWidget *
show_window (GtkWidget *child)
{
  GtkWidget *window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

  gtk_window_set_decorated (GTK_WINDOW (window), FALSE);
  /* an opaque visual, so that the X server keeps what is drawn for read_window() */
  gtk_widget_set_visual (window, gdk_screen_get_system_visual (gtk_widget_get_screen (window)));
  gtk_container_add (GTK_CONTAINER (window), child);
  gtk_widget_show_all (window);
  gtk_test_widget_wait_for_draw (window);
  wait_for_paint (window);

  return window;
}

static cairo_surface_t *
draw_widget (GtkWidget *widget)
{
  cairo_surface_t *surface;
  cairo_t *cr;

  surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32,
                                        gtk_widget_get_allocated_width (widget),
                                        gtk_widget_get_allocated_height (widget));
  cr = cairo_create (surface);
  gtk_widget_draw (widget, cr);
  cairo_destroy (cr);

  return surface;
}

static cairo_surface_t *
draw_node (GskRenderNode *node,
           int            width,
           int            height)
{
  cairo_surface_t *surface;
  cairo_t *cr;

  surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);
  cr = cairo_create (surface);
  gsk_render_node_draw (node, cr);
  cairo_destroy (cr);

  return surface;
}

static guint32
surface_pixel (cairo_surface_t *surface,
               int              x,
               int              y)
{
  const guchar *data;

  cairo_surface_flush (surface);
  data = cairo_image_surface_get_data (surface) + y * cairo_image_surface_get_stride (surface);

  return ((const guint32 *) data)[x] & 0xffffff;
}

static guint32
pixbuf_pixel (GdkPixbuf *pixbuf,
              int        x,
              int        y)
{
  const guchar *p = gdk_pixbuf_get_pixels (pixbuf)
                    + y * gdk_pixbuf_get_rowstride (pixbuf)
                    + x * gdk_pixbuf_get_n_channels (pixbuf);

  return (p[0] << 16) | (p[1] << 8) | p[2];
}

static void
widget_origin (GtkWidget *widget,
               GtkWidget *ancestor,
               int       *x,
               int       *y)
{
  g_assert_true (gtk_widget_translate_coordinates (widget, ancestor, 0, 0, x, y));
}

static GdkPixbuf *
read_window (GtkWidget *window)
{
  int x, y;

  /* What is on the screen, read from the root window: reading the GdkWindow
   * itself returns nothing on some X servers.  The test windows are not
   * covered (no window manager, nothing else mapped). */
  gdk_window_get_origin (gtk_widget_get_window (window), &x, &y);

  return gdk_pixbuf_get_from_window (gdk_get_default_root_window (), x, y,
                                     gtk_widget_get_allocated_width (window),
                                     gtk_widget_get_allocated_height (window));
}

/* ---------------------------------------------------------------- tests */

/* A widget without its own snapshot becomes a cairo node that draws exactly
 * like gtk_widget_draw(). */
static void
test_fallback (void)
{
  GtkWidget *label, *window;
  GtkSnapshot *snapshot;
  GskRenderNode *node;
  cairo_surface_t *drawn, *rendered;
  int width, height;

  label = gtk_label_new ("OSK snapshot");
  window = show_window (label);
  width = gtk_widget_get_allocated_width (label);
  height = gtk_widget_get_allocated_height (label);

  snapshot = gtk_snapshot_new ();
  gtk_widget_snapshot (label, snapshot);
  node = gtk_snapshot_free_to_node (snapshot);
  g_assert_nonnull (node);
  g_assert_cmpint (gsk_render_node_get_node_type (node), ==, GSK_CAIRO_NODE);

  drawn = draw_widget (label);
  rendered = draw_node (node, width, height);
  cairo_surface_flush (drawn);
  cairo_surface_flush (rendered);
  g_assert_cmpmem (cairo_image_surface_get_data (drawn), cairo_image_surface_get_stride (drawn) * height,
                   cairo_image_surface_get_data (rendered), cairo_image_surface_get_stride (rendered) * height);

  cairo_surface_destroy (drawn);
  cairo_surface_destroy (rendered);
  gsk_render_node_unref (node);
  gtk_widget_destroy (window);
}

/* Widgets with a snapshot are drawn from their nodes, also by gtk_widget_draw()
 * (the legacy renderer), and ::draw is not emitted for them. */
static void
test_custom (void)
{
  GtkWidget *frame, *color, *window;
  GtkSnapshot *snapshot;
  GskRenderNode *node;
  cairo_surface_t *surface;
  int x, y;

  frame = g_object_new (test_frame_get_type (), NULL);
  color = g_object_new (test_color_get_type (), NULL);
  gtk_container_add (GTK_CONTAINER (frame), color);
  window = show_window (frame);

  g_assert_cmpint (gtk_widget_get_allocated_width (frame), ==, 40);
  g_assert_cmpint (gtk_widget_get_allocated_height (frame), ==, 40);

  surface = draw_widget (window);
  widget_origin (frame, window, &x, &y);
  g_assert_cmphex (surface_pixel (surface, x + 5, y + 5), ==, BLUE);
  g_assert_cmphex (surface_pixel (surface, x + 20, y + 20), ==, RED);
  g_assert_cmphex (surface_pixel (surface, x + 35, y + 35), ==, BLUE);
  cairo_surface_destroy (surface);
  g_assert_cmpint (((TestColor *) color)->draws, ==, 0);

  snapshot = gtk_snapshot_new ();
  gtk_widget_snapshot (frame, snapshot);
  node = gtk_snapshot_free_to_node (snapshot);
  surface = draw_node (node, 40, 40);
  g_assert_cmphex (surface_pixel (surface, 5, 5), ==, BLUE);
  g_assert_cmphex (surface_pixel (surface, 10, 10), ==, RED);
  g_assert_cmphex (surface_pixel (surface, 29, 29), ==, RED);
  g_assert_cmphex (surface_pixel (surface, 30, 30), ==, BLUE);
  cairo_surface_destroy (surface);
  gsk_render_node_unref (node);

  gtk_widget_destroy (window);
}

/* gtk_widget_set_opacity() applies to snapshot widgets too. */
static void
test_opacity (void)
{
  GtkWidget *frame, *color, *window;
  cairo_surface_t *surface;
  guint32 pixel;

  frame = g_object_new (test_frame_get_type (), NULL);
  color = g_object_new (test_color_get_type (), NULL);
  gtk_container_add (GTK_CONTAINER (frame), color);
  gtk_widget_set_opacity (color, 0.5);
  window = show_window (frame);

  surface = draw_widget (frame);
  pixel = surface_pixel (surface, 20, 20);
  g_assert_cmpint (ABS ((int) ((pixel >> 16) & 0xff) - 0x80), <=, 1);
  g_assert_cmpint ((pixel >> 8) & 0xff, ==, 0);
  g_assert_cmpint (ABS ((int) (pixel & 0xff) - 0x80), <=, 1);
  cairo_surface_destroy (surface);

  gtk_widget_destroy (window);
}

/* What reaches the screen is what gtk_widget_draw() draws, with either
 * renderer, also after a partial redraw. */
static void
test_window (void)
{
  GtkWidget *box, *label, *frame, *color, *window;
  GdkPixbuf *pixbuf;
  cairo_surface_t *surface;
  int x, y, width, height, differ;

  box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 6);
  label = gtk_label_new ("Ocimum");
  frame = g_object_new (test_frame_get_type (), NULL);
  color = g_object_new (test_color_get_type (), NULL);
  gtk_container_add (GTK_CONTAINER (frame), color);
  gtk_box_pack_start (GTK_BOX (box), label, FALSE, FALSE, 0);
  gtk_box_pack_start (GTK_BOX (box), frame, FALSE, FALSE, 0);
  window = show_window (box);

  if (renderer_is_cairo ())
    g_assert_nonnull (g_object_get_data (G_OBJECT (window), "otk-widget-renderer"));
  else
    g_assert_null (g_object_get_data (G_OBJECT (window), "otk-widget-renderer"));

  width = gtk_widget_get_allocated_width (window);
  height = gtk_widget_get_allocated_height (window);
  widget_origin (frame, window, &x, &y);

  pixbuf = read_window (window);
  g_assert_cmphex (pixbuf_pixel (pixbuf, x + 5, y + 5), ==, BLUE);
  g_assert_cmphex (pixbuf_pixel (pixbuf, x + 20, y + 20), ==, RED);

  surface = draw_widget (window);
  differ = 0;
  for (int j = 0; j < height; j++)
    for (int i = 0; i < width; i++)
      if (pixbuf_pixel (pixbuf, i, j) != surface_pixel (surface, i, j))
        differ++;
  g_assert_cmpint (differ, ==, 0);
  cairo_surface_destroy (surface);
  g_object_unref (pixbuf);

  /* a redraw of only the child */
  ((TestColor *) color)->color = (GdkRGBA) { 0, 1, 0, 1 };
  gtk_widget_queue_draw (color);
  wait_for_paint (window);

  pixbuf = read_window (window);
  g_assert_cmphex (pixbuf_pixel (pixbuf, x + 5, y + 5), ==, BLUE);
  g_assert_cmphex (pixbuf_pixel (pixbuf, x + 20, y + 20), ==, GREEN);
  surface = draw_widget (window);
  differ = 0;
  for (int j = 0; j < height; j++)
    for (int i = 0; i < width; i++)
      if (pixbuf_pixel (pixbuf, i, j) != surface_pixel (surface, i, j))
        differ++;
  g_assert_cmpint (differ, ==, 0);
  cairo_surface_destroy (surface);
  g_object_unref (pixbuf);

  g_assert_cmpint (((TestColor *) color)->draws, ==, 0);

  gtk_widget_destroy (window);
}

int
main (int argc, char **argv)
{
  gtk_test_init (&argc, &argv, NULL);

  g_test_add_func ("/snapshot/fallback", test_fallback);
  g_test_add_func ("/snapshot/custom", test_custom);
  g_test_add_func ("/snapshot/opacity", test_opacity);
  g_test_add_func ("/snapshot/window", test_window);

  return g_test_run ();
}
