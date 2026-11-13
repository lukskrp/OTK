/* OSK - the Ocimum Scene Kit
 *
 * GTK 4's profiler marks, compiled out: OSK has no sysprof integration yet.
 * (ODK has its own gdkprofilerprivate.h; this one serves osk/ only.)
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */
#pragma once

#define GDK_PROFILER_IS_RUNNING 0
#define GDK_PROFILER_CURRENT_TIME 0

#define gdk_profiler_is_running() FALSE
#define gdk_profiler_add_mark(b, d, n, m) G_STMT_START {} G_STMT_END
#define gdk_profiler_end_mark(b, n, m) G_STMT_START {} G_STMT_END
#define gdk_profiler_add_markf(b, d, n, m, ...) G_STMT_START {} G_STMT_END
#define gdk_profiler_end_markf(b, n, m, ...) G_STMT_START {} G_STMT_END
#define gdk_profiler_define_counter(n, d) 0
#define gdk_profiler_define_int_counter(n, d) 0
#define gdk_profiler_set_counter(i, v) G_STMT_START {} G_STMT_END
#define gdk_profiler_set_int_counter(i, v) G_STMT_START {} G_STMT_END
