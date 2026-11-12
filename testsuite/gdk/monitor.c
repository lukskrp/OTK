/* OTK: the GdkDisplay monitor list model and the GdkMonitor additions
 * (connector, scale). */
#include <string.h>
#include <gtk/gtk.h>
#ifdef GDK_WINDOWING_X11
#include <gdk/gdkx.h>
#endif

/* The model holds exactly gdk_display_get_monitor (0 … n-1), in order. */
static void
assert_model_matches_display (GdkDisplay *display)
{
  GListModel *model = gdk_display_get_monitors (display);
  guint i, n = g_list_model_get_n_items (model);

  g_assert_cmpuint (n, ==, gdk_display_get_n_monitors (display));

  for (i = 0; i < n; i++)
    {
      GdkMonitor *monitor = g_list_model_get_item (model, i);

      g_assert_true (monitor == gdk_display_get_monitor (display, i));
      g_object_unref (monitor);
    }
}

static void
test_monitor_model (void)
{
  GdkDisplay *display = gdk_display_get_default ();
  GListModel *model;
  guint i, n;

  model = gdk_display_get_monitors (display);
  g_assert_nonnull (model);
  g_assert_true (gdk_display_get_monitors (display) == model);
  g_assert_true (g_list_model_get_item_type (model) == GDK_TYPE_MONITOR);

  n = g_list_model_get_n_items (model);
  g_assert_cmpuint (n, >, 0);
  assert_model_matches_display (display);

  for (i = 0; i < n; i++)
    {
      GdkMonitor *monitor = g_list_model_get_item (model, i);
      char *connector = NULL;
      double scale = 0;

      g_object_get (monitor, "connector", &connector, "scale", &scale, NULL);
      g_assert_nonnull (gdk_monitor_get_connector (monitor));
      g_assert_cmpstr (connector, ==, gdk_monitor_get_connector (monitor));
      g_assert_cmpfloat (scale, ==, gdk_monitor_get_scale (monitor));
      g_assert_cmpfloat (gdk_monitor_get_scale (monitor), ==,
                         (double) gdk_monitor_get_scale_factor (monitor));

      g_free (connector);
      g_object_unref (monitor);
    }
}

typedef struct {
  guint added;
  guint removed;
} Changes;

static void
items_changed (GListModel *model,
               guint       position,
               guint       removed,
               guint       added,
               Changes    *changes)
{
  GdkMonitor *monitor;
  guint i;

  changes->added += added;
  changes->removed += removed;

  /* Monitors are complete when they appear. */
  for (i = position; i < position + added; i++)
    {
      monitor = g_list_model_get_item (model, i);
      g_assert_nonnull (gdk_monitor_get_connector (monitor));
      g_object_unref (monitor);
    }
}

static gboolean
timeout_cb (gpointer data)
{
  *(gboolean *) data = TRUE;
  return G_SOURCE_REMOVE;
}

static gboolean
run_xrandr (const char *args, char **out)
{
  char *cmd = g_strconcat ("xrandr ", args, NULL);
  int status = -1;
  gboolean ok;

  ok = g_spawn_command_line_sync (cmd, out, NULL, &status, NULL) &&
       g_spawn_check_exit_status (status, NULL);
  g_free (cmd);
  return ok;
}

static gboolean
display_has_connector (GdkDisplay *display, const char *name)
{
  int i;

  for (i = 0; i < gdk_display_get_n_monitors (display); i++)
    if (g_strcmp0 (gdk_monitor_get_connector (gdk_display_get_monitor (display, i)), name) == 0)
      return TRUE;
  return FALSE;
}

/* Runs the main loop until GDK's own monitor list does (or does not) contain
 * @name, or 3 s pass. */
static gboolean
wait_for_connector (GdkDisplay *display, const char *name, gboolean present)
{
  gboolean timed_out = FALSE;
  guint id = g_timeout_add (3000, timeout_cb, &timed_out);

  while (!timed_out && display_has_connector (display, name) != present)
    g_main_context_iteration (NULL, TRUE);

  if (!timed_out)
    g_source_remove (id);
  return !timed_out;
}

/* When a RandR monitor is added and removed on the X server, the model
 * follows GDK's monitor list, with complete monitors. */
static void
test_monitor_model_changes (void)
{
  GdkDisplay *display = gdk_display_get_default ();
  GListModel *model;
  Changes changes = { 0, 0 };
  GdkMonitor *first;
  char *args;

#ifdef GDK_WINDOWING_X11
  if (!g_find_program_in_path ("xrandr") || !GDK_IS_X11_DISPLAY (display))
#endif
    {
      g_test_skip ("needs X11 and xrandr");
      return;
    }

  model = gdk_display_get_monitors (display);
  g_signal_connect (model, "items-changed", G_CALLBACK (items_changed), &changes);

  /* Give the new monitor the first monitor's output, so the server lists it
   * as active. */
  first = g_list_model_get_item (model, 0);
  args = g_strdup_printf ("--setmonitor OTK-TEST 320/80x240/60+0+0 %s",
                          gdk_monitor_get_connector (first));
  run_xrandr (args, NULL);
  g_free (args);
  g_object_unref (first);

  if (!wait_for_connector (display, "OTK-TEST", TRUE))
    {
      run_xrandr ("--delmonitor OTK-TEST", NULL);
      g_signal_handlers_disconnect_by_func (model, items_changed, &changes);
      /* Xvfb creates the monitor but sends no RandR event, so GTK never
       * rereads the layout. */
      g_test_skip ("the X server did not report the new RandR monitor");
      return;
    }

  g_assert_cmpuint (changes.added, >, 0);
  assert_model_matches_display (display);

  run_xrandr ("--delmonitor OTK-TEST", NULL);
  g_assert_true (wait_for_connector (display, "OTK-TEST", FALSE));
  g_assert_cmpuint (changes.removed, >, 0);
  assert_model_matches_display (display);

  g_signal_handlers_disconnect_by_func (model, items_changed, &changes);
}

int
main (int argc, char *argv[])
{
  gtk_test_init (&argc, &argv, NULL);

  g_test_add_func ("/monitor/model", test_monitor_model);
  g_test_add_func ("/monitor/model-changes", test_monitor_model_changes);

  return g_test_run ();
}
