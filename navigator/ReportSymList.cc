#include "ReportSymList.h"

#include <QObject>
#include <QString>
#include <QStringList>
#include <cassert>
#include <string>

#include "Project.h"
#include "ReportRefList.h"
#include "ReportWindowFactory.h"
#include "TableReport.h"
#include "TableReportWindow.h"

namespace Nav {

ReportSymList::ReportSymList(Project &project, ReportWindowFactory& reportFactory, QObject *parent) :
    TableReport(parent),
    m_project(project),
    m_reportFactory(reportFactory)
{
}

QString ReportSymList::title()
{
    return "Symbols";
}

QStringList ReportSymList::columns()
{
    QStringList ret;
    ret << "Symbol";
    ret << "Type";
    return ret;
}

int ReportSymList::rowCount()
{
    return m_project.symbolStringTable().size();
}

const char *ReportSymList::text(int row, int column, std::string &tempBuf)
{
    if (column == 0) {
        return m_project.symbolStringTable().item(row);
    } else if (column == 1) {
        return m_project.getSymbolType(m_project.querySymbolType(row));
    } else {
        assert(false && "Invalid column");
    }
}

int ReportSymList::compare(int row1, int row2, int col)
{
    if (col == 0) {
        return row1 - row2;
    } else if (col == 1) {
        return static_cast<int>(m_project.querySymbolType(row1)) -
                static_cast<int>(m_project.querySymbolType(row2));
    } else {
        assert(false && "Invalid column");
    }
}

bool ReportSymList::activate(int row)
{
    m_reportFactory.openWindow(ReportWindowFactory::WindowType::SymbolResult, m_project.symbolStringTable().item(row));
    return false;
}

} // namespace Nav
