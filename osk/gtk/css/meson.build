# GTK 4's CSS tokenizer and parser, used inside OSK only (the .node format).
osk_css_enums = gnome.mkenums('gtkcssenumtypes',
  sources: files('gtkcssenums.h', 'gtkcsserror.h', 'gtkcsslocation.h', 'gtkcsssection.h'),
  c_template: 'gtkcssenumtypes.c.template',
  h_template: 'gtkcssenumtypes.h.template',
  install_dir: gtk_includedir / 'otk-3.0/osk/gtk/css',
  install_header: true,
)
install_headers('gtkcss.h', 'gtkcssenums.h', 'gtkcsserror.h', 'gtkcsslocation.h', subdir: 'otk-3.0/osk/gtk/css')
