
#pragma once

#include <QString>
#include <QTabWidget>
#include <QObject>

namespace Nav {
class ReportWindowFactory : public QObject
{ // this calss control the behaviour when requesting a new result window

    Q_OBJECT

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
        virtual ~ReportWindowFactory() = default;
        void openWindow(WindowType windowType, const QString &symbolName);
    protected:
        WindowPolicy currentWindowPolicy = WindowPolicy::SingleWindow;
        QTabWidget singleWindow;
        QTabWidget groupFiles;
        QTabWidget groupSymbols;
        QTabWidget groupGlobalDefinitions;

};
};
