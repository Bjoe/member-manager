#include "contributionreceipthandler.h"

#include <QList>

#include "entity/member.h"
#include "entity/balance.h"
#include "dao/membertablemodel.h"
#include "dao/balancetablemodel.h"

namespace membermanager {
namespace gui {

ContributionReceiptHandler::ContributionReceiptHandler(QObject *parent) :
    QObject(parent)
{
}

ContributionReceiptHandler::~ContributionReceiptHandler()
{
    clearList();
}

void ContributionReceiptHandler::createReceipt(QVariant memberId, int year)
{
    clearList();
    m_balanceList = dao::BalanceTableModel::findContributionByMemberIdAndYear(memberId, year);
    emit balanceListChanged();
}

void ContributionReceiptHandler::clearList()
{
    for(QObject *object : m_balanceList) {
        delete object;
    }
    m_balanceList.clear();
}

QList<QObject *> ContributionReceiptHandler::balanceList() const
{
    return m_balanceList;
}

void ContributionReceiptHandler::setBalanceList(const QList<QObject *> &balanceList)
{
    m_balanceList = balanceList;
}

} // namespace gui
} // namespace membermanager
