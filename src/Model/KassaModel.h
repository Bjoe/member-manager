/*
 * KassaModel.h
 *
 *  Created on: Oct 3, 2010
 *      Author: joerg
 */

#ifndef KASSAMODEL_H_
#define KASSAMODEL_H_

#include <QtCore>
#include <QSqlDatabase>
#include <QSqlTableModel>

namespace ClubFrontend
{

class KassaModel: public QObject
{

public:
    KassaModel ( const QSqlDatabase& aDb );
    virtual ~KassaModel();

    void setDefaultFilter();
    void refresh();

    QSqlTableModel* getKassaTableModel() const;

private:
    QSqlTableModel* model;
};

}

#endif /* KASSAMODEL_H_ */
