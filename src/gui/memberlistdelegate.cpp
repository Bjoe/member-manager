#include "memberlistdelegate.h"

#include <QStringList>
#include <QComboBox>

#include "dao/databasestructure.h"
#include "accounting/contributionentry.h"
#include "member.h"

#include <QDebug>

namespace membermanager
{
namespace gui
{

MemberListDelegate::MemberListDelegate(QObject *aParent) :
    QStyledItemDelegate(aParent),
    memberDao(QSqlDatabase::database(), this),
    contributionDao(QSqlDatabase::database(), this),
    model(0)
{
    model = memberDao.modelSelectDeleted(false);
}

MemberListDelegate::~MemberListDelegate()
{
    delete model;
}

QWidget* MemberListDelegate::createEditor(QWidget *aParent, const QStyleOptionViewItem &anOption, const QModelIndex &anIndex) const
{
    qDebug() << "createEditor ";
    QComboBox *comboBox = new QComboBox(aParent);
    comboBox->setModel(model);
    comboBox->setModelColumn(dao::MemberTable::Name);
    return comboBox;
}

void MemberListDelegate::setEditorData(QWidget *anEditor, const QModelIndex &anIndex) const
{
    qDebug() << "setEditorData " << anIndex;
    QVariant variant = anIndex.data();

    QComboBox *comboBox = static_cast<QComboBox *>(anEditor);
    int index = comboBox->findData(variant, Qt::DisplayRole);
    comboBox->setCurrentIndex(index);
}

void MemberListDelegate::setModelData(QWidget *anEditor, QAbstractItemModel *aModel, const QModelIndex &anIndex) const
{
    QComboBox *comboBox = static_cast<QComboBox *>(anEditor);
    QString value = comboBox->currentText();
    aModel->setData(anIndex, value);

    int comboRow = comboBox->currentIndex();
    QModelIndex comboIndex = model->index(comboRow, dao::MemberTable::MemberId);
    int memberId = model->data(comboIndex).toInt();
    qDebug() << "setModelData " << memberId;
    accounting::ContributionEntry contributionEntry = contributionDao.findLastEntryByMemberId(memberId);

    int row = anIndex.row();
    QModelIndex index = aModel->index(row, 0);
    aModel->setData(index, memberId);
    index = aModel->index(row, 2);
    aModel->setData(index, contributionEntry.getFee());
    index = aModel->index(row, 3);
    aModel->setData(index, contributionEntry.getDonation());
    index = aModel->index(row, 4);
    aModel->setData(index, contributionEntry.getAdditionalFee());
}

} // namespace gui
} // namespace membermanager
