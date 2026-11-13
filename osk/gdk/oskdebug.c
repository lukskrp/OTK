/* OSK - the Ocimum Scene Kit
 *
 * The GTK 4 debug helpers GSK uses (from GTK 4's gdk/gdk.c and gtk/gtkdebug.c).
 * OSK reads GSK_DEBUG and GDK_DEBUG like GTK 4; all GDK features are on.
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */
#include "config.h"

#include "oskprivate.h"

#include <string.h>

/* From GTK 4's gdk/gdk.c */
guint
gdk_parse_debug_var (const char        *variable,
                     const char        *docs,
                     const GdkDebugKey *keys,
                     guint              nkeys)
{
  guint i;
  guint result = 0;
  const char *string;
  const char *p;
  const char *q;
  gboolean invert;
  gboolean help;

  string = g_getenv (variable);
  if (string == NULL)
    return 0;

  p = string;
  invert = FALSE;
  help = FALSE;

  while (*p)
    {
      q = strpbrk (p, ":;, \t");
      if (!q)
        q = p + strlen (p);

      if (3 == q - p && g_ascii_strncasecmp ("all", p, q - p) == 0)
        {
          invert = TRUE;
        }
      else if (4 == q - p && g_ascii_strncasecmp ("help", p, q - p) == 0)
        {
          help = TRUE;
        }
      else
        {
          for (i = 0; i < nkeys; i++)
            {
              if (strlen (keys[i].key) == q - p &&
                  g_ascii_strncasecmp (keys[i].key, p, q - p) == 0)
                {
                  result |= keys[i].value;
                  break;
                }
            }
          if (i == nkeys)
            gdk_help_message ("Unrecognized value \"%.*s\". Try %s=help", (int) (q - p), p, variable);
         }

      p = q;
      if (*p)
        p++;
    }

  if (help)
    {
      int max_width = 4;
      for (i = 0; i < nkeys; i++)
        max_width = MAX (max_width, strlen (keys[i].key));
      max_width += 4;

      gdk_help_message ("%s", docs);
      gdk_help_message ("Supported %s values:", variable);
      for (i = 0; i < nkeys; i++)
        gdk_help_message ("  %s%*s%s", keys[i].key, (int)(max_width - strlen (keys[i].key)), " ", keys[i].help);
      gdk_help_message ("  %s%*s%s", "all", max_width - 3, " ", "Enable all values. Other given values are subtracted");
      gdk_help_message ("  %s%*s%s", "help", max_width - 4, " ", "Print this help");
      gdk_help_message ("\nMultiple values can be given, separated by : or space.");
    }

  if (invert)
    {
      guint all_flags = 0;

      for (i = 0; i < nkeys; i++)
        {
          all_flags |= keys[i].value;
        }

      result = all_flags & (~result);
    }

  return result;
}

/* GDK_DEBUG: the GTK 4 flags that GSK's code checks. ODK reads its own
 * GDK_DEBUG flags separately; unknown keys are ignored by each side. */
static const GdkDebugKey osk_gdk_debug_keys[] = {
  { "misc",        GDK_DEBUG_MISC,             "Miscellaneous information" },
  { "opengl",      GDK_DEBUG_OPENGL,           "OpenGL support" },
  { "linear",      GDK_DEBUG_LINEAR,           "Use linear buffers" },
  { "hdr",         GDK_DEBUG_HIGH_DEPTH,       "Use high bit depth" },
  { "color-mgmt",  GDK_DEBUG_COLOR_MANAGEMENT, "Debug color management" },
};

GdkDebugFlags
gdk_display_get_debug_flags (GdkDisplay *display)
{
  static gsize flags_once = 0;
  static GdkDebugFlags flags;

  if (g_once_init_enter (&flags_once))
    {
      flags = gdk_parse_debug_var ("GDK_DEBUG",
                                   "GDK_DEBUG selects GDK debugging output and behavior.",
                                   osk_gdk_debug_keys,
                                   G_N_ELEMENTS (osk_gdk_debug_keys));
      g_once_init_leave (&flags_once, 1);
    }

  return flags;
}

gboolean
gdk_has_feature (GdkFeatures feature)
{
  return TRUE;
}

/* GTK_DEBUG flags, used by GTK 4's CSS parser; OSK has none set. */
guint gtk_get_debug_flags (void);

guint
gtk_get_debug_flags (void)
{
  return 0;
}
