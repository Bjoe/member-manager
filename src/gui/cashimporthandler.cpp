#include "cashimporthandler.h"

#include <QDate>
#include <QSqlTableModel>
#include <QIODevice>
#include <QUrl>
#include <QTextStream>
#include <QFile>
#include <QSettings>

#include <QDebug>

#include "swift/importer.h"
#include "swift/transaction.h"

#include "accounting/cashimporter.h"
#include "dao/cashaccounttablemodel.h"

namespace membermanager {
namespace gui {

CashImportHandler::CashImportHandler(QObject *parent) :
    QObject(parent)
{
    QDate date = QDate::currentDate();
    m_year = date.year();
    refresh();
}

ProxyTableModel *CashImportHandler::cashProxyModel() const
{
    return m_cashProxyModel;
}

entity::CashAccount *CashImportHandler::cashAccount() const
{
    return m_cashAccount;
}

void CashImportHandler::selectYear(int year)
{
    m_year = year;
    QSqlTableModel* model = dao::CashAccountTableModel::createModel(m_year);
    m_cashProxyModel->setModel(model);
}

void CashImportHandler::refresh()
{
    selectYear(m_year);
    qDebug() << QString("Refresh: Selected row count: %1").arg(m_cashProxyModel->rowCount());
}

void CashImportHandler::selectedRow(int row)
{
    delete m_cashAccount;
    QSqlTableModel* model = m_cashProxyModel->getModel();
    m_cashAccount = dao::CashAccountTableModel::findBySelectedRow(model, row);
    emit cashAccountChanged();
}

void CashImportHandler::importFile(const QString &urlFilename)
{
    emit progress(0);
    QSettings settings;
    QString bankCode = settings.value("bank/code").toString();
    QString accountNumber = settings.value("bank/account").toString();
    if(accountNumber.isEmpty() || bankCode.isEmpty()) {
        emit statusMessage(QString("Wrong settings: account Nr: -%2- code: -%3-")
                           .arg(accountNumber)
                           .arg(bankCode));
        return;
    }

    QUrl url(urlFilename);
    QString filename = url.path();
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString error = file.errorString();
        emit statusMessage(QString("Error import SWIFT file: %1:%2").arg(urlFilename).arg(error));
        return;
    }
    QTextStream stream(&file);
    accounting::CashImporter importer(&stream);

    emit statusMessage("Importing SWIFT .... please wait");
    CashImportHandler* instance = this;
    importer.logMessageSlot(
        [instance](QString message)
        {
            emit instance->statusMessage(message);
        }
    );

    bool result = importer.import(bankCode, accountNumber);
    file.close();

    if(result) {
        emit statusMessage(QString("Imported SWIFT file: %1").arg(urlFilename));
        emit progress(1);
    }
    emit cashAccountModelChanged();
}

} // namespace gui
} // namespace membermanager
