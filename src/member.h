#ifndef MEMBER_H
#define MEMBER_H

#include <QtGui>
#include <QtSql>

#include "model/saldomodel.h"
#include "model/contributionmodel.h"

namespace membermanager
{

class Member
{
public:
    Member();
    Member(int anId);

    int getMemberId() const;
    QString getName() const;
    QString getFirstname() const;
    QString getNickname() const;
    QString getEmail() const;
    QString getStreet() const;
    QString getTown() const;
    QString getZipCode() const;
    QString getAccountNr() const;
    QString getBankName() const;
    QString getCode() const;

    QString getDonation() const;
    float getDonationAsFloat() const;
    QString getFee() const;
    float getFeeAsFloat() const;
    QString getContributionInfo() const;

    model::ContributionModel *getContributionModel() const;
    model::SaldoModel *getSaldoModel() const;

    void initAddressMapper(QDataWidgetMapper *aMapper) const;
    void initBankAccountMapper(QDataWidgetMapper *aMapper) const;
    void initRessourcenMapper(QDataWidgetMapper *aMapper) const;
    void initMemberMapper(QDataWidgetMapper *aMapper) const;

    void submitContribution(const QString &aFee, const QString &aDonation, const QString &anInfo);

private:
    void initModels();
    void initTableModel(const QString &aTablename, QSqlTableModel *const aModel);
    QString getValue(const QSqlTableModel *aModel, int aColumn) const;

    int id;

    QSqlTableModel *addressModel;
    QSqlTableModel *bankAccountModel;
    QSqlTableModel *ressourcenModel;
    QSqlTableModel *memberModel;
    model::ContributionModel *contributionModel;
    model::SaldoModel *saldoModel;

};

}

#endif // MEMBER_H
