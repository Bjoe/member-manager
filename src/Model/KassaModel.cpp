/*
 * KassaModel.cpp
 *
 *  Created on: Oct 3, 2010
 *      Author: joerg
 */

#include "Model/KassaModel.h"

#include "Model/DatabaseStructure.h"

namespace ClubFrontend
{
namespace Model
{

KassaModel::KassaModel ( const QSqlDatabase& aDb ) :
        model ( new QSqlTableModel ( this, aDb ) )
{
    model->setTable ( KassaTable::TABLENAME );
    model->setObjectName ( "model" );
    setDefaultFilter();
    refresh();
}

KassaModel::~KassaModel()
{
    delete model;
}

void KassaModel::setDefaultFilter()
{
    model->setFilter ( KassaTable::COLUMNNAME[KassaTable::deleted] + "='false'" );
}

void KassaModel::refresh()
{
    model->select();
}

void KassaModel::initTableView ( QTableView* aTableView ) const
{
    aTableView->setModel ( model );
    aTableView->setColumnHidden ( KassaTable::kasse_pkey, true );
    aTableView->setColumnHidden ( KassaTable::deleted, true );

    aTableView->sortByColumn ( KassaTable::kasse_pkey, Qt::DescendingOrder );
}

}
}
