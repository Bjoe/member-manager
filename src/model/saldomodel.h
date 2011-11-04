#ifndef SALDOMODEL_H_
#define SALDOMODEL_H_

#include <QtCore>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QTableView>

namespace membermanager
{
namespace model
{

class SaldoModel: public QObject
{
public:
    SaldoModel(int anId, const QSqlDatabase &aDb = QSqlDatabase::database());
    virtual ~SaldoModel();

    double amount() const;
    void initTableView(QTableView *aTableView) const;

private:
    QSqlTableModel *model;
};

}
}

#endif /* SALDOMODEL_H_ */
