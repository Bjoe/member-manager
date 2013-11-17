#ifndef MEMBERMANAGER_ACCOUNTING_CASHIMPORTER_H
#define MEMBERMANAGER_ACCOUNTING_CASHIMPORTER_H

#include <functional>

#include <QString>
#include <QTextStream>

#include "swift/importer.h"

namespace membermanager {
namespace accounting {

class CashImporter
{
public:
    CashImporter(QTextStream *stream);

    void logMessageSlot(std::function<void (QString)> logCb);

    bool import(const QString bankCode, const QString accountNumber);

private:
    std::function<void (QString)> m_logCb;
    QTextStream *m_stream;
};

} // namespace accounting
} // namespace membermanager

#endif // MEMBERMANAGER_ACCOUNTING_CASHIMPORTER_H
