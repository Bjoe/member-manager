#ifndef MEMBERMANAGER_GUI_MEMBERLISTDELEGATE_H
#define MEMBERMANAGER_GUI_MEMBERLISTDELEGATE_H

#include <QWidget>
#include <QStyledItemDelegate>

namespace membermanager
{
namespace gui
{

class MemberListDelegate : public QStyledItemDelegate
{
public:
    MemberListDelegate(QObject *aParent = 0);
    virtual ~MemberListDelegate() {}

    virtual QWidget* createEditor(QWidget *aParent, const QStyleOptionViewItem &anOption, const QModelIndex &anIndex) const;
};

} // namespace gui
} // namespace membermanager

#endif // MEMBERMANAGER_GUI_MEMBERLISTDELEGATE_H
