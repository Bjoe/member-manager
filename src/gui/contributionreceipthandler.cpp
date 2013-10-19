#include "contributionreceipthandler.h"

#include <QList>
#include <QUrl>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QRegExp>

#include <QDebug>

#include "entity/balance.h"
#include "entity/member.h"
#include "dao/membertablemodel.h"
#include "dao/balancetablemodel.h"

#include "accounting/contributionreceiptparser.h"

namespace membermanager {
namespace gui {

ContributionReceiptHandler::ContributionReceiptHandler(QObject *parent) :
    QObject(parent)
{
}

ContributionReceiptHandler::~ContributionReceiptHandler()
{
    clearList();
}

void ContributionReceiptHandler::createReceipt(QVariant memberId, int year)
{
    clearList();
    m_balanceList = dao::BalanceTableModel::findContributionByMemberIdAndYear(memberId, year);
    setSum(calculateSum());
    emit balanceListChanged();
}

void ContributionReceiptHandler::removeRow(int row)
{
    m_balanceList.removeAt(row);
    setSum(calculateSum());
    emit balanceListChanged();
}

void ContributionReceiptHandler::saveReceipt(int id, const QString& urlPath, const QString& urlFilename, int year)
{
    emit progress(0);

    QUrl url(urlFilename);
    QString filePath = url.path();
    qDebug() << "tex Filename" << filePath;
    QFile texFile(filePath);

    if(! texFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString error = texFile.errorString();
        emit statusMessage(QString("Cant open LaTEX File %1: %2").arg(filePath).arg(error));
        return;
    }

    QTextStream readStream(&texFile);

    entity::Member* member = dao::MemberTableModel::findByMemberId(id);

    QUrl url2(urlPath);
    QString path = url2.path();
    QString outFilename = QString("%1/Spendenquittung-%2-%3-%4.tex")
            .arg(path)
            .arg(year)
            .arg(member->name())
            .arg(member->firstname());

    qDebug() << "out Filename" << outFilename;
    QFile outFile(outFilename);

    if(! outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QString error = outFile.errorString();
        emit statusMessage(QString("Cant save LaTEX File %1: %2").arg(outFilename).arg(error));
        return;
    }

    QTextStream writeStream(&outFile);


    accounting::ContributionReceiptParser parser(m_sum, year, &m_balanceList, member);

    parser.parse(readStream, writeStream);

    writeStream.flush();
    outFile.close();
    texFile.close();
    emit statusMessage(QString("File Save: %1").arg(outFilename));
    emit progress(1);
}

void ContributionReceiptHandler::clearList()
{
    for(QObject *object : m_balanceList) {
        delete object;
    }
    m_balanceList.clear();
}

double ContributionReceiptHandler::calculateSum()
{
    double sum = 0;
    for(const QObject *object : m_balanceList) {
        const entity::Balance* balance = qobject_cast<const entity::Balance* >(object);
        sum += balance->value();
    }
    return sum;
}

QList<QObject *> ContributionReceiptHandler::balanceList() const
{
    return m_balanceList;
}

void ContributionReceiptHandler::setBalanceList(const QList<QObject *> &balanceList)
{
    m_balanceList = balanceList;
    emit balanceListChanged();
}

double ContributionReceiptHandler::sum() const
{
    return m_sum;
}

void ContributionReceiptHandler::setSum(double sum)
{
    m_sum = sum;
    emit sumChanged();
}

} // namespace gui
} // namespace membermanager
