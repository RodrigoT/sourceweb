project('libsha2', 'c')

inc = include_directories('.')
#dep_threads = dependency('threads')
src_sha2 = [
    'sha2.c'
    ]

libsha2 = static_library('sha2', src_sha2, include_directories : inc)
libsha2_dep = declare_dependency(include_directories : inc, link_with : libsha2)

