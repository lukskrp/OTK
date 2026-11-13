# OSK, the Ocimum Scene Kit: GTK 4's rendering engine as an OTK module
# (libosk-3, pkg-config osk-3.0, typelib Osk-3.0).  See osk/UPSTREAM and OTK.md.

osk_api_version = '3.0'
osk_enabled = false

graphene_dep = dependency('graphene-gobject-1.0', version: '>= 1.10.0', required: get_option('osk'))
png_dep = dependency('libpng', required: get_option('osk'))
tiff_dep = dependency('libtiff-4', required: get_option('osk'))
jpeg_dep = dependency('libjpeg', required: get_option('osk'))
osk_glib_dep = dependency('glib-2.0', version: '>= 2.89.3', required: get_option('osk'))
osk_gio_dep = dependency('gio-2.0', version: '>= 2.89.3', required: get_option('osk'))
hb_subset_dep = dependency('harfbuzz-subset', required: get_option('osk'))
osk_pangoft_dep = dependency('pangoft2', required: get_option('osk'))
osk_csi_dep = dependency('cairo-script-interpreter', required: false)

if not (graphene_dep.found() and png_dep.found() and osk_glib_dep.found())
  subdir_done()
endif

osk_enabled = true

osk_conf = configuration_data()
osk_conf.set_quoted('GETTEXT_PACKAGE', 'osk30')
osk_conf.set('_GDK_EXTERN', '__attribute__((visibility("default"))) extern')
osk_conf.set('HAVE_PANGOFT', 1)
osk_conf.set('HAVE_CAIRO_SCRIPT_INTERPRETER', osk_csi_dep.found() ? 1 : false)
osk_conf.set('HAVE_F16C', cc.has_argument('-mf16c') ? 1 : false)
subdir('config')   # config.h alone in its own include directory, ahead of ODK's

osk_sources = files([
  'gsk/gskarithmeticnode.c',
  'gsk/gskblendnode.c',
  'gsk/gskblurnode.c',
  'gsk/gskblurutils.c',
  'gsk/gskbordernode.c',
  'gsk/gskcairoblur.c',
  'gsk/gskcairogradient.c',
  'gsk/gskcaironode.c',
  'gsk/gskcairorenderer.c',
  'gsk/gskcairoshadow.c',
  'gsk/gskclipnode.c',
  'gsk/gskcolormatrixnode.c',
  'gsk/gskcolornode.c',
  'gsk/gskcomponenttransfer.c',
  'gsk/gskcomponenttransfernode.c',
  'gsk/gskcompositenode.c',
  'gsk/gskconicgradientnode.c',
  'gsk/gskcontainernode.c',
  'gsk/gskcontour.c',
  'gsk/gskcopynode.c',
  'gsk/gskcopypasteutils.c',
  'gsk/gskcrossfadenode.c',
  'gsk/gskcurve-ct-values.c',
  'gsk/gskcurve.c',
  'gsk/gskcurveintersect.c',
  'gsk/gskdebug.c',
  'gsk/gskdebugnode.c',
  'gsk/gskdiff.c',
  'gsk/gskdisplacementnode.c',
  'gsk/gskfillnode.c',
  'gsk/gskglshader.c',
  'gsk/gskglshadernode.c',
  'gsk/gskgradient.c',
  'gsk/gskinsetshadownode.c',
  'gsk/gskisolationnode.c',
  'gsk/gsklineargradientnode.c',
  'gsk/gskmasknode.c',
  'gsk/gskopacitynode.c',
  'gsk/gskoutsetshadownode.c',
  'gsk/gskpastenode.c',
  'gsk/gskpath.c',
  'gsk/gskpathbuilder.c',
  'gsk/gskpathclassify.c',
  'gsk/gskpathintersect.c',
  'gsk/gskpathmeasure.c',
  'gsk/gskpathparser.c',
  'gsk/gskpathpoint.c',
  'gsk/gskprivate.c',
  'gsk/gskradialgradientnode.c',
  'gsk/gskrectsnap.c',
  'gsk/gskrenderer.c',
  'gsk/gskrendernode.c',
  'gsk/gskrendernodeparser.c',
  'gsk/gskrenderreplay.c',
  'gsk/gskrepeatnode.c',
  'gsk/gskroundedclipnode.c',
  'gsk/gskroundedrect.c',
  'gsk/gskshadownode.c',
  'gsk/gskstroke.c',
  'gsk/gskstrokenode.c',
  'gsk/gsksubsurfacenode.c',
  'gsk/gsktextnode.c',
  'gsk/gsktexturenode.c',
  'gsk/gsktexturescalenode.c',
  'gsk/gsktransform.c',
  'gsk/gsktransformnode.c',
  'gsk/gskturbulencenode.c',
  'gsk/gl/fp16.c',
  'gsk/oskgpustubs.c',
  'gdk/gdkcicpparams.c',
  'gdk/gdkcolor.c',
  'gdk/gdkcolorstate.c',
  'gdk/gdkdihedral.c',
  'gdk/gdkhsla.c',
  'gdk/osksubsurface.c',
  'gdk/oskdebug.c',
  'gdk/oskdmabuf.c',
  'gdk/loaders/gdkjpeg.c',
  'gdk/loaders/gdktiff.c',
  'gsk/gpu/gskgputransform.c',
  'gdk/gdkmemoryformat.c',
  'gdk/gdkmemorylayout.c',
  'gdk/gdkmemorytexture.c',
  'gdk/gdkmemorytexturebuilder.c',
  'gdk/gdktexture.c',
  'gdk/gdktexturedownloader.c',
  'gdk/gdkpaintable.c',
  'gdk/gdksnapshot.c',
  'gdk/gdkparalleltask.c',
  'gdk/gdkrgba.c',
  'gdk/loaders/gdkpng.c',
  'gtk/css/gtkcssdataurl.c',
  'gtk/css/gtkcsserror.c',
  'gtk/css/gtkcssparser.c',
  'gtk/css/gtkcsssection.c',
  'gtk/css/gtkcssserializer.c',
  'gtk/css/gtkcsstokenizer.c',
  'gtk/css/gtkcssvariablevalue.c',
  'gtk/gtkcolorutils.c',
  'gtk/gtksnapshot.c',
  'gtk/gtkrendernodepaintable.c',
  'gtk/gskpango.c',
])

osk_gsk_public_headers = files([
  'gsk/gsk.h',
  'gsk/gskblendnode.h',
  'gsk/gskblurnode.h',
  'gsk/gskbordernode.h',
  'gsk/gskcaironode.h',
  'gsk/gskcairorenderer.h',
  'gsk/gskclipnode.h',
  'gsk/gskcolormatrixnode.h',
  'gsk/gskcolornode.h',
  'gsk/gskcomponenttransfer.h',
  'gsk/gskcomponenttransfernode.h',
  'gsk/gskcompositenode.h',
  'gsk/gskconicgradientnode.h',
  'gsk/gskcontainernode.h',
  'gsk/gskcopynode.h',
  'gsk/gskcrossfadenode.h',
  'gsk/gskdebugnode.h',
  'gsk/gskenums.h',
  'gsk/gskfillnode.h',
  'gsk/gskglshader.h',
  'gsk/gskglshadernode.h',
  'gsk/gskinsetshadownode.h',
  'gsk/gskisolationnode.h',
  'gsk/gsklineargradientnode.h',
  'gsk/gskmasknode.h',
  'gsk/gskopacitynode.h',
  'gsk/gskoutsetshadownode.h',
  'gsk/gskpastenode.h',
  'gsk/gskpath.h',
  'gsk/gskpathbuilder.h',
  'gsk/gskpathmeasure.h',
  'gsk/gskpathpoint.h',
  'gsk/gskradialgradientnode.h',
  'gsk/gskrectsnap.h',
  'gsk/gskrenderer.h',
  'gsk/gskrendernode.h',
  'gsk/gskrenderreplay.h',
  'gsk/gskrepeatnode.h',
  'gsk/gskroundedclipnode.h',
  'gsk/gskroundedrect.h',
  'gsk/gskshadownode.h',
  'gsk/gskstroke.h',
  'gsk/gskstrokenode.h',
  'gsk/gsksubsurfacenode.h',
  'gsk/gsktextnode.h',
  'gsk/gsktexturenode.h',
  'gsk/gsktexturescalenode.h',
  'gsk/gsktransform.h',
  'gsk/gsktransformnode.h',
  'gsk/gsktypes.h',
])

osk_gtk_public_headers = files([
  'gtk/gtksnapshot.h',
])

osk_gdk_public_headers = files([
  'gdk/gdkcicpparams.h',
  'gdk/gdkcolorstate.h',
  'gdk/gdkenums.h',
  'gdk/gdkmemorytexture.h',
  'gdk/gdkmemorytexturebuilder.h',
  'gdk/gdkpaintable.h',
  'gdk/gdktexture.h',
  'gdk/gdktexturedownloader.h',
  'gdk/gdktypes.h',
  'gdk/oskgdk.h',
  'gdk/osksurface.h',
])

subdir('gsk')
subdir('gdk')
subdir('gtk/css')

osk_cflags = [
  '-DGTK_COMPILATION',
  '-DGDK_COMPILATION',
  # ODK's deprecated GdkColor (gdk/deprecated/gdkcolor.h) stays out: OSK's GdkColor is GTK 4's.
  '-D__GDK_COLOR_H__',
  # GtkCssSection's GType name; OTK registers its own GtkCssSection.
  '-DGtkCssSection=OskCssSection',
  '-DG_LOG_DOMAIN="Osk"',
  '-DG_LOG_STRUCTURED=1',
  '-UGLIB_VERSION_MIN_REQUIRED',
  '-UGLIB_VERSION_MAX_ALLOWED',
  '-DGLIB_VERSION_MIN_REQUIRED=GLIB_VERSION_2_88',
] + common_cflags

# Search order: OSK's generated files, then ODK (<gdk/gdk.h> is ODK's), then
# OSK's sources.  Quoted includes find a header next to the including file first.
osk_inc = include_directories('.', 'gdk', 'gsk', 'gtk', 'gtk/css')
osk_deps = [osk_glib_dep, osk_gio_dep, hb_subset_dep, cairogobj_dep, osk_pangoft_dep, osk_csi_dep, graphene_dep, png_dep, tiff_dep, jpeg_dep, pixbuf_dep, pango_dep, pangocairo_dep, cairo_dep, epoxy_dep, libm]

libosk_f16c = static_library('osk_f16c',
  sources: files('gsk/gl/fp16i.c'),
  dependencies: osk_deps,
  include_directories: [osk_config_inc, confinc, osk_inc],
  c_args: osk_cflags + (cc.has_argument('-mf16c') ? ['-mf16c'] : []),
  implicit_include_directories: false,
)

# Compiled once; libosk-3.so links all of it, and tests that use OSK's private
# API (GTK 4's replay test) link the static library, as GTK 4's tests do.
libosk_static = static_library('osk-3-static',
  sources: [osk_sources, osk_gsk_enums, osk_gdk_enums, osk_css_enums],
  dependencies: osk_deps,
  include_directories: [osk_config_inc, confinc, osk_inc],
  c_args: osk_cflags,
  implicit_include_directories: false,
  link_with: [libosk_f16c],
  pic: true,
)

libosk = library('osk-3',
  dependencies: osk_deps,
  include_directories: [osk_config_inc, confinc, osk_inc],  # for the GIR scanner
  link_whole: [libosk_static],
  link_with: [libgdk],
  soversion: gtk_soversion,
  version: gtk_library_version,
  install: true,
)

install_headers('osk.h', subdir: 'otk-3.0/osk/osk')
install_headers(osk_gsk_public_headers, 'gsk/gsk.h', subdir: 'otk-3.0/osk/gsk')
install_headers(osk_gdk_public_headers, subdir: 'otk-3.0/osk/gdk')
install_headers(osk_gtk_public_headers, subdir: 'otk-3.0/osk/gtk')
install_headers('gdk/version/gdkversionmacros.h', subdir: 'otk-3.0/osk/gdk/version')

libosk_dep = declare_dependency(
  link_with: [libosk, libgdk],
  sources: [osk_gsk_enums[1], osk_gdk_enums[1]],
  include_directories: [confinc, osk_inc],
  dependencies: osk_deps,
)

libosk_static_dep = declare_dependency(
  link_with: [libosk_static, libgdk],
  sources: [osk_gsk_enums[1], osk_gdk_enums[1]],
  include_directories: [osk_config_inc, confinc, osk_inc],
  dependencies: osk_deps,
  compile_args: osk_cflags,
)

import('pkgconfig').generate(
  libraries: ['-L${libdir}', '-losk-3'],
  requires_private: ['gio-2.0', 'harfbuzz-subset', 'pangoft2', 'cairo-gobject', 'gdk-pixbuf-2.0',
                     'epoxy', 'libpng', 'libtiff-4', 'libjpeg'] + (osk_csi_dep.found() ? ['cairo-script-interpreter'] : []),
  filebase: 'osk-3.0',
  name: 'OSK',
  description: 'OSK, the Ocimum Scene Kit: GTK 4\'s rendering engine for OTK',
  version: meson.project_version(),
  requires: ['odk-3.0', 'graphene-gobject-1.0', 'pango', 'pangocairo', 'cairo'],
  subdirs: ['otk-3.0', 'otk-3.0/osk'],
)

if build_gir
  osk_gir = gnome.generate_gir(libosk,
    sources: [osk_gsk_public_headers, osk_gdk_public_headers, osk_gtk_public_headers, osk_sources, osk_gsk_enums, osk_gdk_enums],
    namespace: 'Osk',
    nsversion: osk_api_version,
    identifier_prefix: ['Gsk', 'Gdk', 'Gtk', 'Osk'],
    symbol_prefix: ['gsk', 'gdk', 'gtk', 'osk'],
    export_packages: 'osk-3.0',
    includes: [gdk_gir[0], 'Graphene-1.0', 'cairo-1.0', 'Pango-1.0', 'Gio-2.0'],
    header: 'osk/osk.h',
    install: true,
    dependencies: osk_deps,
    extra_args: ['--quiet', '-DGTK_COMPILATION', '-DGDK_COMPILATION', '-D__GDK_COLOR_H__',
                 '-DGtkCssSection=OskCssSection', '-I' + meson.current_build_dir() / 'config'],
  )
endif

# OSK's tests need no display, so they have their own switch (GTK 3's need X11)
if get_option('osk_tests')
  subdir('testsuite')
endif
