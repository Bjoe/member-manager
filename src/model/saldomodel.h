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
    SaldoModel(const MemberFilter &aFilter, const QSqlDatabase &aDb = QSqlDatabase::database(), QObject *aParent = 0);
    virtual ~SaldoModel();

    void initTableView(QTableView *aTableView) const;
    QString getMemberId() const;
    double amount() const;
    QModelIndex insertNewRow();
    bool deleteRow(const QModelIndex &anIndex);

private:
    QSqlTableModel *model;
};

}
}

#endif /* SALDOMODEL_H_ */
