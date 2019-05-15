
#pragma once

#include <QString>
#include <QTabWidget>

namespace Nav {
class ReportWindowFactory
{ // this calss control the behaviour when requesting a new result window
    public:
        enum class WindowPolicy {
            NewWindow, // always new window
            GroupedWindow, // grouped one window per resutl type
            SingleWindow, // only one result window
        };
        enum class WindowType {
            SymbolSearch,
            Files,
            GlobalDefinitions,
            SymbolResult,
            GlobalDefintionResult
        };
        ReportWindowFactory();
        void openWindow(WindowType windowType, const QString &symbolName);
    protected:
        WindowPolicy currentWindowPolicy = WindowPolicy::GroupedWindow;
        QTabWidget singleWindow;
        QTabWidget groupFiles;
        QTabWidget groupSymbols;
        QTabWidget groupGlobalDefinitions;

};
};
