#include "memberlistdelegatetest.h"

#include "gui/memberlistdelegate.h"

#include <QVariant>
#include <QString>
#include <QList>
#include <QStandardItem>
#include <QWidget>
#include <QComboBox>
#include <QStyleOptionViewItem>
#include <QModelIndex>
#include <QStandardItemModel>
#include <QSqlTableModel>

#include "testconfig.h"
#include "dao/databasestructure.h"
#include "dao/memberdao.h"

namespace membermanagertest
{
namespace gui
{

MemberListDelegateTest::MemberListDelegateTest() :
    database(DATABASEDRIVER)
{}

void MemberListDelegateTest::initTestCase()
{
    database.open(DATABASE);
}

void MemberListDelegateTest::initTest()
{
    database.read(SQLTESTFILE);
}

void MemberListDelegateTest::testCreateEditor()
{
    membermanager::gui::MemberListDelegate delegate;

    QStyleOptionViewItem item;
    QModelIndex index;
    QWidget *widget = delegate.createEditor(0, item, index);
    QComboBox *comboBox = qobject_cast<QComboBox *>(widget);

    QCOMPARE(comboBox->itemData(0, Qt::DisplayRole).toString(), QString("-"));
    QCOMPARE(comboBox->itemData(1, Qt::DisplayRole).toString(), QString("Kirk"));
    QCOMPARE(comboBox->itemData(2, Qt::DisplayRole).toString(), QString("Scott"));
}

void MemberListDelegateTest::testSetEditorData()
{
    QStyleOptionViewItem emptyItem;
    QModelIndex emptyIndex;

    membermanager::gui::MemberListDelegate delegate;
    QWidget *widget = delegate.createEditor(0, emptyItem, emptyIndex);
    QComboBox *comboBox = qobject_cast<QComboBox *>(widget);
    QStandardItemModel *testModel = new QStandardItemModel();
    QList<QStandardItem *> row0;
    row0.append(new QStandardItem("9999"));
    row0.append(new QStandardItem("foo"));
    row0.append(new QStandardItem("0"));
    row0.append(new QStandardItem("0"));
    row0.append(new QStandardItem("0"));
    testModel->insertRow(0, row0);
    QList<QStandardItem *> row1;
    row1.append(new QStandardItem("4321"));
    row1.append(new QStandardItem("McCoy"));
    row1.append(new QStandardItem("0"));
    row1.append(new QStandardItem("0"));
    row1.append(new QStandardItem("1"));
    testModel->insertRow(1, row1);
    QModelIndex index = testModel->index(1,1);

    delegate.setEditorData(comboBox, index);

    QCOMPARE(comboBox->currentIndex(), 3);
    QCOMPARE(comboBox->currentText(), QString("McCoy"));
}

void MemberListDelegateTest::testSetModelData()
{
    QStyleOptionViewItem emptyItem;
    QModelIndex emptyIndex;

    membermanager::gui::MemberListDelegate delegate;
    QWidget *widget = delegate.createEditor(0, emptyItem, emptyIndex);
    QComboBox *comboBox = qobject_cast<QComboBox *>(widget);
    comboBox->setCurrentIndex(1);

    QStandardItemModel *testModel = new QStandardItemModel();
    QList<QStandardItem *> row0;
    row0.append(new QStandardItem("9999"));
    row0.append(new QStandardItem("foo"));
    row0.append(new QStandardItem("0"));
    row0.append(new QStandardItem("0"));
    row0.append(new QStandardItem("0"));
    testModel->insertRow(0, row0);
    QList<QStandardItem *> row1;
    row1.append(new QStandardItem("4321"));
    row1.append(new QStandardItem("bar"));
    row1.append(new QStandardItem("0"));
    row1.append(new QStandardItem("0"));
    row1.append(new QStandardItem("1"));
    testModel->insertRow(1, row1);
    QModelIndex index = testModel->index(1,1);

    delegate.setModelData(comboBox, testModel, index);

    QCOMPARE(data(0, 0, testModel), QString("9999"));
    QCOMPARE(data(0, 1, testModel), QString("foo"));
    QCOMPARE(data(0, 2, testModel), QString("0"));
    QCOMPARE(data(0, 3, testModel), QString("0"));
    QCOMPARE(data(0, 4, testModel), QString("0"));
    QCOMPARE(data(1, 0, testModel), QString("1025"));
    QCOMPARE(data(1, 1, testModel), QString("Kirk"));
    QCOMPARE(data(1, 2, testModel), QString("99"));
    QCOMPARE(data(1, 3, testModel), QString("1.5"));
    QCOMPARE(data(1, 4, testModel), QString("0"));
}

QString MemberListDelegateTest::data(int aRow, int aColumn, QAbstractItemModel *aModel)
{
    QModelIndex index = aModel->index(aRow, aColumn);
    QVariant variant = aModel->data(index);
    return variant.toString();
}

} // namespace gui
} // namespace membermanagertest

QTEST_MAIN(membermanagertest::gui::MemberListDelegateTest)
#include "moc_memberlistdelegatetest.cpp"
