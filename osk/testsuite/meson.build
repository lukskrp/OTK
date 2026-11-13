# GTK 4's GSK tests, run against OSK with the Cairo renderer.
# The lists come from GTK 4.24.0's testsuite/gsk/meson.build.

osk_test_cflags = ['-DGTK_COMPILATION', '-UGLIB_VERSION_MIN_REQUIRED', '-UGLIB_VERSION_MAX_ALLOWED']

osk_testutils = static_library('osk-testutils', 'testutils.c', 'diff/diffreg.c',
  dependencies: libosk_dep,
  include_directories: [osk_config_inc],
  c_args: osk_test_cflags,
)

osk_compare_render = executable('osk-compare-render',
  'gsk/compare-render.c', 'gsk/replay-node.c', 'reftests/reftest-compare.c',
  dependencies: libosk_static_dep,
  include_directories: [osk_config_inc],
  c_args: osk_test_cflags,
)

osk_node_parser = executable('osk-node-parser', 'gsk/node-parser.c',
  link_with: osk_testutils,
  dependencies: libosk_dep,
  include_directories: [osk_config_inc],
  c_args: osk_test_cflags,
)

osk_serialize = executable('osk-serialize', 'gsk/serialize.c',
  link_with: osk_testutils,
  dependencies: libosk_dep,
  include_directories: [osk_config_inc],
  c_args: osk_test_cflags,
)

subdir('gsk')
