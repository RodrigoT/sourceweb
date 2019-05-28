project('libsnappy', 'cpp')

inc = include_directories('.')
src_snappy = [
    'snappy-sinksource.cc',
    'snappy-stubs-internal.cc',
    'snappy.cc'
    ]

libsnappy = static_library('snappy', src_snappy, include_directories : inc)
libsnappy_dep = declare_dependency(include_directories : inc, link_with : libsnappy)

