#ifndef SALDOMODEL_H_
#define SALDOMODEL_H_

#include <QtCore>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QTableView>

namespace ClubFrontend
{
namespace Model
{

class SaldoModel: public QObject
{
public:
    SaldoModel(const QSqlDatabase &aDb = QSqlDatabase::database());
    virtual ~SaldoModel();

    void setMemberId(const int aMemberId);
    float amount() const;
    void refresh();

    void initTableView(QTableView *aTableView) const;

private:
    QSqlTableModel *model;
};

}
}

#endif /* SALDOMODEL_H_ */
