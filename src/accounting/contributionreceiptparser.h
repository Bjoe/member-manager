#ifndef MEMBERMANAGER_ACCOUNTING_CONTRIBUTIONRECEIPTPARSER_H
#define MEMBERMANAGER_ACCOUNTING_CONTRIBUTIONRECEIPTPARSER_H

#include <QObject>
#include <QList>
#include <QTextStream>

#include "entity/member.h"

namespace membermanager {
namespace accounting {

class ContributionReceiptParser
{
public:
    ContributionReceiptParser(double sum, int year, const QList<QObject *>* list, const entity::Member* member);

    void parse(QTextStream &streamIn, QTextStream& streamOut);

private:
    double m_sum;
    int m_year;
    const QList<QObject *>* m_list;
    const entity::Member* m_member;
};

} // namespace accounting
} // namespace membermanager

#endif // MEMBERMANAGER_ACCOUNTING_CONTRIBUTIONRECEIPTPARSER_H
