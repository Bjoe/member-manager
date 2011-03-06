#include "CountMemberSummary.h"

namespace ClubFrontend
{

CountMemberSummary::CountMemberSummary ( SummaryHandler* aHandler, QObject* parent ) :
        QObject ( parent ), countMemberButton ( new QPushButton ), handler ( aHandler )
{
    countMemberButton->setObjectName ( QString::fromUtf8 ( "countMemberButton" ) );
    countMemberButton->setText ( tr ( "Anzahl Mitglieder" ) );

    connect ( countMemberButton, SIGNAL ( clicked() ), this, SLOT ( summaryResult() ) );

    handler->addButton ( countMemberButton );
}

void CountMemberSummary::summaryResult()
{
    QString result ( "foo" );

    // TODO QVector< Member > MemberModel.getSelectedMembers();

    handler->showSummary ( result );
}

}
