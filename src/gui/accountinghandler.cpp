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

#include "accounting/accountingdatacreator.h"
#include "accounting/memberaccountingdata.h"
#include "accounting/accounttransaction.h"
#include "accounting/transactionexporter.h"

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

    accounting::TransactionExporter transactionExporter(creditorId, iban, bic, name,
                                                        bankAccountNumber, bankName, bankCode);
    accounting::AccountTransaction transaction;

    connect(&transactionExporter, &accounting::TransactionExporter::logMessage, this, &AccountingHandler::statusMessage);

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    emit statusMessage("Booking in progess ... please wait");
    double progressValue = 1/m_memberAccountingDataList.size();

    for(QObject* object : m_memberAccountingDataList) {
        accounting::MemberAccountingData* data = qobject_cast<accounting::MemberAccountingData *>(object);

        transaction.accounting(data);

        if(data->canCharge()) {
            transactionExporter.addTransaction(data);
            transaction.collectionAccounting(data);
        }
        emit progress(progressValue);
    }

    QTextStream stream(&csvFile);
    QTextStream dtausStream(&dtausFile);
    QTextStream sepaStream(&sepaFile);
    transactionExporter.out(sepaStream, dtausStream, stream);
    csvFile.close();
    dtausFile.close();
    sepaFile.close();

    transaction.commit();

    emit statusMessage("Booking done");
    emit progress(1);
    QApplication::restoreOverrideCursor();
}

void AccountingHandler::onRefresh()
{
    clearList();

    QSettings settings;
    int accountingReference = settings.value("accounting/reference", 0).toInt();

    accounting::AccountingDataCreator accountingCreator(m_valuta, m_purpose, m_accountingInfo, accountingReference);

    QList<entity::Member *> memberList = dao::MemberTableModel::findByState(entity::Member::State::active);
    for(const entity::Member* member : memberList) {

        accounting::MemberAccountingData* data = accountingCreator.create(member);
        m_memberAccountingDataList.append(data);
        delete member;
    }
    settings.setValue("accounting/reference", accountingCreator.getAccountingReference());

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
