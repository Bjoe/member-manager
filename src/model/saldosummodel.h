#ifndef SALDOSUMMODEL_H
#define SALDOSUMMODEL_H

#include <QtCore>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QTableView>

namespace ClubFrontend
{
namespace Model
{

class SaldoSumModel : public QObject
{
public:
    SaldoSumModel(const QSqlDatabase &aDb);

    void initTableView(QTableView * const aView);

private:
    QSqlQueryModel *model;
};

}
}

#endif  /* // SALDOSUMMODEL_H */
