#ifndef MEMBERMANAGER_ENTITY_MEMBER_H
#define MEMBERMANAGER_ENTITY_MEMBER_H

#include <QtCore/QString>
#include <QtCore/QDate>

#include "QDjangoModel.h"

namespace membermanager {
namespace entity {

class Member : public QDjangoModel
{
    Q_OBJECT

    Q_CLASSINFO("__meta__", "db_table=Member")
    Q_CLASSINFO("memberId", "db_index=true unique=true")
    Q_CLASSINFO("nickname", "null=true")
    Q_CLASSINFO("cancellationDate", "null=true")
    Q_CLASSINFO("info", "null=true")
    Q_CLASSINFO("reference", "null=true")

    Q_PROPERTY(QString memberId READ memberId WRITE setMemberId NOTIFY memberIdChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString firstname READ firstname WRITE setFirstname NOTIFY firstnameChanged)
    Q_PROPERTY(QString nickname READ nickname WRITE setNickname NOTIFY nicknameChanged)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(QDate entryDate READ entryDate WRITE setEntryDate NOTIFY entryDateChanged)
    Q_PROPERTY(QDate cancellationDate READ cancellationDate WRITE setCancellationDate NOTIFY cancellationDateChanged)
    Q_PROPERTY(QString info READ info WRITE setInfo NOTIFY infoChanged)
    Q_PROPERTY(QString reference READ reference WRITE setReference NOTIFY referenceChanged)
    Q_PROPERTY(QString street READ street WRITE setStreet NOTIFY streetChanged)
    Q_PROPERTY(QString city READ city WRITE setCity NOTIFY cityChanged)
    Q_PROPERTY(QString zipCode READ zipCode WRITE setZipCode NOTIFY zipCodeChanged)
    Q_PROPERTY(QString collectionState READ collectionState WRITE setCollectionState NOTIFY collectionStateChanged)
    Q_PROPERTY(QString state READ state WRITE setState NOTIFY stateChanged)

    Q_ENUMS(membermanager::entity::Member::State)
    Q_ENUMS(membermanager::entity::Member::CollectionState)

public:

    enum class State : char { active='A', inactive='I', deleted='D' };
    enum class CollectionState : char { known='K', pause='P', notKnown='N' };

    QString memberId() const;
    void setMemberId(QString id);

    QString name() const;
    void setName(const QString &name);

    QString firstname() const;
    void setFirstname(const QString &name);

    QString nickname() const;
    void setNickname(const QString &name);

    QString email() const;
    void setEmail(const QString &email);

    QDate entryDate() const;
    void setEntryDate(const QDate &date);

    QDate cancellationDate() const;
    void setCancellationDate(const QDate &date);

    QString info() const;
    void setInfo(const QString &info);

    QString reference() const;
    void setReference(const QString &reference);

    QString street() const;
    void setStreet(const QString &street);

    QString city() const;
    void setCity(const QString &city);

    QString zipCode() const;
    void setZipCode(const QString &code);

    QString collectionState() const;
    void setCollectionState(QString state);
    void setCollectionState(CollectionState state);

    QString state() const;
    void setState(QString state);
    void setState(State state);

signals:
    void memberIdChanged();
    void nameChanged();
    void firstnameChanged();
    void nicknameChanged();
    void emailChanged();
    void entryDateChanged();
    void cancellationDateChanged();
    void infoChanged();
    void referenceChanged();
    void streetChanged();
    void cityChanged();
    void zipCodeChanged();
    void collectionStateChanged();
    void stateChanged();

private:
    QString m_memberId {};
    QString m_name {};
    QString m_firstname {};
    QString m_nickname {};
    QString m_email {};
    QDate m_entryDate {};
    QDate m_cancellationDate {};
    QString m_info {};
    QString m_reference {};
    QString m_street {};
    QString m_city {};
    QString m_zipCode {};
    QString m_state {};
    QString m_collectionState {};
};

} // namespace entity
} // namespace membermanager

Q_DECLARE_METATYPE(membermanager::entity::Member::State)
Q_DECLARE_METATYPE(membermanager::entity::Member::CollectionState)

#endif // MEMBERMANAGER_ENTITY_MEMBER_H
