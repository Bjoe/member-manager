#ifndef MEMBERMANAGER_GUI_MEMBERLISTDELEGATE_H
#define MEMBERMANAGER_GUI_MEMBERLISTDELEGATE_H

#include <QWidget>
#include <QAbstractItemModel>
#include <QStyledItemDelegate>

#include "dao/memberdao.h"
#include "dao/contributiondao.h"

namespace membermanager
{
namespace gui
{

class MemberListDelegate : public QStyledItemDelegate
{
public:
    MemberListDelegate(QObject *aParent = 0);
    virtual ~MemberListDelegate();

    virtual QWidget* createEditor(QWidget *aParent, const QStyleOptionViewItem &anOption, const QModelIndex &anIndex) const;
    virtual void setEditorData(QWidget *anEditor, const QModelIndex &anIndex) const;
    virtual void setModelData(QWidget *anEditor, QAbstractItemModel *aModel, const QModelIndex &anIndex) const;

private:
    dao::MemberDao memberDao;
    dao::ContributionDao contributionDao;
    QAbstractItemModel *model;
};

} // namespace gui
} // namespace membermanager

#endif // MEMBERMANAGER_GUI_MEMBERLISTDELEGATE_H
