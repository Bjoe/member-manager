#include "feedebthandler.h"

#include "accounting/memberdebt.h"

#include "dao/membertablemodel.h"
#include "dao/balancetablemodel.h"

namespace membermanager {
namespace gui {

FeeDebtHandler::FeeDebtHandler(QObject *parent) :
    QObject(parent), m_memberState(entity::Member::State::active), m_debtModel()
{
}

QList<QObject *> FeeDebtHandler::debtModel() const
{
    return m_debtModel;
}

void FeeDebtHandler::setDebtModel(QList<QObject *> model)
{
    m_debtModel = model;
    emit debtModelChanged();
}

entity::Member::State FeeDebtHandler::memberState() const
{
    return m_memberState;
}

void FeeDebtHandler::setMemberState(entity::Member::State state)
{
    m_memberState = state;
    emit memberStateChanged();
}

void FeeDebtHandler::onCalculate()
{
    emit progress(0);
    emit statusMessage("Calculate in progress ... please wait");

    clearList();
    QList<entity::Member *> members = dao::MemberTableModel::findByState(m_memberState);

    double progressValue = 1/ members.size();
    for(const entity::Member *member : members) {
        double sum = dao::BalanceTableModel::calculateFeeSumByMemberId(member->memberId());
        if(sum < 0) {
            accounting::MemberDebt *memberDebt = new accounting::MemberDebt(this);
            QString memberId = QVariant(member->memberId()).toString();
            memberDebt->setMemberId(memberId);
            memberDebt->setFirstname(member->firstname());
            memberDebt->setName(member->name());
            memberDebt->setEmail(member->email());
            memberDebt->setDebit(sum);

            m_debtModel.append(memberDebt);
        }
        delete member;
        emit progress(progressValue);
    }

    emit debtModelChanged();
    emit statusMessage("Calculate done");
}

void FeeDebtHandler::clearList()
{
    for(const QObject *object : m_debtModel) {
        delete object;
    }
    m_debtModel.clear();
}

void FeeDebtHandler::onRefresh()
{
    clearList();
    emit debtModelChanged();
}


} // namespace gui
} // namespace membermanager
