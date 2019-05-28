project('sourceweb', 'cpp')

qt5_mod = import('qt5')
qt5widgets = dependency('qt5', modules : ['Widgets', 'Concurrent'])

qtprocessed = qt5_mod.preprocess(
  moc_headers : [ # Only headers that need moc should be put here
    'navigator/ReportWindowFactory.h'
    , 'navigator/FindBar.h'
    , 'navigator/PlaceholderLineEdit.h'
    , 'navigator/ReportSymList.h'
    , 'navigator/TableReport.h'
    , 'navigator/ReportRefList.h'
    , 'navigator/ReportDefList.h'
    , 'navigator/TableReportView.h'
    , 'navigator/MainWindow.h'
    , 'navigator/FolderWidget.h'
    , 'navigator/Application.h'
    , 'navigator/TableReportWindow.h'
    , 'navigator/ReportFileList.h'
    , 'navigator/SourceWidget.h'
      ],
  #  moc_sources : 'helperFile.cpp', # must have #include"moc_helperFile.cpp"
  ui_files    : 'navigator/MainWindow.ui',
  qresources  : 'navigator/navigator.qrc',
)

#q5exe = executable('qt5test',
#  sources     : ['main.cpp',
#                 'mainWindow.cpp',
#                 processed],
#  dependencies: qt5widgets)

libre2_proj = subproject('libre2')
libre2_dep = libre2_proj.get_variable('libre2_dep')
libsha2_proj = subproject('libsha2')
libsha2_dep = libsha2_proj.get_variable('libsha2_dep')
libsnappy_proj = subproject('libsnappy')
libsnappy_dep = libsnappy_proj.get_variable('libsnappy_dep')
libMurmurHash3_proj = subproject('libMurmurHash3')
libMurmurHash3_dep = libMurmurHash3_proj.get_variable('libMurmurHash3_dep')

src_lidxdb = [
    'libindexdb/Buffer.cc',
    'libindexdb/FileIo.cc',
    'libindexdb/FileIo64BitSupport.cc',
    'libindexdb/IndexArchiveBuilder.cc',
    'libindexdb/IndexArchiveReader.cc',
    'libindexdb/IndexDb.cc',
    'libindexdb/StringTable.cc']
inc_lidxdb = include_directories('libindexdb')
libidxdb = static_library('indexdb', src_lidxdb, dependencies: [libsha2_dep, libsnappy_dep, libMurmurHash3_dep], include_directories : inc_lidxdb)
libidxdb_dep = declare_dependency(include_directories : inc_lidxdb, link_with : libidxdb)

src_nav = [
    'navigator/CXXSyntaxHighlighter.cc', 'navigator/File.cc', 'navigator/FileManager.cc',
    'navigator/FindBar.cc', 'navigator/Folder.cc', 'navigator/FolderItem.cc',
    'navigator/FolderWidget.cc', 'navigator/History.cc', 'navigator/MainWindow.cc',
    'navigator/Misc.cc', 'navigator/PlaceholderLineEdit.cc', 'navigator/Project.cc',
    'navigator/Ref.cc', 'navigator/Regex.cc', 'navigator/RegexMatchList.cc',
    'navigator/ReportDefList.cc', 'navigator/ReportFileList.cc',
    'navigator/ReportRefList.cc', 'navigator/ReportSymList.cc',
    'navigator/ReportWindowFactory.cc', 'navigator/SourceWidget.cc',
    'navigator/TableReport.cc', 'navigator/TableReportView.cc',
    'navigator/TableReportWindow.cc', 'navigator/TextWidthCalculator.cc',
    'navigator/main.cc', 'navigator/Application.cpp']
executable('nagivator', sources: [src_nav, qtprocessed], dependencies: [qt5widgets, libre2_dep, libidxdb_dep])

