#include "accountinghandler.h"

#include <QSettings>
#include <QTextStream>
#include <QUrl>
#include <QFile>
#include <QApplication>
#include <QCursor>

#include "dtaus/exporter.h"
#include "dtaus/transaction.h"

#include "entity/member.h"
#include "entity/bankaccount.h"
#include "entity/contribution.h"

#include "dao/membertablemodel.h"
#include "dao/bankaccounttablemodel.h"
#include "dao/contributiontablemodel.h"

#include "accounting/memberaccountingdata.h"
#include "accounting/accounttransaction.h"

namespace membermanager {
namespace gui {

AccountingHandler::AccountingHandler(QObject *parent) :
    QObject(parent), m_valuta(QDate::currentDate())
{
}

AccountingHandler::~AccountingHandler()
{
    clearList();
}

void AccountingHandler::setValuta(const QDate &date)
{
    m_valuta = date;
    emit valutaChanged();
}

QDate AccountingHandler::valuta() const
{
    return m_valuta;
}

void AccountingHandler::setPurpose(const QString &text)
{
    m_purpose = text;
    emit purposeChanged();
}

QString AccountingHandler::purpose() const
{
    return m_purpose;
}

void AccountingHandler::setAccountingInfo(const QString &text)
{
    m_accountingInfo = text;
    emit accountingInfoChanged();
}

QString AccountingHandler::accountingInfo() const
{
    return m_accountingInfo;
}

void AccountingHandler::setAccountingDataList(const QList<QObject *> &list)
{
    m_memberAccountingDataList = list;
    emit accountingDataListChanged();
}

QList<QObject *> AccountingHandler::accountingDataList() const
{
    return m_memberAccountingDataList;
}

void AccountingHandler::book(const QString &urlFilename)
{
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    emit progress(0);
    emit statusMessage("Booking in progess ... please wait");

    QUrl url(urlFilename);
    QString filename = url.path();
    QString csvFilename = QString("%1.csv").arg(filename);
    QFile csvFile(csvFilename);

    if(! csvFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QString error = csvFile.errorString();
        emit statusMessage(QString("Cant save %1:%2").arg(csvFilename).arg(error));
        QApplication::restoreOverrideCursor();
        return;
    }

    QTextStream stream(&csvFile);

    QSettings settings;
    QString bankAccountNumber = settings.value("bank/account").toString();
    QString bankName = settings.value("bank/name").toString();
    QString bankCode = settings.value("bank/code").toString();

    accounting::AccountTransaction transaction(bankAccountNumber, bankCode, bankName, stream);

    qiabanking::dtaus::Exporter exporter(bankAccountNumber, bankName,bankCode, "EUR");

    double progressValue = 1/m_memberAccountingDataList.size();
    for(QObject* object : m_memberAccountingDataList) {
        accounting::MemberAccountingData* data = qobject_cast<accounting::MemberAccountingData *>(object);

        transaction.accounting(data);

        if(data->canCharge()) {
            qiabanking::dtaus::Transaction dtausTransaction = transaction.createDtausTransaction(data);
            exporter.addTransaction(dtausTransaction);
            transaction.collectionAccounting(data);
        }
        emit progress(progressValue);
    }

    QString dtausFilename = QString("%1.txt").arg(filename);
    exporter.createDtausFile(dtausFilename);

    emit statusMessage("Booking done");
    emit progress(1);
    QApplication::restoreOverrideCursor();
}

void AccountingHandler::onRefresh()
{
    clearList();

    QList<entity::Member *> memberList = dao::MemberTableModel::findByState(entity::Member::State::active);
    for(const entity::Member* member : memberList) {
        QString memberId = QString::number(member->memberId());
        accounting::MemberAccountingData* data = new accounting::MemberAccountingData(this);
        data->setValuta(m_valuta);
        data->setAccountingInfo(m_accountingInfo);
        data->setPurpose(m_purpose);
        data->setMemberId(memberId);
        data->setName(member->name());
        data->setFirstname(member->firstname());
        QString collectionState = member->collectionState();
        if(! collectionState.isEmpty())
            data->setCollectionState(collectionState.at(0));

        entity::BankAccount *bankaccount = dao::BankAccountTableModel::findByMemberId(memberId);
        data->setBankAccountNumber(bankaccount->accountNumber());
        data->setBankCode(bankaccount->code());

        entity::Contribution *contribution = dao::ContributionTableModel::findByMemberIdWithPointInTime(memberId, m_valuta);
        data->setFee(contribution->fee());
        data->setDonation(contribution->donation());
        data->setAdditionalFee(contribution->additionalFee());
        data->setAdditionalDonation(contribution->additionalDonation());
        data->setAmortization(contribution->amortization());

        m_memberAccountingDataList.append(data);

        delete bankaccount;
        delete contribution;
        delete member;
    }

    emit accountingDataListChanged();
}

void AccountingHandler::clearList()
{
    for(const QObject* object : m_memberAccountingDataList) {
        delete object;
    }
    m_memberAccountingDataList.clear();
}

} // namespace gui
} // namespace membermanager
