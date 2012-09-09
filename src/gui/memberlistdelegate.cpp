#include "memberlistdelegate.h"

#include <QStringList>
#include <QComboBox>

namespace membermanager
{
namespace gui
{

MemberListDelegate::MemberListDelegate(QObject *aParent) : QStyledItemDelegate(aParent)
{
}

QWidget* MemberListDelegate::createEditor(QWidget *aParent, const QStyleOptionViewItem &anOption, const QModelIndex &anIndex) const
{
    QStringList stringList;
    stringList << "foo" << "bar";
    QComboBox *comboBox = new QComboBox(aParent);
    comboBox->addItems(stringList);
    return comboBox;
}

} // namespace gui
} // namespace membermanager
