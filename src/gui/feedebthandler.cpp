#include "feedebthandler.h"

#include <QSettings>
#include <QClipboard>
#include <QApplication>

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

bool FeeDebtHandler::isInactive() const
{
    if(m_memberState == entity::Member::State::inactive) {
        return true;
    } else {
        return false;
    }
}

void FeeDebtHandler::setBoolMemberState(bool isInactive)
{
    m_memberState = entity::Member::State::active;
    if(isInactive) {
        m_memberState = entity::Member::State::inactive;
    }
    emit memberStateChanged();
}

void FeeDebtHandler::copyToClipboard(int row)
{
    const QObject* object = m_debtModel.at(row);
    const accounting::MemberDebt* member = qobject_cast<const accounting::MemberDebt* >(object);

    QSettings settings;
    QString name = settings.value("main/name").toString();
    QString bic = settings.value("sepa/bic").toString();
    QString iban = settings.value("sepa/iban").toString();

    QString text;
    text.append(QString("To: %1").arg(member->email()));
    text.append("\n");
    text.append(tr("Subject: Chaosdorf Mitgliedsbeitrag Kontostand"));
    text.append("\n");
    text.append("\n");
    text.append(QString("Hallo %1,").arg(member->firstname()));
    text.append("\n");
    text.append("\n");
    text.append(tr("leider weist dein Mitgliedskontostand ein Sollwert von"));
    text.append(QString(" %L1 EUR ").arg(member->debit(), 4, 'f', 2));
    text.append(tr("auf."));
    text.append("\n");
    text.append(tr("Bitte zahle uns den ausstehenden Beitrag von"));
    text.append(QString(" %L1 EUR ").arg((member->debit() * -1), 4, 'f', 2));
    text.append(tr("auf"));
    text.append("\n");
    text.append(tr("folgendes Vereins Konto ein:"));
    text.append("\n");
    text.append(QString("Name: %1").arg(name));
    text.append("\n");
    text.append(QString("IBAN: %1").arg(iban));
    text.append("\n");
    text.append(QString("BIC: %1").arg(bic));
    text.append("\n");
    text.append("\n");
    text.append(tr("Als Referenz/MandateId bitte folgendes Eintragen:"));
    text.append("\n");
    text.append(QString("%1").arg(member->memberId()));
    text.append("\n");
    text.append("\n");
    text.append(tr("Sollte es Probleme oder Fragen geben, dann wende dich bitte"));
    text.append("\n");
    text.append(tr("schnellstmoeglich an den Chaosdorf Vorstand"));
    text.append("\n");
    text.append(tr("Chaosdorf Vorstand <vorstand@chaosdorf.de>"));
    text.append("\n");
    text.append("\n");
    text.append(tr("Diese Email wurde automatisch generiert und verschickt"));
    text.append("\n");

    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(text);
}

void FeeDebtHandler::copyAllToClipboard()
{
    QString text("Rueckstand\tName\tVorname\tEmail\n");
    for(const QObject* object : m_debtModel) {
        const accounting::MemberDebt* member = qobject_cast<const accounting::MemberDebt* >(object);
        text.append(QString("%L1 EUR\t%2\t%3\t%4\n")
                    .arg(member->debit(), 4, 'f', 2)
                    .arg(member->name())
                    .arg(member->firstname())
                    .arg(member->email()));
    }

    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(text);
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
            QString memberId = member->memberId();
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
