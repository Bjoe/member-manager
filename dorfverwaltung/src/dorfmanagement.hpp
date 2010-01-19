#ifndef _dorfmanagement_hpp_
#define _dorfmanagement_hpp_
#include "litesql.hpp"
namespace MemberManagement
{
    class Member;
    class Bank;
    class Contribution;
    class Balance;
    class Ressourcen;
    class BankRl
    {
    public:
        class Row
        {
        public:
            litesql::Field<int> member;
            litesql::Field<int> bank;
            Row(const litesql::Database& db, const litesql::Record& rec=litesql::Record());
        };
        static const std::string table__;
        static const litesql::FieldType Bank;
        static const litesql::FieldType Member;
        static void link(const litesql::Database& db, const MemberManagement::Bank& o0, const MemberManagement::Member& o1);
        static void unlink(const litesql::Database& db, const MemberManagement::Bank& o0, const MemberManagement::Member& o1);
        static void del(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
        static litesql::DataSource<BankRl::Row> getRows(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
        template <class T> static litesql::DataSource<T> get(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
        ;
        ;
    };
    class ContributionRl
    {
    public:
        class Row
        {
        public:
            litesql::Field<int> member;
            litesql::Field<int> contribution;
            Row(const litesql::Database& db, const litesql::Record& rec=litesql::Record());
        };
        static const std::string table__;
        static const litesql::FieldType Contribution;
        static const litesql::FieldType Member;
        static void link(const litesql::Database& db, const MemberManagement::Contribution& o0, const MemberManagement::Member& o1);
        static void unlink(const litesql::Database& db, const MemberManagement::Contribution& o0, const MemberManagement::Member& o1);
        static void del(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
        static litesql::DataSource<ContributionRl::Row> getRows(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
        template <class T> static litesql::DataSource<T> get(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
        ;
        ;
    };
    class BalanceRl
    {
    public:
        class Row
        {
        public:
            litesql::Field<int> member;
            litesql::Field<int> balance;
            Row(const litesql::Database& db, const litesql::Record& rec=litesql::Record());
        };
        static const std::string table__;
        static const litesql::FieldType Balance;
        static const litesql::FieldType Member;
        static void link(const litesql::Database& db, const MemberManagement::Balance& o0, const MemberManagement::Member& o1);
        static void unlink(const litesql::Database& db, const MemberManagement::Balance& o0, const MemberManagement::Member& o1);
        static void del(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
        static litesql::DataSource<BalanceRl::Row> getRows(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
        template <class T> static litesql::DataSource<T> get(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
        ;
        ;
    };
    class RessourcenRl
    {
    public:
        class Row
        {
        public:
            litesql::Field<int> ressourcen;
            litesql::Field<int> member;
            Row(const litesql::Database& db, const litesql::Record& rec=litesql::Record());
        };
        static const std::string table__;
        static const litesql::FieldType Member;
        static const litesql::FieldType Ressourcen;
        static void link(const litesql::Database& db, const MemberManagement::Member& o0, const MemberManagement::Ressourcen& o1);
        static void unlink(const litesql::Database& db, const MemberManagement::Member& o0, const MemberManagement::Ressourcen& o1);
        static void del(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
        static litesql::DataSource<RessourcenRl::Row> getRows(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
        template <class T> static litesql::DataSource<T> get(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
        ;
        ;
    };
    class Member : public litesql::Persistent
    {
    public:
        class Own
        {
        public:
            static const litesql::FieldType Id;
        };
    class BankAccountHandle : public litesql::RelationHandle<Member>
        {
        public:
            BankAccountHandle(const Member& owner);
            void link(const Bank& o0);
            void unlink(const Bank& o0);
            void del(const litesql::Expr& expr=litesql::Expr());
            litesql::DataSource<Bank> get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
            litesql::DataSource<BankRl::Row> getRows(const litesql::Expr& expr=litesql::Expr());
        };
    class MoneyHandle : public litesql::RelationHandle<Member>
        {
        public:
            MoneyHandle(const Member& owner);
            void link(const Contribution& o0);
            void unlink(const Contribution& o0);
            void del(const litesql::Expr& expr=litesql::Expr());
            litesql::DataSource<Contribution> get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
            litesql::DataSource<ContributionRl::Row> getRows(const litesql::Expr& expr=litesql::Expr());
        };
    class CashAccountHandle : public litesql::RelationHandle<Member>
        {
        public:
            CashAccountHandle(const Member& owner);
            void link(const Balance& o0);
            void unlink(const Balance& o0);
            void del(const litesql::Expr& expr=litesql::Expr());
            litesql::DataSource<Balance> get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
            litesql::DataSource<BalanceRl::Row> getRows(const litesql::Expr& expr=litesql::Expr());
        };
    class InternalRessourcenHandle : public litesql::RelationHandle<Member>
        {
        public:
            InternalRessourcenHandle(const Member& owner);
            void link(const Ressourcen& o0);
            void unlink(const Ressourcen& o0);
            void del(const litesql::Expr& expr=litesql::Expr());
            litesql::DataSource<Ressourcen> get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
            litesql::DataSource<RessourcenRl::Row> getRows(const litesql::Expr& expr=litesql::Expr());
        };
        static const std::string type__;
        static const std::string table__;
        static const std::string sequence__;
        static const litesql::FieldType Id;
        litesql::Field<int> id;
        static const litesql::FieldType Type;
        litesql::Field<std::string> type;
        static const litesql::FieldType MemberId;
        litesql::Field<int> memberId;
        static const litesql::FieldType Deleted;
        litesql::Field<bool> deleted;
        static const litesql::FieldType Surename;
        litesql::Field<std::string> surename;
        static const litesql::FieldType FirstName;
        litesql::Field<std::string> firstName;
        static const litesql::FieldType Nickname;
        litesql::Field<std::string> nickname;
        static const litesql::FieldType DateOfEntry;
        litesql::Field<litesql::Date> dateOfEntry;
        static const litesql::FieldType DateOfLeaving;
        litesql::Field<litesql::Date> dateOfLeaving;
        static const litesql::FieldType Email;
        litesql::Field<std::string> email;
        static const litesql::FieldType Street;
        litesql::Field<std::string> street;
        static const litesql::FieldType ZipCode;
        litesql::Field<int> zipCode;
        static const litesql::FieldType City;
        litesql::Field<std::string> city;
        static const litesql::FieldType CashCollection;
        litesql::Field<bool> cashCollection;
        static const litesql::FieldType Info;
        litesql::Field<std::string> info;
    protected:
        void defaults();
    public:
        Member(const litesql::Database& db);
        Member(const litesql::Database& db, const litesql::Record& rec);
        Member(const Member& obj);
        const Member& operator=(const Member& obj);
        Member::BankAccountHandle bankAccount();
        Member::MoneyHandle money();
        Member::CashAccountHandle cashAccount();
        Member::InternalRessourcenHandle internalRessourcen();
    protected:
        std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
        void create();
        virtual void addUpdates(Updates& updates);
        virtual void addIDUpdates(Updates& updates);
    public:
        static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
    protected:
        virtual void delRecord();
        virtual void delRelations();
    public:
        virtual void update();
        virtual void del();
        virtual bool typeIsCorrect();
        std::auto_ptr<Member> upcast();
        std::auto_ptr<Member> upcastCopy();
    };
    std::ostream & operator<<(std::ostream& os, Member o);
    class Bank : public litesql::Persistent
    {
    public:
        class Own
        {
        public:
            static const litesql::FieldType Id;
        };
    class MemberHandle : public litesql::RelationHandle<Bank>
        {
        public:
            MemberHandle(const Bank& owner);
            void link(const Member& o0);
            void unlink(const Member& o0);
            void del(const litesql::Expr& expr=litesql::Expr());
            litesql::DataSource<Member> get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
            litesql::DataSource<BankRl::Row> getRows(const litesql::Expr& expr=litesql::Expr());
        };
        static const std::string type__;
        static const std::string table__;
        static const std::string sequence__;
        static const litesql::FieldType Id;
        litesql::Field<int> id;
        static const litesql::FieldType Type;
        litesql::Field<std::string> type;
        static const litesql::FieldType Account;
        litesql::Field<int> account;
        static const litesql::FieldType Name;
        litesql::Field<std::string> name;
        static const litesql::FieldType Code;
        litesql::Field<int> code;
    protected:
        void defaults();
    public:
        Bank(const litesql::Database& db);
        Bank(const litesql::Database& db, const litesql::Record& rec);
        Bank(const Bank& obj);
        const Bank& operator=(const Bank& obj);
        Bank::MemberHandle member();
    protected:
        std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
        void create();
        virtual void addUpdates(Updates& updates);
        virtual void addIDUpdates(Updates& updates);
    public:
        static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
    protected:
        virtual void delRecord();
        virtual void delRelations();
    public:
        virtual void update();
        virtual void del();
        virtual bool typeIsCorrect();
        std::auto_ptr<Bank> upcast();
        std::auto_ptr<Bank> upcastCopy();
    };
    std::ostream & operator<<(std::ostream& os, Bank o);
    class Contribution : public litesql::Persistent
    {
    public:
        class Own
        {
        public:
            static const litesql::FieldType Id;
        };
    class MemberHandle : public litesql::RelationHandle<Contribution>
        {
        public:
            MemberHandle(const Contribution& owner);
            void link(const Member& o0);
            void unlink(const Member& o0);
            void del(const litesql::Expr& expr=litesql::Expr());
            litesql::DataSource<Member> get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
            litesql::DataSource<ContributionRl::Row> getRows(const litesql::Expr& expr=litesql::Expr());
        };
        static const std::string type__;
        static const std::string table__;
        static const std::string sequence__;
        static const litesql::FieldType Id;
        litesql::Field<int> id;
        static const litesql::FieldType Type;
        litesql::Field<std::string> type;
        static const litesql::FieldType Fee;
        litesql::Field<int> fee;
        static const litesql::FieldType Donation;
        litesql::Field<int> donation;
        static const litesql::FieldType ValidFrom;
        litesql::Field<litesql::Date> validFrom;
        static const litesql::FieldType Info;
        litesql::Field<std::string> info;
    protected:
        void defaults();
    public:
        Contribution(const litesql::Database& db);
        Contribution(const litesql::Database& db, const litesql::Record& rec);
        Contribution(const Contribution& obj);
        const Contribution& operator=(const Contribution& obj);
        Contribution::MemberHandle member();
    protected:
        std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
        void create();
        virtual void addUpdates(Updates& updates);
        virtual void addIDUpdates(Updates& updates);
    public:
        static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
    protected:
        virtual void delRecord();
        virtual void delRelations();
    public:
        virtual void update();
        virtual void del();
        virtual bool typeIsCorrect();
        std::auto_ptr<Contribution> upcast();
        std::auto_ptr<Contribution> upcastCopy();
    };
    std::ostream & operator<<(std::ostream& os, Contribution o);
    class Balance : public litesql::Persistent
    {
    public:
        class Own
        {
        public:
            static const litesql::FieldType Id;
        };
    class MemberHandle : public litesql::RelationHandle<Balance>
        {
        public:
            MemberHandle(const Balance& owner);
            void link(const Member& o0);
            void unlink(const Member& o0);
            void del(const litesql::Expr& expr=litesql::Expr());
            litesql::DataSource<Member> get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
            litesql::DataSource<BalanceRl::Row> getRows(const litesql::Expr& expr=litesql::Expr());
        };
        static const std::string type__;
        static const std::string table__;
        static const std::string sequence__;
        static const litesql::FieldType Id;
        litesql::Field<int> id;
        static const litesql::FieldType Type;
        litesql::Field<std::string> type;
        static const litesql::FieldType Amount;
        litesql::Field<int> amount;
        static const litesql::FieldType Date;
        litesql::Field<litesql::Date> date;
        static const litesql::FieldType Description;
        litesql::Field<std::string> description;
        static const litesql::FieldType Info;
        litesql::Field<std::string> info;
    protected:
        void defaults();
    public:
        Balance(const litesql::Database& db);
        Balance(const litesql::Database& db, const litesql::Record& rec);
        Balance(const Balance& obj);
        const Balance& operator=(const Balance& obj);
        Balance::MemberHandle member();
    protected:
        std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
        void create();
        virtual void addUpdates(Updates& updates);
        virtual void addIDUpdates(Updates& updates);
    public:
        static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
    protected:
        virtual void delRecord();
        virtual void delRelations();
    public:
        virtual void update();
        virtual void del();
        virtual bool typeIsCorrect();
        std::auto_ptr<Balance> upcast();
        std::auto_ptr<Balance> upcastCopy();
    };
    std::ostream & operator<<(std::ostream& os, Balance o);
    class Ressourcen : public litesql::Persistent
    {
    public:
        class Own
        {
        public:
            static const litesql::FieldType Id;
        };
    class MemberHandle : public litesql::RelationHandle<Ressourcen>
        {
        public:
            MemberHandle(const Ressourcen& owner);
            void link(const Member& o0);
            void unlink(const Member& o0);
            void del(const litesql::Expr& expr=litesql::Expr());
            litesql::DataSource<Member> get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
            litesql::DataSource<RessourcenRl::Row> getRows(const litesql::Expr& expr=litesql::Expr());
        };
        static const std::string type__;
        static const std::string table__;
        static const std::string sequence__;
        static const litesql::FieldType Id;
        litesql::Field<int> id;
        static const litesql::FieldType Type;
        litesql::Field<std::string> type;
        static const litesql::FieldType EmailIntern;
        litesql::Field<std::string> emailIntern;
        static const litesql::FieldType EmailCCC;
        litesql::Field<std::string> emailCCC;
        static const litesql::FieldType ShellAccount;
        litesql::Field<std::string> shellAccount;
    protected:
        void defaults();
    public:
        Ressourcen(const litesql::Database& db);
        Ressourcen(const litesql::Database& db, const litesql::Record& rec);
        Ressourcen(const Ressourcen& obj);
        const Ressourcen& operator=(const Ressourcen& obj);
        Ressourcen::MemberHandle member();
    protected:
        std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
        void create();
        virtual void addUpdates(Updates& updates);
        virtual void addIDUpdates(Updates& updates);
    public:
        static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
    protected:
        virtual void delRecord();
        virtual void delRelations();
    public:
        virtual void update();
        virtual void del();
        virtual bool typeIsCorrect();
        std::auto_ptr<Ressourcen> upcast();
        std::auto_ptr<Ressourcen> upcastCopy();
    };
    std::ostream & operator<<(std::ostream& os, Ressourcen o);
    class DorfManagement : public litesql::Database
    {
    public:
        DorfManagement(std::string backendType, std::string connInfo);
    protected:
        virtual std::vector<litesql::Database::SchemaItem> getSchema() const;
        static void initialize();
    };
}
#endif
