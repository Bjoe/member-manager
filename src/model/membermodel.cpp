#include "membermodel.h"

#include "model/databasestructure.h"

namespace membermanager
{
namespace model
{

MemberModel::MemberModel(QObject *anObject, const QSqlDatabase &aDb) :
    model(new QSqlTableModel(anObject, aDb))
{
    model->setObjectName(MemberTable::TABLENAME);
    model->setTable(MemberTable::TABLENAME);
    model->setHeaderData(MemberTable::MemberId, Qt::Horizontal, QObject::tr("Nr."));
    model->removeColumn(MemberTable::Deleted);
    model->setHeaderData(MemberTable::FirstName -1, Qt::Horizontal, QObject::tr("Vorname"));
    model->setHeaderData(MemberTable::Name -1, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(MemberTable::NickName -1, Qt::Horizontal, QObject::tr("Nickname"));
    model->removeColumn(MemberTable::FOO_ClubAdress -1);
    model->removeColumn(MemberTable::FOO_intern -2);
    model->removeColumn(MemberTable::FOO_CCC -3);
    model->removeColumn(MemberTable::FOO_Shell -4);
    model->removeColumn(MemberTable::FOO_Einzug -5);
    model->removeColumn(MemberTable::FOO_ChaosNr -6);
    model->setHeaderData(MemberTable::EntryDate -7, Qt::Horizontal, QObject::tr("Eintritts Datum"));
    model->removeColumn(MemberTable::Info -7);
}

MemberModel::~MemberModel()
{
}

void MemberModel::setFilter(const QString aSqlFilter)
{
    model->setFilter(aSqlFilter);
    model->select();
}

int MemberModel::getMemberId(const QModelIndex &anIndex) const
{
    QSqlRecord record = model->record(anIndex.row());
    return record.value(MemberTable::MemberId).toInt();
}

QString MemberModel::getLastError() const
{
    return model->lastError().text();
}

QSqlTableModel* MemberModel::getModel()
{
    return model;
}

}
}
