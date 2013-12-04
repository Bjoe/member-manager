#include "accountinghandler.h"

#include <QSettings>
#include <QTextStream>
#include <QUrl>
#include <QFile>
#include <QApplication>
#include <QCursor>
#include <QSharedPointer>

#include "dtaus/exporter.h"
#include "dtaus/transaction.h"

#include "entity/member.h"
#include "entity/bankaccount.h"
#include "entity/sepaaccount.h"
#include "entity/contribution.h"

#include "dao/membertablemodel.h"
#include "dao/bankaccounttablemodel.h"
#include "dao/sepaaccounttablemodel.h"
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
    emit progress(0);
    QSettings settings;
    QString bankAccountNumber = settings.value("bank/account").toString();
    QString bankName = settings.value("bank/name").toString();
    QString bankCode = settings.value("bank/code").toString();

    QString name = settings.value("name").toString();
    QString creditorId = settings.value("creditorId").toString();
    QString bic = settings.value("sepa/bic").toString();
    QString iban = settings.value("sepa/iban").toString();

    if(bankAccountNumber.isEmpty() || bankName.isEmpty() || bankCode.isEmpty() ||
            name.isEmpty() || creditorId.isEmpty() || bic.isEmpty() || iban.isEmpty()) {
        emit statusMessage(QString("Wrong settings: BIC -%1- IBAN -%2- Name -%3- Creditor Id -%4- Bank name -%5- account Nr: -%6- code: -%7-")
                           .arg(bic)
                           .arg(iban)
                           .arg(name)
                           .arg(creditorId)
                           .arg(bankName)
                           .arg(bankAccountNumber)
                           .arg(bankCode));
        return;
    }

    QUrl url(urlFilename);
    QString filename = url.path();

    QString csvFilename = QString("%1.csv").arg(filename);
    QFile csvFile(csvFilename);
    if(! csvFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QString error = csvFile.errorString();
        emit statusMessage(QString("Cant save %1:%2").arg(csvFilename).arg(error));
        return;
    }

    QString dtausFilename = QString("%1.txt").arg(filename);
    QFile dtausFile(dtausFilename);
    if(! dtausFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QString error = dtausFile.errorString();
        emit statusMessage(QString("Cant save %1:%2").arg(dtausFilename).arg(error));
        csvFile.close();
        return;
    }

    QString sepaFilename = QString("%1.xml").arg(filename);
    QFile sepaFile(sepaFilename);
    if(! sepaFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QString error = sepaFile.errorString();
        emit statusMessage(QString("Cant save SEPA %1:%2").arg(sepaFilename).arg(error));
        dtausFile.close();
        csvFile.close();
        return;
    }

    QTextStream stream(&csvFile);
    accounting::AccountTransaction transaction(bankAccountNumber, bankCode, bankName,
                                               name, creditorId, iban, bic, stream);

    qaqbanking::sepa::Exporter sepaExporter(iban, bic, name);
    qaqbanking::dtaus::Exporter exporter(bankAccountNumber, bankName,bankCode, "EUR");

    connect(&sepaExporter, &qaqbanking::sepa::Exporter::logMessage, this, &AccountingHandler::statusMessage);
    connect(&exporter, &qaqbanking::dtaus::Exporter::logMessage, this, &AccountingHandler::statusMessage);

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    emit statusMessage("Booking in progess ... please wait");
    double progressValue = 1/m_memberAccountingDataList.size();

    for(QObject* object : m_memberAccountingDataList) {

        accounting::MemberAccountingData* data = qobject_cast<accounting::MemberAccountingData *>(object);
        transaction.accounting(data);

        if(data->canCharge()) {
            qaqbanking::sepa::TransactionPtr sepaTransaction = transaction.createSepaTransaction(data);
            sepaExporter.addTransaction(sepaTransaction);

            qaqbanking::dtaus::TransactionPtr dtausTransaction = transaction.createDtausTransaction(data);
            exporter.addTransaction(dtausTransaction);

            transaction.collectionAccounting(data);
        }
        emit progress(progressValue);
    }

    QTextStream dtausStream(&dtausFile);
    exporter.createDtausStream(&dtausStream);

    QTextStream sepaStream(&sepaFile);
    sepaExporter.createSepaDirectDebitStream(&sepaStream);

    csvFile.close();
    dtausFile.close();
    sepaFile.close();
    emit statusMessage("Booking done");
    emit progress(1);
    QApplication::restoreOverrideCursor();
}

void AccountingHandler::onRefresh()
{
    clearList();

    QSettings settings;
    int accountingReference = settings.value("accounting/reference", 0).toInt();

    QList<entity::Member *> memberList = dao::MemberTableModel::findByState(entity::Member::State::active);
    for(const entity::Member* member : memberList) {
        QString memberId = member->memberId();
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

        entity::BankAccount *bankAccount = dao::BankAccountTableModel::findByMemberId(memberId);
        data->setBankAccountNumber(bankAccount->accountNumber());
        data->setBankCode(bankAccount->code());

        entity::SepaAccount *sepaAccount = dao::SepaAccountTableModel::findByMemberId(memberId);
        data->setSepaBic(sepaAccount->bic());
        data->setSepaIban(sepaAccount->iban());
        data->setSepaMandateDate(sepaAccount->mandateDate());
        data->setSepaSequenceState(sepaAccount->sequenceState());

        entity::Contribution *contribution = dao::ContributionTableModel::findByMemberIdWithPointInTime(memberId, m_valuta);
        data->setFee(contribution->fee());
        data->setDonation(contribution->donation());
        data->setAdditionalFee(contribution->additionalFee());
        data->setAdditionalDonation(contribution->additionalDonation());
        data->setAmortization(contribution->amortization());

        data->setAccountingReference(QString("%1").arg(++accountingReference));

        m_memberAccountingDataList.append(data);

        delete bankAccount;
        delete sepaAccount;
        delete contribution;
        delete member;
    }
    settings.setValue("accounting/reference", accountingReference);

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
