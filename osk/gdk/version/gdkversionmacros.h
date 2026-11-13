/* OSK - the Ocimum Scene Kit
 *
 * GTK 4's availability macros for the API OSK imports from GTK 4.
 * OSK has one API level: everything is available as of OTK 2, so the
 * GTK 4 version markers all export the symbol and nothing else.
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

#pragma once

#include <gdk/gdk.h>   /* ODK: GDK_AVAILABLE_IN_ALL, _GDK_EXTERN */

/* Exported whether or not the including file saw OSK's config.h first
 * (glib-mkenums output does not include it). */
#ifdef __GNUC__
#define OSK_AVAILABLE_IN_ALL __attribute__((visibility("default"))) extern
#else
#define OSK_AVAILABLE_IN_ALL _GDK_EXTERN
#endif

#define GDK_AVAILABLE_IN_4_0  OSK_AVAILABLE_IN_ALL
#define GDK_AVAILABLE_IN_4_2  OSK_AVAILABLE_IN_ALL
#define GDK_AVAILABLE_IN_4_4  OSK_AVAILABLE_IN_ALL
#define GDK_AVAILABLE_IN_4_6  OSK_AVAILABLE_IN_ALL
#define GDK_AVAILABLE_IN_4_8  OSK_AVAILABLE_IN_ALL
#define GDK_AVAILABLE_IN_4_10 OSK_AVAILABLE_IN_ALL
#define GDK_AVAILABLE_IN_4_12 OSK_AVAILABLE_IN_ALL
#define GDK_AVAILABLE_IN_4_14 OSK_AVAILABLE_IN_ALL
#define GDK_AVAILABLE_IN_4_16 OSK_AVAILABLE_IN_ALL
#define GDK_AVAILABLE_IN_4_18 OSK_AVAILABLE_IN_ALL
#define GDK_AVAILABLE_IN_4_20 OSK_AVAILABLE_IN_ALL
#define GDK_AVAILABLE_IN_4_22 OSK_AVAILABLE_IN_ALL
#define GDK_AVAILABLE_IN_4_24 OSK_AVAILABLE_IN_ALL

#define GDK_DEPRECATED_IN_4_16_FOR(f) OSK_AVAILABLE_IN_ALL
#define GDK_DEPRECATED_IN_4_20        OSK_AVAILABLE_IN_ALL
#define GDK_DEPRECATED_IN_4_20_FOR(f) OSK_AVAILABLE_IN_ALL
#define GDK_DEPRECATED_TYPE_IN_4_16_FOR(f)
#define GDK_DEPRECATED_TYPE_IN_4_20_FOR(f)

#define GDK_AVAILABLE_ENUMERATOR_IN_4_12
#define GDK_AVAILABLE_ENUMERATOR_IN_4_14
#define GDK_AVAILABLE_ENUMERATOR_IN_4_16
#define GDK_AVAILABLE_ENUMERATOR_IN_4_18
#define GDK_AVAILABLE_ENUMERATOR_IN_4_20
#define GDK_AVAILABLE_ENUMERATOR_IN_4_22
#define GDK_AVAILABLE_ENUMERATOR_IN_4_24
