/* OSK: GdkRGBA is ODK's (double components); GTK 4's float GdkRGBA is not imported. */
#pragma once

#include <gdk/gdk.h>

G_BEGIN_DECLS
/* From GTK 4's gdkrgba.h; OSK-internal (gdk/gdkrgba.c). */
GString *      gdk_rgba_print          (const GdkRGBA *rgba,
                                        GString       *string);
G_END_DECLS
