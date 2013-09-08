#include "databasemanager.h"

#include <QUrl>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>

#include "QDjango.h"

#include "config.h"

#include "entity/member.h"
#include "entity/contribution.h"
#include "entity/balance.h"
#include "entity/cashaccount.h"
#include "entity/bankaccount.h"

namespace membermanager {

DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent)
{
}

void DatabaseManager::onLoadSqlFile(QString filename)
{
    QUrl url(filename);
    QString database = url.path();

    QSqlDatabase db = QSqlDatabase::addDatabase(DATABASEDRIVER);
    db.setDatabaseName(database);
    if (!db.open()) {
        QSqlError err = db.lastError();
        if (err.type() != QSqlError::NoError) {
            QMessageBox::warning(0, QObject::tr("Unable to open database"),
                                 QObject::tr(
                                     "An error occured while opening the connection: ")
                                 + err.text());
            return;
        }
    }

    QDjango::setDatabase(db);

    QDjango::registerModel<membermanager::entity::Member>();
    QDjango::registerModel<membermanager::entity::Contribution>();
    QDjango::registerModel<membermanager::entity::Balance>();
    QDjango::registerModel<membermanager::entity::CashAccount>();
    QDjango::registerModel<membermanager::entity::BankAccount>();

    emit databaseReady();
}

} // namespace membermanager
