#include "accountingdatacreator.h"

#include <QString>

#include "entity/bankaccount.h"
#include "entity/sepaaccount.h"
#include "entity/contribution.h"

#include "dao/bankaccounttablemodel.h"
#include "dao/sepaaccounttablemodel.h"
#include "dao/contributiontablemodel.h"

namespace membermanager {
namespace accounting {

AccountingDataCreator::AccountingDataCreator(QDate valuta, QString purpose, QString accountingInfo, int accountingRefernce)
    : m_valuta{valuta}, m_purpose{purpose}, m_accountingInfo{accountingInfo}, m_accountingReference{accountingRefernce}
{
}

MemberAccountingData *AccountingDataCreator::create(const entity::Member* member)
{
    QString memberId = member->memberId();
    MemberAccountingData* data = new MemberAccountingData();
    data->setValuta(m_valuta);
    data->setAccountingInfo(m_accountingInfo);
    data->setPurpose(m_purpose);
    data->setMemberId(memberId);
    data->setFirstname(member->firstname());
    data->setName(member->name());
    QString collectionState = member->collectionState();
    if(! collectionState.isEmpty()) {
        data->setCollectionState(collectionState.at(0));
    }

    entity::BankAccount *bankAccount = dao::BankAccountTableModel::findByMemberId(memberId);
    data->setBankAccountNumber(bankAccount->accountNumber());
    data->setBankCode(bankAccount->code());

    entity::SepaAccount *sepaAccount = dao::SepaAccountTableModel::findByMemberId(memberId);
    data->setSepaBic(sepaAccount->bic());
    data->setSepaIban(sepaAccount->iban());
    data->setSepaMandateDate(sepaAccount->mandateDate());
    data->setSepaSequenceState(sepaAccount->sequenceState());

    entity::Contribution *contribution = dao::ContributionTableModel::findByMemberIdWithPointInTime(memberId, m_valuta);
    data->setFee(contribution->fee());
    data->setDonation(contribution->donation());
    data->setAdditionalFee(contribution->additionalFee());
    data->setAdditionalDonation(contribution->additionalDonation());
    data->setAmortization(contribution->amortization());

    data->setAccountingReference(QString("%1").arg(++m_accountingReference));

    delete bankAccount;
    delete sepaAccount;
    delete contribution;

    return data;
}

int AccountingDataCreator::getAccountingReference() const
{
    return m_accountingReference;
}

} // namespace accounting
} // namespace membermanager
