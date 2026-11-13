/* OSK - the Ocimum Scene Kit
 *
 * OSK's replacement for GTK 4's gdk/gdktypes.h: the GTK 4 types the
 * rendering engine uses, on top of ODK (OTK's GDK).  GTK 4's own
 * gdktypes.h is not imported, because ODK already defines most of it.
 *
 * Only files in osk/ reach this header, through a quoted
 * #include "gdktypes.h" from osk/gdk/ or through <gdk/oskgdk.h>;
 * <gdk/gdktypes.h> is still ODK's.
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

#pragma once

#include <gdk/gdk.h>
#include <graphene.h>

#include "gdkenums.h"
#include "version/gdkversionmacros.h"

G_BEGIN_DECLS

/* OSK renders into ODK windows: a GdkSurface is a GdkWindow.  A macro rather
 * than a typedef, so introspection sees Odk.Window. */
#define GdkSurface GdkWindow

typedef struct _GdkCicpParams         GdkCicpParams;
typedef struct _GdkColorState         GdkColorState;
typedef struct _GdkTexture            GdkTexture;
typedef struct _GdkTextureDownloader  GdkTextureDownloader;
typedef struct _GdkSnapshot           GdkSnapshot;
typedef struct _GdkPaintable          GdkPaintable;
typedef struct _GdkDmabufFormats      GdkDmabufFormats;
typedef struct _GdkDmabufTexture      GdkDmabufTexture;

#define GDK_DECLARE_INTERNAL_TYPE(ModuleObjName, module_obj_name, MODULE, OBJ_NAME, ParentName) \
  GType module_obj_name##_get_type (void);                                                               \
  G_GNUC_BEGIN_IGNORE_DEPRECATIONS                                                                       \
  typedef struct _##ModuleObjName ModuleObjName;                                                         \
  typedef struct _##ModuleObjName##Class ModuleObjName##Class;                                           \
                                                                                                         \
  _GLIB_DEFINE_AUTOPTR_CHAINUP (ModuleObjName, ParentName)                                               \
  G_DEFINE_AUTOPTR_CLEANUP_FUNC (ModuleObjName##Class, g_type_class_unref)                               \
                                                                                                         \
  G_GNUC_UNUSED static inline ModuleObjName * MODULE##_##OBJ_NAME (gpointer ptr) {                       \
    return G_TYPE_CHECK_INSTANCE_CAST (ptr, module_obj_name##_get_type (), ModuleObjName); }             \
  G_GNUC_UNUSED static inline ModuleObjName##Class * MODULE##_##OBJ_NAME##_CLASS (gpointer ptr) {        \
    return G_TYPE_CHECK_CLASS_CAST (ptr, module_obj_name##_get_type (), ModuleObjName##Class); }         \
  G_GNUC_UNUSED static inline gboolean MODULE##_IS_##OBJ_NAME (gpointer ptr) {                           \
    return G_TYPE_CHECK_INSTANCE_TYPE (ptr, module_obj_name##_get_type ()); }                            \
  G_GNUC_UNUSED static inline gboolean MODULE##_IS_##OBJ_NAME##_CLASS (gpointer ptr) {                   \
    return G_TYPE_CHECK_CLASS_TYPE (ptr, module_obj_name##_get_type ()); }                               \
  G_GNUC_UNUSED static inline ModuleObjName##Class * MODULE##_##OBJ_NAME##_GET_CLASS (gpointer ptr) {    \
    return G_TYPE_INSTANCE_GET_CLASS (ptr, module_obj_name##_get_type (), ModuleObjName##Class); }       \
  G_GNUC_END_IGNORE_DEPRECATIONS

G_END_DECLS
