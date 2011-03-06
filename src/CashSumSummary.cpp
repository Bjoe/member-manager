#include "CashSumSummary.h"

namespace ClubFrontend
{

CashSumSummary::CashSumSummary ( SummaryHandler* aHandler, QObject* parent ) :
        QObject ( parent ), handler ( aHandler ), cashSumButton ( new QPushButton() )
{
    cashSumButton->setObjectName ( QString::fromUtf8 ( "cashSumButton" ) );
    cashSumButton->setText ( tr ( "Gesamte Einahmen" ) );

    connect ( cashSumButton, SIGNAL ( clicked ( bool ) ), this, SLOT ( summaryResult() ) );

    handler->addButton ( cashSumButton );
}

void CashSumSummary::summaryResult()
{
    QString result ( "foo" );

    // TODO QVector< Member > MemberModel.getSelectedMembers();

    handler->showSummary ( result );
}

}
