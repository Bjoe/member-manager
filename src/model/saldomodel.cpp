#include "model/saldomodel.h"

#include "model/databasestructure.h"

#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QVariant>

#include "model/memberfilter.h"

namespace membermanager
{
namespace model
{

SaldoModel::SaldoModel(int aMemberId, const QSqlDatabase &aDb, QObject *aParent) :
    memberId(aMemberId), model(new QSqlTableModel(aParent, aDb))
{
    model->setObjectName(SaldoTable::TABLENAME);
    model->setTable(SaldoTable::TABLENAME);
    model->setHeaderData(SaldoTable::betrag, Qt::Horizontal, aParent->tr("Betrag"));
    model->setHeaderData(SaldoTable::datum, Qt::Horizontal, aParent->tr("Valuta Datum"));
    model->setHeaderData(SaldoTable::bezeichnung, Qt::Horizontal, aParent->tr("Bezeichnung"));
    model->removeColumn(SaldoTable::barkonto);
    model->setHeaderData(SaldoTable::konten -1, Qt::Horizontal, aParent->tr("Konten"));
    model->setHeaderData(SaldoTable::kasse_pkey -1, Qt::Horizontal, aParent->tr("Kassa Id"));
    model->setHeaderData(SaldoTable::info -1, Qt::Horizontal, aParent->tr("Info"));

    MemberFilter filter = MemberFilter::build().withMemberId(memberId);
    model->setFilter(filter.createFilter());
    model->sort(SaldoTable::datum, Qt::DescendingOrder);
    model->select();
}

SaldoModel::~SaldoModel()
{
}

int SaldoModel::getMemberId() const
{
    return memberId;
}

double SaldoModel::amount() const
{
    double sum = 0;
    for(int row = 0; row < model->rowCount(); row++) {
        QModelIndex index = model->index(row, SaldoTable::betrag);
        QVariant variant = index.data();
        sum += variant.toFloat();
    }
    return sum;
}

QSqlTableModel *SaldoModel::getModel()
{
    return model;
}

QModelIndex SaldoModel::insertNewRow()
{
    int row = model->rowCount();
    model->insertRow(row);
    model->setData(model->index(row, SaldoTable::dorfmitglied_pkey), getMemberId());
    model->submitAll();
    /// \todo model.lastError();
    return model->index(row, SaldoTable::betrag);
}

bool SaldoModel::deleteRow(const QModelIndex &anIndex)
{
    return model->removeRow(anIndex.row());
    /// \todo model.lastError();
}

}
}
