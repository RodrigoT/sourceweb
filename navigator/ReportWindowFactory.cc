
#include "ReportWindowFactory.h"
#include "TableReportWindow.h"
#include "ReportDefList.h"
#include "ReportFileList.h"
#include "ReportRefList.h"
#include "ReportSymList.h"

using namespace Nav;

ReportWindowFactory::ReportWindowFactory()
{
    QTabWidget *panels[] = {&singleWindow, &groupFiles, &groupSymbols, &groupGlobalDefinitions};
    for (QTabWidget *tabPanel : panels)
    {
        tabPanel->setMovable(true);
        tabPanel->setTabsClosable(true);
        //connect(tabPanel, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab_(int))); // TODO
    }
}

void ReportWindowFactory::openWindow(WindowType windowType, const QString &symbolName)
{
    QTabWidget *tabContainer = nullptr; // left as null when using NewWindow policy
    TableReportWindow *tw = nullptr;
    if (currentWindowPolicy == WindowPolicy::SingleWindow)
    {
        tabContainer = &singleWindow;
    }
    else
    { // GroupedWindow
        if (windowType == WindowType::SymbolSearch || windowType == WindowType::SymbolResult)
        {
            tabContainer = &groupSymbols;
        }
        else if (windowType == WindowType::GlobalDefinitions || windowType == WindowType::GlobalDefintionResult)
        {
            tabContainer = &groupGlobalDefinitions;
        }
        else
        {
            tabContainer = &groupFiles;
        }
    }
    // done selecting tab container, create tablereport
    if (windowType == WindowType::SymbolSearch || windowType == WindowType::SymbolResult)
    {
        tw = new TableReportWindow;
        TableReport *r;
        if (windowType == WindowType::SymbolSearch)
            r = new ReportSymList(*theProject, *this, tw);
        else // SymbolResult
            r = new ReportRefList(*theProject, symbolName, tw);

        tw->setTableReport(r);

        if (windowType == WindowType::SymbolSearch)
        {
            tw->setFilterBoxVisible(true);
            tw->resize(kReportSymListDefaultSize);
        }
    }
    else if (windowType == WindowType::GlobalDefinitions || windowType == WindowType::GlobalDefintionResult)
    {
        tw = new TableReportWindow;
        ReportDefList *r = new ReportDefList(*theProject, tw);
        tw->setTableReport(r);
        tw->setFilterBoxVisible(true);
        tw->resize(kReportDefListDefaultSize);
    }
    else // Files
    {
        tw = new TableReportWindow;
        ReportFileList *r = new ReportFileList(*theProject, tw);
        tw->setTableReport(r);
        tw->setFilterBoxVisible(true);
    }

    //if tab contianer set: add to it, else own window
    if (tabContainer != nullptr)
    {
        int idx = tabContainer->addTab(tw, symbolName);
        tabContainer->setCurrentIndex(idx);
        tabContainer->show();
    }
    else
    {
        tw->show();
    }
}
