project('sourceweb', 'cpp')
add_global_arguments('-std=c++0x', language : 'cpp')
add_global_arguments('-std=gnu99', language : 'c')

qt5_mod = import('qt5')
qt5widgets = dependency('qt5', modules : ['Core', 'Widgets', 'Concurrent'])

qtprocessed = qt5_mod.preprocess(
  moc_headers : [ # Only headers that need moc should be put here
    'navigator/ReportWindowFactory.h',  'navigator/FindBar.h',          'navigator/PlaceholderLineEdit.h'
    ,'navigator/ReportSymList.h',       'navigator/TableReport.h',      'navigator/ReportRefList.h'
    ,'navigator/ReportDefList.h',       'navigator/TableReportView.h',  'navigator/MainWindow.h'
    ,'navigator/FolderWidget.h',        'navigator/Application.h',      'navigator/TableReportWindow.h'
    ,'navigator/ReportFileList.h',      'navigator/SourceWidget.h'],
  ui_files    : 'navigator/MainWindow.ui',
  qresources  : 'navigator/navigator.qrc',
)

libre2_proj = subproject('libre2')
libre2_dep = libre2_proj.get_variable('libre2_dep')
libsha2_proj = subproject('libsha2')
libsha2_dep = libsha2_proj.get_variable('libsha2_dep')
libsnappy_proj = subproject('libsnappy')
libsnappy_dep = libsnappy_proj.get_variable('libsnappy_dep')
libMurmurHash3_proj = subproject('libMurmurHash3')
libMurmurHash3_dep = libMurmurHash3_proj.get_variable('libMurmurHash3_dep')

src_lidxdb = [
    'libindexdb/Buffer.cc',              'libindexdb/FileIo.cc',             'libindexdb/FileIo64BitSupport.cc',
    'libindexdb/IndexArchiveBuilder.cc', 'libindexdb/IndexArchiveReader.cc', 'libindexdb/IndexDb.cc',
    'libindexdb/StringTable.cc']
inc_lidxdb = include_directories('libindexdb')
libidxdb = static_library('indexdb', src_lidxdb, dependencies: [libsha2_dep, libsnappy_dep, libMurmurHash3_dep], include_directories : inc_lidxdb)
libidxdb_dep = declare_dependency(include_directories : inc_lidxdb, link_with : libidxdb)

src_nav = [
    'navigator/CXXSyntaxHighlighter.cc',    'navigator/File.cc',                'navigator/FileManager.cc',
    'navigator/FindBar.cc',                 'navigator/Folder.cc',              'navigator/FolderItem.cc',
    'navigator/FolderWidget.cc',            'navigator/History.cc',             'navigator/MainWindow.cc',
    'navigator/Misc.cc',                    'navigator/PlaceholderLineEdit.cc', 'navigator/Project.cc',
    'navigator/Ref.cc',                     'navigator/Regex.cc',               'navigator/RegexMatchList.cc',
    'navigator/ReportDefList.cc',           'navigator/ReportFileList.cc',      'navigator/ReportRefList.cc',
    'navigator/ReportSymList.cc',           'navigator/ReportWindowFactory.cc', 'navigator/SourceWidget.cc',
    'navigator/TableReport.cc',             'navigator/TableReportView.cc',     'navigator/TableReportWindow.cc',
    'navigator/TextWidthCalculator.cc',     'navigator/main.cc',                'navigator/Application.cpp']
executable('nagivator', sources: [src_nav, qtprocessed], dependencies: [qt5widgets, libre2_dep, libidxdb_dep])

src_idxtool = ['index-tool/main.cc']
executable('sw-index-tool', sources: src_idxtool, dependencies: libidxdb_dep)

llvm_dep = dependency('llvm', version : '>= 6.0', modules: [
    'mc', 'mcparser', 'object', 'asmparser', 'core', 'profiledata', 'support', 'option', 'bitwriter', 'bitreader', 'demangle'])
llvm_libdir = llvm_dep.get_configtool_variable('libdir')
dep_clang_names = [
    'clangFrontend',    'clangSerialization',  'clangDriver',   'clangTooling',
    'clangParse',       'clangSema',           'clangAnalysis', 'clangEdit',
    'clangAST',         'clangLex',             'clangBasic']
dep_clang = []
foreach lclang: dep_clang_names
    dep_clang += meson.get_compiler('cpp').find_library(lclang, dirs : llvm_libdir)
endforeach
src_clidx = [
    'clang-indexer/ASTIndexer.cc',      'clang-indexer/DaemonPool.cc',          'clang-indexer/IndexBuilder.cc',
    'clang-indexer/IndexerContext.cc',  'clang-indexer/IndexerPPCallbacks.cc',  'clang-indexer/Mutex.cc',
    'clang-indexer/NameGenerator.cc',   'clang-indexer/Process.cc',             'clang-indexer/TUIndexer.cc',
    'clang-indexer/Util.cc',            'clang-indexer/main.cc' ]
executable('sw-clang-indexer', sources: src_clidx, dependencies: [llvm_dep, qt5widgets, dep_clang, libidxdb_dep])

src_swb = ['btrace/btrace.c']
if build_machine.system() == 'darwin'
    src_swb += 'btrace/btrace_darwin.c'
elif ['dragonfly','freebsd','netbsd'].contains(build_machine.system())
    src_swb += 'btrace/btrace_freebsd.c'
elif build_machine.system() == 'linux'
    src_swb += 'btrace/btrace_linux.c'
else
    warning('Unknown OS '+build_machine.system()+': asuming Solaris')
    src_swb += 'btrace/btrace_solaris.c'
endif
vflag = '-Wl,--version-script,btrace/version_script'
shared_library('sw-btrace', sources: src_swb)

