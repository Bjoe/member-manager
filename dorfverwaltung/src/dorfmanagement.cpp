#include "dorfmanagement.hpp"
namespace MemberManagement
{
using namespace litesql;
BankRl::Row::Row(const litesql::Database& db, const litesql::Record& rec)
		: member(BankRl::Member), bank(BankRl::Bank)
{
	switch (rec.size()) {
	case 2:
		member = rec[1];
	case 1:
		bank = rec[0];
	}
}
const std::string BankRl::table__("Bank_Member_");
const litesql::FieldType BankRl::Bank("Bank1","INTEGER",table__);
const litesql::FieldType BankRl::Member("Member2","INTEGER",table__);
void BankRl::link(const litesql::Database& db, const MemberManagement::Bank& o0, const MemberManagement::Member& o1)
{
	Record values;
	Split fields;
	fields.push_back(Bank.name());
	values.push_back(o0.id);
	fields.push_back(Member.name());
	values.push_back(o1.id);
	db.insert(table__, values, fields);
}
void BankRl::unlink(const litesql::Database& db, const MemberManagement::Bank& o0, const MemberManagement::Member& o1)
{
	db.delete_(table__, (Bank == o0.id && Member == o1.id));
}
void BankRl::del(const litesql::Database& db, const litesql::Expr& expr)
{
	db.delete_(table__, expr);
}
litesql::DataSource<BankRl::Row> BankRl::getRows(const litesql::Database& db, const litesql::Expr& expr)
{
	SelectQuery sel;
	sel.result(Bank.fullName());
	sel.result(Member.fullName());
	sel.source(table__);
	sel.where(expr);
	return DataSource<BankRl::Row>(db, sel);
}
template <> litesql::DataSource<MemberManagement::Bank> BankRl::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr)
{
	SelectQuery sel;
	sel.source(table__);
	sel.result(Bank.fullName());
	sel.where(srcExpr);
	return DataSource<MemberManagement::Bank>(db, MemberManagement::Bank::Id.in(sel) && expr);
}
template <> litesql::DataSource<MemberManagement::Member> BankRl::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr)
{
	SelectQuery sel;
	sel.source(table__);
	sel.result(Member.fullName());
	sel.where(srcExpr);
	return DataSource<MemberManagement::Member>(db, MemberManagement::Member::Id.in(sel) && expr);
}
ContributionRl::Row::Row(const litesql::Database& db, const litesql::Record& rec)
		: member(ContributionRl::Member), contribution(ContributionRl::Contribution)
{
	switch (rec.size()) {
	case 2:
		member = rec[1];
	case 1:
		contribution = rec[0];
	}
}
const std::string ContributionRl::table__("Contribution_Member_");
const litesql::FieldType ContributionRl::Contribution("Contribution1","INTEGER",table__);
const litesql::FieldType ContributionRl::Member("Member2","INTEGER",table__);
void ContributionRl::link(const litesql::Database& db, const MemberManagement::Contribution& o0, const MemberManagement::Member& o1)
{
	Record values;
	Split fields;
	fields.push_back(Contribution.name());
	values.push_back(o0.id);
	fields.push_back(Member.name());
	values.push_back(o1.id);
	db.insert(table__, values, fields);
}
void ContributionRl::unlink(const litesql::Database& db, const MemberManagement::Contribution& o0, const MemberManagement::Member& o1)
{
	db.delete_(table__, (Contribution == o0.id && Member == o1.id));
}
void ContributionRl::del(const litesql::Database& db, const litesql::Expr& expr)
{
	db.delete_(table__, expr);
}
litesql::DataSource<ContributionRl::Row> ContributionRl::getRows(const litesql::Database& db, const litesql::Expr& expr)
{
	SelectQuery sel;
	sel.result(Contribution.fullName());
	sel.result(Member.fullName());
	sel.source(table__);
	sel.where(expr);
	return DataSource<ContributionRl::Row>(db, sel);
}
template <> litesql::DataSource<MemberManagement::Contribution> ContributionRl::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr)
{
	SelectQuery sel;
	sel.source(table__);
	sel.result(Contribution.fullName());
	sel.where(srcExpr);
	return DataSource<MemberManagement::Contribution>(db, MemberManagement::Contribution::Id.in(sel) && expr);
}
template <> litesql::DataSource<MemberManagement::Member> ContributionRl::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr)
{
	SelectQuery sel;
	sel.source(table__);
	sel.result(Member.fullName());
	sel.where(srcExpr);
	return DataSource<MemberManagement::Member>(db, MemberManagement::Member::Id.in(sel) && expr);
}
BalanceRl::Row::Row(const litesql::Database& db, const litesql::Record& rec)
		: member(BalanceRl::Member), balance(BalanceRl::Balance)
{
	switch (rec.size()) {
	case 2:
		member = rec[1];
	case 1:
		balance = rec[0];
	}
}
const std::string BalanceRl::table__("Balance_Member_");
const litesql::FieldType BalanceRl::Balance("Balance1","INTEGER",table__);
const litesql::FieldType BalanceRl::Member("Member2","INTEGER",table__);
void BalanceRl::link(const litesql::Database& db, const MemberManagement::Balance& o0, const MemberManagement::Member& o1)
{
	Record values;
	Split fields;
	fields.push_back(Balance.name());
	values.push_back(o0.id);
	fields.push_back(Member.name());
	values.push_back(o1.id);
	db.insert(table__, values, fields);
}
void BalanceRl::unlink(const litesql::Database& db, const MemberManagement::Balance& o0, const MemberManagement::Member& o1)
{
	db.delete_(table__, (Balance == o0.id && Member == o1.id));
}
void BalanceRl::del(const litesql::Database& db, const litesql::Expr& expr)
{
	db.delete_(table__, expr);
}
litesql::DataSource<BalanceRl::Row> BalanceRl::getRows(const litesql::Database& db, const litesql::Expr& expr)
{
	SelectQuery sel;
	sel.result(Balance.fullName());
	sel.result(Member.fullName());
	sel.source(table__);
	sel.where(expr);
	return DataSource<BalanceRl::Row>(db, sel);
}
template <> litesql::DataSource<MemberManagement::Balance> BalanceRl::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr)
{
	SelectQuery sel;
	sel.source(table__);
	sel.result(Balance.fullName());
	sel.where(srcExpr);
	return DataSource<MemberManagement::Balance>(db, MemberManagement::Balance::Id.in(sel) && expr);
}
template <> litesql::DataSource<MemberManagement::Member> BalanceRl::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr)
{
	SelectQuery sel;
	sel.source(table__);
	sel.result(Member.fullName());
	sel.where(srcExpr);
	return DataSource<MemberManagement::Member>(db, MemberManagement::Member::Id.in(sel) && expr);
}
RessourcenRl::Row::Row(const litesql::Database& db, const litesql::Record& rec)
		: ressourcen(RessourcenRl::Ressourcen), member(RessourcenRl::Member)
{
	switch (rec.size()) {
	case 2:
		ressourcen = rec[1];
	case 1:
		member = rec[0];
	}
}
const std::string RessourcenRl::table__("Member_Ressourcen_");
const litesql::FieldType RessourcenRl::Member("Member1","INTEGER",table__);
const litesql::FieldType RessourcenRl::Ressourcen("Ressourcen2","INTEGER",table__);
void RessourcenRl::link(const litesql::Database& db, const MemberManagement::Member& o0, const MemberManagement::Ressourcen& o1)
{
	Record values;
	Split fields;
	fields.push_back(Member.name());
	values.push_back(o0.id);
	fields.push_back(Ressourcen.name());
	values.push_back(o1.id);
	db.insert(table__, values, fields);
}
void RessourcenRl::unlink(const litesql::Database& db, const MemberManagement::Member& o0, const MemberManagement::Ressourcen& o1)
{
	db.delete_(table__, (Member == o0.id && Ressourcen == o1.id));
}
void RessourcenRl::del(const litesql::Database& db, const litesql::Expr& expr)
{
	db.delete_(table__, expr);
}
litesql::DataSource<RessourcenRl::Row> RessourcenRl::getRows(const litesql::Database& db, const litesql::Expr& expr)
{
	SelectQuery sel;
	sel.result(Member.fullName());
	sel.result(Ressourcen.fullName());
	sel.source(table__);
	sel.where(expr);
	return DataSource<RessourcenRl::Row>(db, sel);
}
template <> litesql::DataSource<MemberManagement::Member> RessourcenRl::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr)
{
	SelectQuery sel;
	sel.source(table__);
	sel.result(Member.fullName());
	sel.where(srcExpr);
	return DataSource<MemberManagement::Member>(db, MemberManagement::Member::Id.in(sel) && expr);
}
template <> litesql::DataSource<MemberManagement::Ressourcen> RessourcenRl::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr)
{
	SelectQuery sel;
	sel.source(table__);
	sel.result(Ressourcen.fullName());
	sel.where(srcExpr);
	return DataSource<MemberManagement::Ressourcen>(db, MemberManagement::Ressourcen::Id.in(sel) && expr);
}
const litesql::FieldType Member::Own::Id("id_","INTEGER","Member_");
Member::BankAccountHandle::BankAccountHandle(const Member& owner)
		: litesql::RelationHandle<Member>(owner)
{
}
void Member::BankAccountHandle::link(const Bank& o0)
{
	BankRl::link(owner->getDatabase(), o0, *owner);
}
void Member::BankAccountHandle::unlink(const Bank& o0)
{
	BankRl::unlink(owner->getDatabase(), o0, *owner);
}
void Member::BankAccountHandle::del(const litesql::Expr& expr)
{
	BankRl::del(owner->getDatabase(), expr && BankRl::Member == owner->id);
}
litesql::DataSource<Bank> Member::BankAccountHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr)
{
	return BankRl::get<Bank>(owner->getDatabase(), expr, (BankRl::Member == owner->id) && srcExpr);
}
litesql::DataSource<BankRl::Row> Member::BankAccountHandle::getRows(const litesql::Expr& expr)
{
	return BankRl::getRows(owner->getDatabase(), expr && (BankRl::Member == owner->id));
}
Member::MoneyHandle::MoneyHandle(const Member& owner)
		: litesql::RelationHandle<Member>(owner)
{
}
void Member::MoneyHandle::link(const Contribution& o0)
{
	ContributionRl::link(owner->getDatabase(), o0, *owner);
}
void Member::MoneyHandle::unlink(const Contribution& o0)
{
	ContributionRl::unlink(owner->getDatabase(), o0, *owner);
}
void Member::MoneyHandle::del(const litesql::Expr& expr)
{
	ContributionRl::del(owner->getDatabase(), expr && ContributionRl::Member == owner->id);
}
litesql::DataSource<Contribution> Member::MoneyHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr)
{
	return ContributionRl::get<Contribution>(owner->getDatabase(), expr, (ContributionRl::Member == owner->id) && srcExpr);
}
litesql::DataSource<ContributionRl::Row> Member::MoneyHandle::getRows(const litesql::Expr& expr)
{
	return ContributionRl::getRows(owner->getDatabase(), expr && (ContributionRl::Member == owner->id));
}
Member::CashAccountHandle::CashAccountHandle(const Member& owner)
		: litesql::RelationHandle<Member>(owner)
{
}
void Member::CashAccountHandle::link(const Balance& o0)
{
	BalanceRl::link(owner->getDatabase(), o0, *owner);
}
void Member::CashAccountHandle::unlink(const Balance& o0)
{
	BalanceRl::unlink(owner->getDatabase(), o0, *owner);
}
void Member::CashAccountHandle::del(const litesql::Expr& expr)
{
	BalanceRl::del(owner->getDatabase(), expr && BalanceRl::Member == owner->id);
}
litesql::DataSource<Balance> Member::CashAccountHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr)
{
	return BalanceRl::get<Balance>(owner->getDatabase(), expr, (BalanceRl::Member == owner->id) && srcExpr);
}
litesql::DataSource<BalanceRl::Row> Member::CashAccountHandle::getRows(const litesql::Expr& expr)
{
	return BalanceRl::getRows(owner->getDatabase(), expr && (BalanceRl::Member == owner->id));
}
Member::InternalRessourcenHandle::InternalRessourcenHandle(const Member& owner)
		: litesql::RelationHandle<Member>(owner)
{
}
void Member::InternalRessourcenHandle::link(const Ressourcen& o0)
{
	RessourcenRl::link(owner->getDatabase(), *owner, o0);
}
void Member::InternalRessourcenHandle::unlink(const Ressourcen& o0)
{
	RessourcenRl::unlink(owner->getDatabase(), *owner, o0);
}
void Member::InternalRessourcenHandle::del(const litesql::Expr& expr)
{
	RessourcenRl::del(owner->getDatabase(), expr && RessourcenRl::Member == owner->id);
}
litesql::DataSource<Ressourcen> Member::InternalRessourcenHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr)
{
	return RessourcenRl::get<Ressourcen>(owner->getDatabase(), expr, (RessourcenRl::Member == owner->id) && srcExpr);
}
litesql::DataSource<RessourcenRl::Row> Member::InternalRessourcenHandle::getRows(const litesql::Expr& expr)
{
	return RessourcenRl::getRows(owner->getDatabase(), expr && (RessourcenRl::Member == owner->id));
}
const std::string Member::type__("Member");
const std::string Member::table__("Member_");
const std::string Member::sequence__("Member_seq");
const litesql::FieldType Member::Id("id_","INTEGER",table__);
const litesql::FieldType Member::Type("type_","TEXT",table__);
const litesql::FieldType Member::MemberId("memberId_","INTEGER",table__);
const litesql::FieldType Member::Deleted("deleted_","INTEGER",table__);
const litesql::FieldType Member::Surename("surename_","TEXT",table__);
const litesql::FieldType Member::FirstName("firstName_","TEXT",table__);
const litesql::FieldType Member::Nickname("nickname_","TEXT",table__);
const litesql::FieldType Member::DateOfEntry("dateOfEntry_","INTEGER",table__);
const litesql::FieldType Member::DateOfLeaving("dateOfLeaving_","INTEGER",table__);
const litesql::FieldType Member::Email("email_","TEXT",table__);
const litesql::FieldType Member::Street("street_","TEXT",table__);
const litesql::FieldType Member::ZipCode("zipCode_","INTEGER",table__);
const litesql::FieldType Member::City("city_","TEXT",table__);
const litesql::FieldType Member::CashCollection("cashCollection_","INTEGER",table__);
const litesql::FieldType Member::Info("info_","TEXT",table__);
void Member::defaults()
{
	id = 0;
	memberId = 0;
	deleted = false;
	dateOfEntry = 0;
	dateOfLeaving = 0;
	zipCode = 0;
	cashCollection = 0;
}
Member::Member(const litesql::Database& db)
		: litesql::Persistent(db), id(Id), type(Type), memberId(MemberId), deleted(Deleted), surename(Surename), firstName(FirstName), nickname(Nickname), dateOfEntry(DateOfEntry), dateOfLeaving(DateOfLeaving), email(Email), street(Street), zipCode(ZipCode), city(City), cashCollection(CashCollection), info(Info)
{
	defaults();
}
Member::Member(const litesql::Database& db, const litesql::Record& rec)
		: litesql::Persistent(db, rec), id(Id), type(Type), memberId(MemberId), deleted(Deleted), surename(Surename), firstName(FirstName), nickname(Nickname), dateOfEntry(DateOfEntry), dateOfLeaving(DateOfLeaving), email(Email), street(Street), zipCode(ZipCode), city(City), cashCollection(CashCollection), info(Info)
{
	defaults();
	size_t size = (rec.size() > 15) ? 15 : rec.size();
	switch (size) {
	case 15:
		info = convert<const std::string&, std::string>(rec[14]);
		info.setModified(false);
	case 14:
		cashCollection = convert<const std::string&, bool>(rec[13]);
		cashCollection.setModified(false);
	case 13:
		city = convert<const std::string&, std::string>(rec[12]);
		city.setModified(false);
	case 12:
		zipCode = convert<const std::string&, int>(rec[11]);
		zipCode.setModified(false);
	case 11:
		street = convert<const std::string&, std::string>(rec[10]);
		street.setModified(false);
	case 10:
		email = convert<const std::string&, std::string>(rec[9]);
		email.setModified(false);
	case 9:
		dateOfLeaving = convert<const std::string&, litesql::Date>(rec[8]);
		dateOfLeaving.setModified(false);
	case 8:
		dateOfEntry = convert<const std::string&, litesql::Date>(rec[7]);
		dateOfEntry.setModified(false);
	case 7:
		nickname = convert<const std::string&, std::string>(rec[6]);
		nickname.setModified(false);
	case 6:
		firstName = convert<const std::string&, std::string>(rec[5]);
		firstName.setModified(false);
	case 5:
		surename = convert<const std::string&, std::string>(rec[4]);
		surename.setModified(false);
	case 4:
		deleted = convert<const std::string&, bool>(rec[3]);
		deleted.setModified(false);
	case 3:
		memberId = convert<const std::string&, int>(rec[2]);
		memberId.setModified(false);
	case 2:
		type = convert<const std::string&, std::string>(rec[1]);
		type.setModified(false);
	case 1:
		id = convert<const std::string&, int>(rec[0]);
		id.setModified(false);
	}
}
Member::Member(const Member& obj)
		: litesql::Persistent(obj), id(obj.id), type(obj.type), memberId(obj.memberId), deleted(obj.deleted), surename(obj.surename), firstName(obj.firstName), nickname(obj.nickname), dateOfEntry(obj.dateOfEntry), dateOfLeaving(obj.dateOfLeaving), email(obj.email), street(obj.street), zipCode(obj.zipCode), city(obj.city), cashCollection(obj.cashCollection), info(obj.info)
{
}
const Member& Member::operator=(const Member& obj)
{
	if (this != &obj) {
		id = obj.id;
		type = obj.type;
		memberId = obj.memberId;
		deleted = obj.deleted;
		surename = obj.surename;
		firstName = obj.firstName;
		nickname = obj.nickname;
		dateOfEntry = obj.dateOfEntry;
		dateOfLeaving = obj.dateOfLeaving;
		email = obj.email;
		street = obj.street;
		zipCode = obj.zipCode;
		city = obj.city;
		cashCollection = obj.cashCollection;
		info = obj.info;
	}
	litesql::Persistent::operator=(obj);
	return *this;
}
Member::BankAccountHandle Member::bankAccount()
{
	return Member::BankAccountHandle(*this);
}
Member::MoneyHandle Member::money()
{
	return Member::MoneyHandle(*this);
}
Member::CashAccountHandle Member::cashAccount()
{
	return Member::CashAccountHandle(*this);
}
Member::InternalRessourcenHandle Member::internalRessourcen()
{
	return Member::InternalRessourcenHandle(*this);
}
std::string Member::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs)
{
	tables.push_back(table__);
	litesql::Record fields;
	litesql::Record values;
	fields.push_back(id.name());
	values.push_back(id);
	id.setModified(false);
	fields.push_back(type.name());
	values.push_back(type);
	type.setModified(false);
	fields.push_back(memberId.name());
	values.push_back(memberId);
	memberId.setModified(false);
	fields.push_back(deleted.name());
	values.push_back(deleted);
	deleted.setModified(false);
	fields.push_back(surename.name());
	values.push_back(surename);
	surename.setModified(false);
	fields.push_back(firstName.name());
	values.push_back(firstName);
	firstName.setModified(false);
	fields.push_back(nickname.name());
	values.push_back(nickname);
	nickname.setModified(false);
	fields.push_back(dateOfEntry.name());
	values.push_back(dateOfEntry);
	dateOfEntry.setModified(false);
	fields.push_back(dateOfLeaving.name());
	values.push_back(dateOfLeaving);
	dateOfLeaving.setModified(false);
	fields.push_back(email.name());
	values.push_back(email);
	email.setModified(false);
	fields.push_back(street.name());
	values.push_back(street);
	street.setModified(false);
	fields.push_back(zipCode.name());
	values.push_back(zipCode);
	zipCode.setModified(false);
	fields.push_back(city.name());
	values.push_back(city);
	city.setModified(false);
	fields.push_back(cashCollection.name());
	values.push_back(cashCollection);
	cashCollection.setModified(false);
	fields.push_back(info.name());
	values.push_back(info);
	info.setModified(false);
	fieldRecs.push_back(fields);
	valueRecs.push_back(values);
	return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void Member::create()
{
	litesql::Record tables;
	litesql::Records fieldRecs;
	litesql::Records valueRecs;
	type = type__;
	std::string newID = insert(tables, fieldRecs, valueRecs);
	if (id == 0)
		id = newID;
}
void Member::addUpdates(Updates& updates)
{
	prepareUpdate(updates, table__);
	updateField(updates, table__, id);
	updateField(updates, table__, type);
	updateField(updates, table__, memberId);
	updateField(updates, table__, deleted);
	updateField(updates, table__, surename);
	updateField(updates, table__, firstName);
	updateField(updates, table__, nickname);
	updateField(updates, table__, dateOfEntry);
	updateField(updates, table__, dateOfLeaving);
	updateField(updates, table__, email);
	updateField(updates, table__, street);
	updateField(updates, table__, zipCode);
	updateField(updates, table__, city);
	updateField(updates, table__, cashCollection);
	updateField(updates, table__, info);
}
void Member::addIDUpdates(Updates& updates)
{
}
void Member::getFieldTypes(std::vector<litesql::FieldType>& ftypes)
{
	ftypes.push_back(Id);
	ftypes.push_back(Type);
	ftypes.push_back(MemberId);
	ftypes.push_back(Deleted);
	ftypes.push_back(Surename);
	ftypes.push_back(FirstName);
	ftypes.push_back(Nickname);
	ftypes.push_back(DateOfEntry);
	ftypes.push_back(DateOfLeaving);
	ftypes.push_back(Email);
	ftypes.push_back(Street);
	ftypes.push_back(ZipCode);
	ftypes.push_back(City);
	ftypes.push_back(CashCollection);
	ftypes.push_back(Info);
}
void Member::delRecord()
{
	deleteFromTable(table__, id);
}
void Member::delRelations()
{
	BankRl::del(*db, (BankRl::Member == id));
	ContributionRl::del(*db, (ContributionRl::Member == id));
	BalanceRl::del(*db, (BalanceRl::Member == id));
	RessourcenRl::del(*db, (RessourcenRl::Member == id));
}
void Member::update()
{
	if (!inDatabase) {
		create();
		return;
	}
	Updates updates;
	addUpdates(updates);
	if (id != oldKey) {
		if (!typeIsCorrect())
			upcastCopy()->addIDUpdates(updates);
	}
	litesql::Persistent::update(updates);
	oldKey = id;
}
void Member::del()
{
	if (typeIsCorrect() == false) {
		std::auto_ptr<Member> p(upcastCopy());
		p->delRelations();
		p->onDelete();
		p->delRecord();
	} else {
		onDelete();
		delRecord();
	}
	inDatabase = false;
}
bool Member::typeIsCorrect()
{
	return type == type__;
}
std::auto_ptr<Member> Member::upcast()
{
	return auto_ptr<Member>(new Member(*this));
}
std::auto_ptr<Member> Member::upcastCopy()
{
	Member* np = NULL;
	np->id = id;
	np->type = type;
	np->memberId = memberId;
	np->deleted = deleted;
	np->surename = surename;
	np->firstName = firstName;
	np->nickname = nickname;
	np->dateOfEntry = dateOfEntry;
	np->dateOfLeaving = dateOfLeaving;
	np->email = email;
	np->street = street;
	np->zipCode = zipCode;
	np->city = city;
	np->cashCollection = cashCollection;
	np->info = info;
	np->inDatabase = inDatabase;
	if (!np)
		np = new Member(*this);
	return auto_ptr<Member>(np);
}
std::ostream & operator<<(std::ostream& os, Member o)
{
	os << "-------------------------------------" << std::endl;
	os << o.id.name() << " = " << o.id << std::endl;
	os << o.type.name() << " = " << o.type << std::endl;
	os << o.memberId.name() << " = " << o.memberId << std::endl;
	os << o.deleted.name() << " = " << o.deleted << std::endl;
	os << o.surename.name() << " = " << o.surename << std::endl;
	os << o.firstName.name() << " = " << o.firstName << std::endl;
	os << o.nickname.name() << " = " << o.nickname << std::endl;
	os << o.dateOfEntry.name() << " = " << o.dateOfEntry << std::endl;
	os << o.dateOfLeaving.name() << " = " << o.dateOfLeaving << std::endl;
	os << o.email.name() << " = " << o.email << std::endl;
	os << o.street.name() << " = " << o.street << std::endl;
	os << o.zipCode.name() << " = " << o.zipCode << std::endl;
	os << o.city.name() << " = " << o.city << std::endl;
	os << o.cashCollection.name() << " = " << o.cashCollection << std::endl;
	os << o.info.name() << " = " << o.info << std::endl;
	os << "-------------------------------------" << std::endl;
	return os;
}
const litesql::FieldType Bank::Own::Id("id_","INTEGER","Bank_");
Bank::MemberHandle::MemberHandle(const Bank& owner)
		: litesql::RelationHandle<Bank>(owner)
{
}
void Bank::MemberHandle::link(const Member& o0)
{
	BankRl::link(owner->getDatabase(), *owner, o0);
}
void Bank::MemberHandle::unlink(const Member& o0)
{
	BankRl::unlink(owner->getDatabase(), *owner, o0);
}
void Bank::MemberHandle::del(const litesql::Expr& expr)
{
	BankRl::del(owner->getDatabase(), expr && BankRl::Bank == owner->id);
}
litesql::DataSource<Member> Bank::MemberHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr)
{
	return BankRl::get<Member>(owner->getDatabase(), expr, (BankRl::Bank == owner->id) && srcExpr);
}
litesql::DataSource<BankRl::Row> Bank::MemberHandle::getRows(const litesql::Expr& expr)
{
	return BankRl::getRows(owner->getDatabase(), expr && (BankRl::Bank == owner->id));
}
const std::string Bank::type__("Bank");
const std::string Bank::table__("Bank_");
const std::string Bank::sequence__("Bank_seq");
const litesql::FieldType Bank::Id("id_","INTEGER",table__);
const litesql::FieldType Bank::Type("type_","TEXT",table__);
const litesql::FieldType Bank::Account("account_","INTEGER",table__);
const litesql::FieldType Bank::Name("name_","TEXT",table__);
const litesql::FieldType Bank::Code("code_","INTEGER",table__);
void Bank::defaults()
{
	id = 0;
	account = 0;
	code = 0;
}
Bank::Bank(const litesql::Database& db)
		: litesql::Persistent(db), id(Id), type(Type), account(Account), name(Name), code(Code)
{
	defaults();
}
Bank::Bank(const litesql::Database& db, const litesql::Record& rec)
		: litesql::Persistent(db, rec), id(Id), type(Type), account(Account), name(Name), code(Code)
{
	defaults();
	size_t size = (rec.size() > 5) ? 5 : rec.size();
	switch (size) {
	case 5:
		code = convert<const std::string&, int>(rec[4]);
		code.setModified(false);
	case 4:
		name = convert<const std::string&, std::string>(rec[3]);
		name.setModified(false);
	case 3:
		account = convert<const std::string&, int>(rec[2]);
		account.setModified(false);
	case 2:
		type = convert<const std::string&, std::string>(rec[1]);
		type.setModified(false);
	case 1:
		id = convert<const std::string&, int>(rec[0]);
		id.setModified(false);
	}
}
Bank::Bank(const Bank& obj)
		: litesql::Persistent(obj), id(obj.id), type(obj.type), account(obj.account), name(obj.name), code(obj.code)
{
}
const Bank& Bank::operator=(const Bank& obj)
{
	if (this != &obj) {
		id = obj.id;
		type = obj.type;
		account = obj.account;
		name = obj.name;
		code = obj.code;
	}
	litesql::Persistent::operator=(obj);
	return *this;
}
Bank::MemberHandle Bank::member()
{
	return Bank::MemberHandle(*this);
}
std::string Bank::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs)
{
	tables.push_back(table__);
	litesql::Record fields;
	litesql::Record values;
	fields.push_back(id.name());
	values.push_back(id);
	id.setModified(false);
	fields.push_back(type.name());
	values.push_back(type);
	type.setModified(false);
	fields.push_back(account.name());
	values.push_back(account);
	account.setModified(false);
	fields.push_back(name.name());
	values.push_back(name);
	name.setModified(false);
	fields.push_back(code.name());
	values.push_back(code);
	code.setModified(false);
	fieldRecs.push_back(fields);
	valueRecs.push_back(values);
	return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void Bank::create()
{
	litesql::Record tables;
	litesql::Records fieldRecs;
	litesql::Records valueRecs;
	type = type__;
	std::string newID = insert(tables, fieldRecs, valueRecs);
	if (id == 0)
		id = newID;
}
void Bank::addUpdates(Updates& updates)
{
	prepareUpdate(updates, table__);
	updateField(updates, table__, id);
	updateField(updates, table__, type);
	updateField(updates, table__, account);
	updateField(updates, table__, name);
	updateField(updates, table__, code);
}
void Bank::addIDUpdates(Updates& updates)
{
}
void Bank::getFieldTypes(std::vector<litesql::FieldType>& ftypes)
{
	ftypes.push_back(Id);
	ftypes.push_back(Type);
	ftypes.push_back(Account);
	ftypes.push_back(Name);
	ftypes.push_back(Code);
}
void Bank::delRecord()
{
	deleteFromTable(table__, id);
}
void Bank::delRelations()
{
	BankRl::del(*db, (BankRl::Bank == id));
}
void Bank::update()
{
	if (!inDatabase) {
		create();
		return;
	}
	Updates updates;
	addUpdates(updates);
	if (id != oldKey) {
		if (!typeIsCorrect())
			upcastCopy()->addIDUpdates(updates);
	}
	litesql::Persistent::update(updates);
	oldKey = id;
}
void Bank::del()
{
	if (typeIsCorrect() == false) {
		std::auto_ptr<Bank> p(upcastCopy());
		p->delRelations();
		p->onDelete();
		p->delRecord();
	} else {
		onDelete();
		delRecord();
	}
	inDatabase = false;
}
bool Bank::typeIsCorrect()
{
	return type == type__;
}
std::auto_ptr<Bank> Bank::upcast()
{
	return auto_ptr<Bank>(new Bank(*this));
}
std::auto_ptr<Bank> Bank::upcastCopy()
{
	Bank* np = NULL;
	np->id = id;
	np->type = type;
	np->account = account;
	np->name = name;
	np->code = code;
	np->inDatabase = inDatabase;
	if (!np)
		np = new Bank(*this);
	return auto_ptr<Bank>(np);
}
std::ostream & operator<<(std::ostream& os, Bank o)
{
	os << "-------------------------------------" << std::endl;
	os << o.id.name() << " = " << o.id << std::endl;
	os << o.type.name() << " = " << o.type << std::endl;
	os << o.account.name() << " = " << o.account << std::endl;
	os << o.name.name() << " = " << o.name << std::endl;
	os << o.code.name() << " = " << o.code << std::endl;
	os << "-------------------------------------" << std::endl;
	return os;
}
const litesql::FieldType Contribution::Own::Id("id_","INTEGER","Contribution_");
Contribution::MemberHandle::MemberHandle(const Contribution& owner)
		: litesql::RelationHandle<Contribution>(owner)
{
}
void Contribution::MemberHandle::link(const Member& o0)
{
	ContributionRl::link(owner->getDatabase(), *owner, o0);
}
void Contribution::MemberHandle::unlink(const Member& o0)
{
	ContributionRl::unlink(owner->getDatabase(), *owner, o0);
}
void Contribution::MemberHandle::del(const litesql::Expr& expr)
{
	ContributionRl::del(owner->getDatabase(), expr && ContributionRl::Contribution == owner->id);
}
litesql::DataSource<Member> Contribution::MemberHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr)
{
	return ContributionRl::get<Member>(owner->getDatabase(), expr, (ContributionRl::Contribution == owner->id) && srcExpr);
}
litesql::DataSource<ContributionRl::Row> Contribution::MemberHandle::getRows(const litesql::Expr& expr)
{
	return ContributionRl::getRows(owner->getDatabase(), expr && (ContributionRl::Contribution == owner->id));
}
const std::string Contribution::type__("Contribution");
const std::string Contribution::table__("Contribution_");
const std::string Contribution::sequence__("Contribution_seq");
const litesql::FieldType Contribution::Id("id_","INTEGER",table__);
const litesql::FieldType Contribution::Type("type_","TEXT",table__);
const litesql::FieldType Contribution::Fee("fee_","INTEGER",table__);
const litesql::FieldType Contribution::Donation("donation_","INTEGER",table__);
const litesql::FieldType Contribution::ValidFrom("validFrom_","INTEGER",table__);
const litesql::FieldType Contribution::Info("info_","TEXT",table__);
void Contribution::defaults()
{
	id = 0;
	fee = 0;
	donation = 0;
	validFrom = 0;
}
Contribution::Contribution(const litesql::Database& db)
		: litesql::Persistent(db), id(Id), type(Type), fee(Fee), donation(Donation), validFrom(ValidFrom), info(Info)
{
	defaults();
}
Contribution::Contribution(const litesql::Database& db, const litesql::Record& rec)
		: litesql::Persistent(db, rec), id(Id), type(Type), fee(Fee), donation(Donation), validFrom(ValidFrom), info(Info)
{
	defaults();
	size_t size = (rec.size() > 6) ? 6 : rec.size();
	switch (size) {
	case 6:
		info = convert<const std::string&, std::string>(rec[5]);
		info.setModified(false);
	case 5:
		validFrom = convert<const std::string&, litesql::Date>(rec[4]);
		validFrom.setModified(false);
	case 4:
		donation = convert<const std::string&, int>(rec[3]);
		donation.setModified(false);
	case 3:
		fee = convert<const std::string&, int>(rec[2]);
		fee.setModified(false);
	case 2:
		type = convert<const std::string&, std::string>(rec[1]);
		type.setModified(false);
	case 1:
		id = convert<const std::string&, int>(rec[0]);
		id.setModified(false);
	}
}
Contribution::Contribution(const Contribution& obj)
		: litesql::Persistent(obj), id(obj.id), type(obj.type), fee(obj.fee), donation(obj.donation), validFrom(obj.validFrom), info(obj.info)
{
}
const Contribution& Contribution::operator=(const Contribution& obj)
{
	if (this != &obj) {
		id = obj.id;
		type = obj.type;
		fee = obj.fee;
		donation = obj.donation;
		validFrom = obj.validFrom;
		info = obj.info;
	}
	litesql::Persistent::operator=(obj);
	return *this;
}
Contribution::MemberHandle Contribution::member()
{
	return Contribution::MemberHandle(*this);
}
std::string Contribution::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs)
{
	tables.push_back(table__);
	litesql::Record fields;
	litesql::Record values;
	fields.push_back(id.name());
	values.push_back(id);
	id.setModified(false);
	fields.push_back(type.name());
	values.push_back(type);
	type.setModified(false);
	fields.push_back(fee.name());
	values.push_back(fee);
	fee.setModified(false);
	fields.push_back(donation.name());
	values.push_back(donation);
	donation.setModified(false);
	fields.push_back(validFrom.name());
	values.push_back(validFrom);
	validFrom.setModified(false);
	fields.push_back(info.name());
	values.push_back(info);
	info.setModified(false);
	fieldRecs.push_back(fields);
	valueRecs.push_back(values);
	return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void Contribution::create()
{
	litesql::Record tables;
	litesql::Records fieldRecs;
	litesql::Records valueRecs;
	type = type__;
	std::string newID = insert(tables, fieldRecs, valueRecs);
	if (id == 0)
		id = newID;
}
void Contribution::addUpdates(Updates& updates)
{
	prepareUpdate(updates, table__);
	updateField(updates, table__, id);
	updateField(updates, table__, type);
	updateField(updates, table__, fee);
	updateField(updates, table__, donation);
	updateField(updates, table__, validFrom);
	updateField(updates, table__, info);
}
void Contribution::addIDUpdates(Updates& updates)
{
}
void Contribution::getFieldTypes(std::vector<litesql::FieldType>& ftypes)
{
	ftypes.push_back(Id);
	ftypes.push_back(Type);
	ftypes.push_back(Fee);
	ftypes.push_back(Donation);
	ftypes.push_back(ValidFrom);
	ftypes.push_back(Info);
}
void Contribution::delRecord()
{
	deleteFromTable(table__, id);
}
void Contribution::delRelations()
{
	ContributionRl::del(*db, (ContributionRl::Contribution == id));
}
void Contribution::update()
{
	if (!inDatabase) {
		create();
		return;
	}
	Updates updates;
	addUpdates(updates);
	if (id != oldKey) {
		if (!typeIsCorrect())
			upcastCopy()->addIDUpdates(updates);
	}
	litesql::Persistent::update(updates);
	oldKey = id;
}
void Contribution::del()
{
	if (typeIsCorrect() == false) {
		std::auto_ptr<Contribution> p(upcastCopy());
		p->delRelations();
		p->onDelete();
		p->delRecord();
	} else {
		onDelete();
		delRecord();
	}
	inDatabase = false;
}
bool Contribution::typeIsCorrect()
{
	return type == type__;
}
std::auto_ptr<Contribution> Contribution::upcast()
{
	return auto_ptr<Contribution>(new Contribution(*this));
}
std::auto_ptr<Contribution> Contribution::upcastCopy()
{
	Contribution* np = NULL;
	np->id = id;
	np->type = type;
	np->fee = fee;
	np->donation = donation;
	np->validFrom = validFrom;
	np->info = info;
	np->inDatabase = inDatabase;
	if (!np)
		np = new Contribution(*this);
	return auto_ptr<Contribution>(np);
}
std::ostream & operator<<(std::ostream& os, Contribution o)
{
	os << "-------------------------------------" << std::endl;
	os << o.id.name() << " = " << o.id << std::endl;
	os << o.type.name() << " = " << o.type << std::endl;
	os << o.fee.name() << " = " << o.fee << std::endl;
	os << o.donation.name() << " = " << o.donation << std::endl;
	os << o.validFrom.name() << " = " << o.validFrom << std::endl;
	os << o.info.name() << " = " << o.info << std::endl;
	os << "-------------------------------------" << std::endl;
	return os;
}
const litesql::FieldType Balance::Own::Id("id_","INTEGER","Balance_");
Balance::MemberHandle::MemberHandle(const Balance& owner)
		: litesql::RelationHandle<Balance>(owner)
{
}
void Balance::MemberHandle::link(const Member& o0)
{
	BalanceRl::link(owner->getDatabase(), *owner, o0);
}
void Balance::MemberHandle::unlink(const Member& o0)
{
	BalanceRl::unlink(owner->getDatabase(), *owner, o0);
}
void Balance::MemberHandle::del(const litesql::Expr& expr)
{
	BalanceRl::del(owner->getDatabase(), expr && BalanceRl::Balance == owner->id);
}
litesql::DataSource<Member> Balance::MemberHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr)
{
	return BalanceRl::get<Member>(owner->getDatabase(), expr, (BalanceRl::Balance == owner->id) && srcExpr);
}
litesql::DataSource<BalanceRl::Row> Balance::MemberHandle::getRows(const litesql::Expr& expr)
{
	return BalanceRl::getRows(owner->getDatabase(), expr && (BalanceRl::Balance == owner->id));
}
const std::string Balance::type__("Balance");
const std::string Balance::table__("Balance_");
const std::string Balance::sequence__("Balance_seq");
const litesql::FieldType Balance::Id("id_","INTEGER",table__);
const litesql::FieldType Balance::Type("type_","TEXT",table__);
const litesql::FieldType Balance::Amount("amount_","INTEGER",table__);
const litesql::FieldType Balance::Date("date_","INTEGER",table__);
const litesql::FieldType Balance::Description("description_","TEXT",table__);
const litesql::FieldType Balance::Info("info_","TEXT",table__);
void Balance::defaults()
{
	id = 0;
	amount = 0;
	date = 0;
}
Balance::Balance(const litesql::Database& db)
		: litesql::Persistent(db), id(Id), type(Type), amount(Amount), date(Date), description(Description), info(Info)
{
	defaults();
}
Balance::Balance(const litesql::Database& db, const litesql::Record& rec)
		: litesql::Persistent(db, rec), id(Id), type(Type), amount(Amount), date(Date), description(Description), info(Info)
{
	defaults();
	size_t size = (rec.size() > 6) ? 6 : rec.size();
	switch (size) {
	case 6:
		info = convert<const std::string&, std::string>(rec[5]);
		info.setModified(false);
	case 5:
		description = convert<const std::string&, std::string>(rec[4]);
		description.setModified(false);
	case 4:
		date = convert<const std::string&, litesql::Date>(rec[3]);
		date.setModified(false);
	case 3:
		amount = convert<const std::string&, int>(rec[2]);
		amount.setModified(false);
	case 2:
		type = convert<const std::string&, std::string>(rec[1]);
		type.setModified(false);
	case 1:
		id = convert<const std::string&, int>(rec[0]);
		id.setModified(false);
	}
}
Balance::Balance(const Balance& obj)
		: litesql::Persistent(obj), id(obj.id), type(obj.type), amount(obj.amount), date(obj.date), description(obj.description), info(obj.info)
{
}
const Balance& Balance::operator=(const Balance& obj)
{
	if (this != &obj) {
		id = obj.id;
		type = obj.type;
		amount = obj.amount;
		date = obj.date;
		description = obj.description;
		info = obj.info;
	}
	litesql::Persistent::operator=(obj);
	return *this;
}
Balance::MemberHandle Balance::member()
{
	return Balance::MemberHandle(*this);
}
std::string Balance::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs)
{
	tables.push_back(table__);
	litesql::Record fields;
	litesql::Record values;
	fields.push_back(id.name());
	values.push_back(id);
	id.setModified(false);
	fields.push_back(type.name());
	values.push_back(type);
	type.setModified(false);
	fields.push_back(amount.name());
	values.push_back(amount);
	amount.setModified(false);
	fields.push_back(date.name());
	values.push_back(date);
	date.setModified(false);
	fields.push_back(description.name());
	values.push_back(description);
	description.setModified(false);
	fields.push_back(info.name());
	values.push_back(info);
	info.setModified(false);
	fieldRecs.push_back(fields);
	valueRecs.push_back(values);
	return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void Balance::create()
{
	litesql::Record tables;
	litesql::Records fieldRecs;
	litesql::Records valueRecs;
	type = type__;
	std::string newID = insert(tables, fieldRecs, valueRecs);
	if (id == 0)
		id = newID;
}
void Balance::addUpdates(Updates& updates)
{
	prepareUpdate(updates, table__);
	updateField(updates, table__, id);
	updateField(updates, table__, type);
	updateField(updates, table__, amount);
	updateField(updates, table__, date);
	updateField(updates, table__, description);
	updateField(updates, table__, info);
}
void Balance::addIDUpdates(Updates& updates)
{
}
void Balance::getFieldTypes(std::vector<litesql::FieldType>& ftypes)
{
	ftypes.push_back(Id);
	ftypes.push_back(Type);
	ftypes.push_back(Amount);
	ftypes.push_back(Date);
	ftypes.push_back(Description);
	ftypes.push_back(Info);
}
void Balance::delRecord()
{
	deleteFromTable(table__, id);
}
void Balance::delRelations()
{
	BalanceRl::del(*db, (BalanceRl::Balance == id));
}
void Balance::update()
{
	if (!inDatabase) {
		create();
		return;
	}
	Updates updates;
	addUpdates(updates);
	if (id != oldKey) {
		if (!typeIsCorrect())
			upcastCopy()->addIDUpdates(updates);
	}
	litesql::Persistent::update(updates);
	oldKey = id;
}
void Balance::del()
{
	if (typeIsCorrect() == false) {
		std::auto_ptr<Balance> p(upcastCopy());
		p->delRelations();
		p->onDelete();
		p->delRecord();
	} else {
		onDelete();
		delRecord();
	}
	inDatabase = false;
}
bool Balance::typeIsCorrect()
{
	return type == type__;
}
std::auto_ptr<Balance> Balance::upcast()
{
	return auto_ptr<Balance>(new Balance(*this));
}
std::auto_ptr<Balance> Balance::upcastCopy()
{
	Balance* np = NULL;
	np->id = id;
	np->type = type;
	np->amount = amount;
	np->date = date;
	np->description = description;
	np->info = info;
	np->inDatabase = inDatabase;
	if (!np)
		np = new Balance(*this);
	return auto_ptr<Balance>(np);
}
std::ostream & operator<<(std::ostream& os, Balance o)
{
	os << "-------------------------------------" << std::endl;
	os << o.id.name() << " = " << o.id << std::endl;
	os << o.type.name() << " = " << o.type << std::endl;
	os << o.amount.name() << " = " << o.amount << std::endl;
	os << o.date.name() << " = " << o.date << std::endl;
	os << o.description.name() << " = " << o.description << std::endl;
	os << o.info.name() << " = " << o.info << std::endl;
	os << "-------------------------------------" << std::endl;
	return os;
}
const litesql::FieldType Ressourcen::Own::Id("id_","INTEGER","Ressourcen_");
Ressourcen::MemberHandle::MemberHandle(const Ressourcen& owner)
		: litesql::RelationHandle<Ressourcen>(owner)
{
}
void Ressourcen::MemberHandle::link(const Member& o0)
{
	RessourcenRl::link(owner->getDatabase(), o0, *owner);
}
void Ressourcen::MemberHandle::unlink(const Member& o0)
{
	RessourcenRl::unlink(owner->getDatabase(), o0, *owner);
}
void Ressourcen::MemberHandle::del(const litesql::Expr& expr)
{
	RessourcenRl::del(owner->getDatabase(), expr && RessourcenRl::Ressourcen == owner->id);
}
litesql::DataSource<Member> Ressourcen::MemberHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr)
{
	return RessourcenRl::get<Member>(owner->getDatabase(), expr, (RessourcenRl::Ressourcen == owner->id) && srcExpr);
}
litesql::DataSource<RessourcenRl::Row> Ressourcen::MemberHandle::getRows(const litesql::Expr& expr)
{
	return RessourcenRl::getRows(owner->getDatabase(), expr && (RessourcenRl::Ressourcen == owner->id));
}
const std::string Ressourcen::type__("Ressourcen");
const std::string Ressourcen::table__("Ressourcen_");
const std::string Ressourcen::sequence__("Ressourcen_seq");
const litesql::FieldType Ressourcen::Id("id_","INTEGER",table__);
const litesql::FieldType Ressourcen::Type("type_","TEXT",table__);
const litesql::FieldType Ressourcen::EmailIntern("emailIntern_","TEXT",table__);
const litesql::FieldType Ressourcen::EmailCCC("emailCCC_","TEXT",table__);
const litesql::FieldType Ressourcen::ShellAccount("shellAccount_","TEXT",table__);
void Ressourcen::defaults()
{
	id = 0;
}
Ressourcen::Ressourcen(const litesql::Database& db)
		: litesql::Persistent(db), id(Id), type(Type), emailIntern(EmailIntern), emailCCC(EmailCCC), shellAccount(ShellAccount)
{
	defaults();
}
Ressourcen::Ressourcen(const litesql::Database& db, const litesql::Record& rec)
		: litesql::Persistent(db, rec), id(Id), type(Type), emailIntern(EmailIntern), emailCCC(EmailCCC), shellAccount(ShellAccount)
{
	defaults();
	size_t size = (rec.size() > 5) ? 5 : rec.size();
	switch (size) {
	case 5:
		shellAccount = convert<const std::string&, std::string>(rec[4]);
		shellAccount.setModified(false);
	case 4:
		emailCCC = convert<const std::string&, std::string>(rec[3]);
		emailCCC.setModified(false);
	case 3:
		emailIntern = convert<const std::string&, std::string>(rec[2]);
		emailIntern.setModified(false);
	case 2:
		type = convert<const std::string&, std::string>(rec[1]);
		type.setModified(false);
	case 1:
		id = convert<const std::string&, int>(rec[0]);
		id.setModified(false);
	}
}
Ressourcen::Ressourcen(const Ressourcen& obj)
		: litesql::Persistent(obj), id(obj.id), type(obj.type), emailIntern(obj.emailIntern), emailCCC(obj.emailCCC), shellAccount(obj.shellAccount)
{
}
const Ressourcen& Ressourcen::operator=(const Ressourcen& obj)
{
	if (this != &obj) {
		id = obj.id;
		type = obj.type;
		emailIntern = obj.emailIntern;
		emailCCC = obj.emailCCC;
		shellAccount = obj.shellAccount;
	}
	litesql::Persistent::operator=(obj);
	return *this;
}
Ressourcen::MemberHandle Ressourcen::member()
{
	return Ressourcen::MemberHandle(*this);
}
std::string Ressourcen::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs)
{
	tables.push_back(table__);
	litesql::Record fields;
	litesql::Record values;
	fields.push_back(id.name());
	values.push_back(id);
	id.setModified(false);
	fields.push_back(type.name());
	values.push_back(type);
	type.setModified(false);
	fields.push_back(emailIntern.name());
	values.push_back(emailIntern);
	emailIntern.setModified(false);
	fields.push_back(emailCCC.name());
	values.push_back(emailCCC);
	emailCCC.setModified(false);
	fields.push_back(shellAccount.name());
	values.push_back(shellAccount);
	shellAccount.setModified(false);
	fieldRecs.push_back(fields);
	valueRecs.push_back(values);
	return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void Ressourcen::create()
{
	litesql::Record tables;
	litesql::Records fieldRecs;
	litesql::Records valueRecs;
	type = type__;
	std::string newID = insert(tables, fieldRecs, valueRecs);
	if (id == 0)
		id = newID;
}
void Ressourcen::addUpdates(Updates& updates)
{
	prepareUpdate(updates, table__);
	updateField(updates, table__, id);
	updateField(updates, table__, type);
	updateField(updates, table__, emailIntern);
	updateField(updates, table__, emailCCC);
	updateField(updates, table__, shellAccount);
}
void Ressourcen::addIDUpdates(Updates& updates)
{
}
void Ressourcen::getFieldTypes(std::vector<litesql::FieldType>& ftypes)
{
	ftypes.push_back(Id);
	ftypes.push_back(Type);
	ftypes.push_back(EmailIntern);
	ftypes.push_back(EmailCCC);
	ftypes.push_back(ShellAccount);
}
void Ressourcen::delRecord()
{
	deleteFromTable(table__, id);
}
void Ressourcen::delRelations()
{
	RessourcenRl::del(*db, (RessourcenRl::Ressourcen == id));
}
void Ressourcen::update()
{
	if (!inDatabase) {
		create();
		return;
	}
	Updates updates;
	addUpdates(updates);
	if (id != oldKey) {
		if (!typeIsCorrect())
			upcastCopy()->addIDUpdates(updates);
	}
	litesql::Persistent::update(updates);
	oldKey = id;
}
void Ressourcen::del()
{
	if (typeIsCorrect() == false) {
		std::auto_ptr<Ressourcen> p(upcastCopy());
		p->delRelations();
		p->onDelete();
		p->delRecord();
	} else {
		onDelete();
		delRecord();
	}
	inDatabase = false;
}
bool Ressourcen::typeIsCorrect()
{
	return type == type__;
}
std::auto_ptr<Ressourcen> Ressourcen::upcast()
{
	return auto_ptr<Ressourcen>(new Ressourcen(*this));
}
std::auto_ptr<Ressourcen> Ressourcen::upcastCopy()
{
	Ressourcen* np = NULL;
	np->id = id;
	np->type = type;
	np->emailIntern = emailIntern;
	np->emailCCC = emailCCC;
	np->shellAccount = shellAccount;
	np->inDatabase = inDatabase;
	if (!np)
		np = new Ressourcen(*this);
	return auto_ptr<Ressourcen>(np);
}
std::ostream & operator<<(std::ostream& os, Ressourcen o)
{
	os << "-------------------------------------" << std::endl;
	os << o.id.name() << " = " << o.id << std::endl;
	os << o.type.name() << " = " << o.type << std::endl;
	os << o.emailIntern.name() << " = " << o.emailIntern << std::endl;
	os << o.emailCCC.name() << " = " << o.emailCCC << std::endl;
	os << o.shellAccount.name() << " = " << o.shellAccount << std::endl;
	os << "-------------------------------------" << std::endl;
	return os;
}
DorfManagement::DorfManagement(std::string backendType, std::string connInfo)
		: litesql::Database(backendType, connInfo)
{
	initialize();
}
std::vector<litesql::Database::SchemaItem> DorfManagement::getSchema() const
{
	vector<Database::SchemaItem> res;
	res.push_back(Database::SchemaItem("schema_","table","CREATE TABLE schema_ (name_ TEXT, type_ TEXT, sql_ TEXT);"));
	if (backend->supportsSequences()) {
		res.push_back(Database::SchemaItem("Member_seq","sequence","CREATE SEQUENCE Member_seq START 1 INCREMENT 1"));
		res.push_back(Database::SchemaItem("Bank_seq","sequence","CREATE SEQUENCE Bank_seq START 1 INCREMENT 1"));
		res.push_back(Database::SchemaItem("Contribution_seq","sequence","CREATE SEQUENCE Contribution_seq START 1 INCREMENT 1"));
		res.push_back(Database::SchemaItem("Balance_seq","sequence","CREATE SEQUENCE Balance_seq START 1 INCREMENT 1"));
		res.push_back(Database::SchemaItem("Ressourcen_seq","sequence","CREATE SEQUENCE Ressourcen_seq START 1 INCREMENT 1"));
	}
	res.push_back(Database::SchemaItem("Member_","table","CREATE TABLE Member_ (id_ " + backend->getRowIDType() + ",type_ TEXT,memberId_ INTEGER,deleted_ INTEGER,surename_ TEXT,firstName_ TEXT,nickname_ TEXT,dateOfEntry_ INTEGER,dateOfLeaving_ INTEGER,email_ TEXT,street_ TEXT,zipCode_ INTEGER,city_ TEXT,cashCollection_ INTEGER,info_ TEXT)"));
	res.push_back(Database::SchemaItem("Bank_","table","CREATE TABLE Bank_ (id_ " + backend->getRowIDType() + ",type_ TEXT,account_ INTEGER,name_ TEXT,code_ INTEGER)"));
	res.push_back(Database::SchemaItem("Contribution_","table","CREATE TABLE Contribution_ (id_ " + backend->getRowIDType() + ",type_ TEXT,fee_ INTEGER,donation_ INTEGER,validFrom_ INTEGER,info_ TEXT)"));
	res.push_back(Database::SchemaItem("Balance_","table","CREATE TABLE Balance_ (id_ " + backend->getRowIDType() + ",type_ TEXT,amount_ INTEGER,date_ INTEGER,description_ TEXT,info_ TEXT)"));
	res.push_back(Database::SchemaItem("Ressourcen_","table","CREATE TABLE Ressourcen_ (id_ " + backend->getRowIDType() + ",type_ TEXT,emailIntern_ TEXT,emailCCC_ TEXT,shellAccount_ TEXT)"));
	res.push_back(Database::SchemaItem("Bank_Member_","table","CREATE TABLE Bank_Member_ (Bank1 INTEGER,Member2 INTEGER)"));
	res.push_back(Database::SchemaItem("Contribution_Member_","table","CREATE TABLE Contribution_Member_ (Contribution1 INTEGER,Member2 INTEGER)"));
	res.push_back(Database::SchemaItem("Balance_Member_","table","CREATE TABLE Balance_Member_ (Balance1 INTEGER,Member2 INTEGER)"));
	res.push_back(Database::SchemaItem("Member_Ressourcen_","table","CREATE TABLE Member_Ressourcen_ (Member1 INTEGER,Ressourcen2 INTEGER)"));
	res.push_back(Database::SchemaItem("Member_memberId_idx","index","CREATE INDEX Member_memberId_idx ON Member_ (memberId_)"));
	res.push_back(Database::SchemaItem("Bank_Member_Bank1idx","index","CREATE INDEX Bank_Member_Bank1idx ON Bank_Member_ (Bank1)"));
	res.push_back(Database::SchemaItem("Bank_Member_Member2idx","index","CREATE INDEX Bank_Member_Member2idx ON Bank_Member_ (Member2)"));
	res.push_back(Database::SchemaItem("Bank_Member__all_idx","index","CREATE INDEX Bank_Member__all_idx ON Bank_Member_ (Bank1,Member2)"));
	res.push_back(Database::SchemaItem("_92fe70793a43ca9384b802d3b046fb40","index","CREATE INDEX _92fe70793a43ca9384b802d3b046fb40 ON Contribution_Member_ (Contribution1)"));
	res.push_back(Database::SchemaItem("Contribution_Member_Member2idx","index","CREATE INDEX Contribution_Member_Member2idx ON Contribution_Member_ (Member2)"));
	res.push_back(Database::SchemaItem("Contribution_Member__all_idx","index","CREATE INDEX Contribution_Member__all_idx ON Contribution_Member_ (Contribution1,Member2)"));
	res.push_back(Database::SchemaItem("Balance_Member_Balance1idx","index","CREATE INDEX Balance_Member_Balance1idx ON Balance_Member_ (Balance1)"));
	res.push_back(Database::SchemaItem("Balance_Member_Member2idx","index","CREATE INDEX Balance_Member_Member2idx ON Balance_Member_ (Member2)"));
	res.push_back(Database::SchemaItem("Balance_Member__all_idx","index","CREATE INDEX Balance_Member__all_idx ON Balance_Member_ (Balance1,Member2)"));
	res.push_back(Database::SchemaItem("Member_Ressourcen_Member1idx","index","CREATE INDEX Member_Ressourcen_Member1idx ON Member_Ressourcen_ (Member1)"));
	res.push_back(Database::SchemaItem("_76d2d420a9b88d16fa9e1e7781397a26","index","CREATE INDEX _76d2d420a9b88d16fa9e1e7781397a26 ON Member_Ressourcen_ (Ressourcen2)"));
	res.push_back(Database::SchemaItem("Member_Ressourcen__all_idx","index","CREATE INDEX Member_Ressourcen__all_idx ON Member_Ressourcen_ (Member1,Ressourcen2)"));
	return res;
}
void DorfManagement::initialize()
{
	static bool initialized = false;
	if (initialized)
		return;
	initialized = true;
}
}
