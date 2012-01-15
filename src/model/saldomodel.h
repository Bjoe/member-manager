#ifndef SALDOMODEL_H_
#define SALDOMODEL_H_

#include <QtCore>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QTableView>
#include <QModelIndex>

#include "model/memberfilter.h"

namespace membermanager
{
namespace model
{

class SaldoModel
{
public:
    SaldoModel(int aMemberId, const QSqlDatabase &aDb = QSqlDatabase::database(), QObject *aParent = 0);
    virtual ~SaldoModel();

    int getMemberId() const;
    QSqlTableModel *getModel();

    double amount() const;
    QModelIndex insertNewRow();
    bool deleteRow(const QModelIndex &anIndex);

private:
    int memberId;
    QSqlTableModel *model;
};

}
}

#endif /* SALDOMODEL_H_ */
