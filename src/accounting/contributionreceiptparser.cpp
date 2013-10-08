#include "contributionreceiptparser.h"

#include <QRegExp>

#include "entity/balance.h"

namespace membermanager {
namespace accounting {

ContributionReceiptParser::ContributionReceiptParser(double sum, int year, const QList<QObject *>* list, const entity::Member* member)
    : m_sum(sum), m_year(year), m_list(list), m_member(member)
{
}

void ContributionReceiptParser::parse(QTextStream& streamIn, QTextStream& streamOut)
{
    QRegExp regExp("88\\.88\\.8888 \\& 99,00 Euro \\& Mitgliedsbeitrag oder Geldzuwendugen");

    while(! streamIn.atEnd()) {
        QString line = streamIn.readLine();
        line.replace(QString("Mustermann"), m_member->name());
        line.replace(QString("Mustername"), m_member->firstname());
        line.replace(QString("Musterstraße 23"), m_member->street());
        line.replace(QString("12345 Musterstadt"), QString("%1 %2").arg(m_member->zipCode()).arg(m_member->city()));
        line.replace(QString("11.11.1111"), QString("01.01.%1").arg(m_year));
        line.replace(QString("99.99.9999"), QString("31.12.%1").arg(m_year));
        line.replace(QString("23,00"), QString("%L1").arg(m_sum, 7, 'f', 2));
        line.replace(QString("DREIUNDZWANZIG"), QString("\\Huge{Bitte ausfuellen}"));

        if(regExp.exactMatch(line)) {
            for(const QObject* object : *m_list) {
                const entity::Balance* balance = qobject_cast<const entity::Balance* >(object);

                QDate valuta = balance->valuta();
                QString balanceLine = QString("%1 & %L2 Euro & %3\\\\")
                        .arg(valuta.toString("dd.MM.yyyy"))
                        .arg(balance->value(), 7, 'f', 2, ' ')
                        .arg(balance->purpose());

                streamOut << balanceLine << "\n"; /// TODO OS carrier return;
            }
        } else {
            streamOut << line << "\n"; /// TODO OS carrier return
        }
    }
}

} // namespace accounting
} // namespace membermanager
