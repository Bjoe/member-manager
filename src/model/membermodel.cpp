#include "membermodel.h"

#include "model/databasestructure.h"

namespace membermanager
{
namespace model
{

MemberModel::MemberModel(const QSqlDatabase &aDb) :
    model(new QSqlTableModel(this, aDb))
{
    model->setObjectName(MemberTable::TABLENAME);
    model->setTable(MemberTable::TABLENAME);
    model->setHeaderData(MemberTable::MemberId, Qt::Horizontal, tr("Nr."));
    model->setHeaderData(MemberTable::FirstName, Qt::Horizontal, tr("Vorname"));
    model->setHeaderData(MemberTable::Name, Qt::Horizontal, tr("Name"));
    model->setHeaderData(MemberTable::NickName, Qt::Horizontal, tr("Nickname"));
    model->setHeaderData(MemberTable::EntryDate, Qt::Horizontal, tr("Eintritts Datum"));
    refresh();
}

MemberModel::~MemberModel()
{
    delete model;
}

void MemberModel::setFilter(const QString aSqlFilter)
{
    model->setFilter(aSqlFilter);
    refresh();
}

void MemberModel::refresh()
{
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

void MemberModel::initTableView(QTableView *aTableView) const
{
    aTableView->setModel(model);
    aTableView->setColumnHidden(MemberTable::Deleted, true);
    aTableView->setColumnHidden(MemberTable::Info, true);
    aTableView->setColumnHidden(MemberTable::FOO_CCC, true);
    aTableView->setColumnHidden(MemberTable::FOO_ChaosNr, true);
    aTableView->setColumnHidden(MemberTable::FOO_ClubAdress, true);
    aTableView->setColumnHidden(MemberTable::FOO_Einzug, true);
    aTableView->setColumnHidden(MemberTable::FOO_intern, true);
    aTableView->setColumnHidden(MemberTable::FOO_Shell, true);

    aTableView->sortByColumn(MemberTable::MemberId, Qt::AscendingOrder);
}

}
}
