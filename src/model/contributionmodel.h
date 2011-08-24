#ifndef CONTRIBUTIONMODEL_H
#define CONTRIBUTIONMODEL_H

#include <QtCore>
#include <QtSql>
#include <QTableView>

namespace ClubFrontend
{
namespace Model
{

class ContributionModel : public QObject
{
public:
    ContributionModel(const QSqlDatabase &aDb);
    virtual ~ContributionModel();

    void setMemberId(const int aMemberId);
    int insertMemberId(const QVariant &aMemberId);
    void refresh();

    void initTableView(QTableView *aTableView) const;

    QString getInfo() const;
    QVariant getInfoValue() const;
    QString getDonation() const;
    QVariant getDonationValue() const;
    QString getFee() const;
    QVariant getFeeValue() const;

    void submit(const QString &aFee, const QString &aDonation, const QString &anInfo);

private:
    QVariant returnValue(int aColumn) const;

    QSqlTableModel *model;
    QSqlRecord record;
    int memberId;
};

}
}

#endif // CONTRIBUTIONMODEL_H
