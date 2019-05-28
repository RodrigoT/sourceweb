project('libMurmurHash3', 'cpp')

inc = include_directories('.')
src_MurmurHash3 = [
    'MurmurHash3.cpp'
    ]

libMurmurHash3 = static_library('MurmurHash3', src_MurmurHash3, include_directories : inc)
libMurmurHash3_dep = declare_dependency(include_directories : inc, link_with : libMurmurHash3)


