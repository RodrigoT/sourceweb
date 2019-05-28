project('libre2', 'cpp')

inc = [include_directories('.'), include_directories('util')]
dep_threads = dependency('threads')
src_re2 = [
    're2/bitstate.cc',
    're2/compile.cc',
    're2/dfa.cc',
    're2/filtered_re2.cc',
    're2/mimics_pcre.cc',
    're2/nfa.cc',
    're2/onepass.cc',
    're2/parse.cc',
    're2/perl_groups.cc',
    're2/prefilter.cc',
    're2/prefilter_tree.cc',
    're2/prog.cc',
    're2/re2.cc',
    're2/regexp.cc',
    're2/set.cc',
    're2/simplify.cc',
    're2/tostring.cc',
    're2/unicode_casefold.cc',
    're2/unicode_groups.cc',

    'util/arena.cc',
    'util/benchmark.cc',
    'util/hash.cc',
    'util/pcre.cc',
    'util/random.cc',
    'util/rune.cc',
    #    'util/sparse_array_test.cc',
    'util/stringpiece.cc',
    'util/stringprintf.cc',
    'util/strutil.cc',
    'util/test.cc',
    'util/thread.cc',
    'util/valgrind.cc'
    ]

libre2 = static_library('re2', src_re2, dependencies: dep_threads, include_directories : inc)
libre2_dep = declare_dependency(include_directories : inc, link_with : libre2)
