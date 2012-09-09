#include "memberlistdelegatetest.h"

#include "gui/memberlistdelegate.h"

#include <QVariant>
#include <QString>
#include <QWidget>
#include <QComboBox>
#include <QStyleOptionViewItem>
#include <QModelIndex>

namespace membermanagertest
{
namespace gui
{

void MemberListDelegateTest::testCreateEditor()
{
    membermanager::gui::MemberListDelegate delegate;

    QStyleOptionViewItem item;
    QModelIndex index;
    QWidget *widget = delegate.createEditor(0, item, index);
    QComboBox *comboBox = dynamic_cast<QComboBox *>(widget);

    QCOMPARE(comboBox->itemData(0, Qt::DisplayRole).toString(), QString("foo"));
    QCOMPARE(comboBox->itemData(1, Qt::DisplayRole).toString(), QString("bar"));
}

} // namespace gui
} // namespace membermanagertest

QTEST_MAIN(membermanagertest::gui::MemberListDelegateTest)
#include "memberlistdelegatetest.moc"
