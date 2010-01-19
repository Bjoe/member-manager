#include "dorfmanagementAddons.hpp"

namespace MemberManagement
{
    // TODO vielleicht besser in VillageSquare uebernehmen.
    template <> litesql::DataSource<Dorfverwaltung::Balance> BalanceRl::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr)
    {
        litesql::SelectQuery sel;
        sel.source(table__);
        sel.result(Balance.fullName());
        sel.where(srcExpr);
        return litesql::DataSource<Dorfverwaltung::Balance>(db, MemberManagement::Balance::Id.in(sel) && expr);
    }
}
