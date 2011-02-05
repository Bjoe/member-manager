/*
 * MemberFilter.h
 *
 *  Created on: Jul 6, 2010
 *      Author: joerg
 */

#ifndef MEMBERFILTER_H_
#define MEMBERFILTER_H_

#include <QString>
#include <QStringList>

namespace ClubFrontend
{
namespace Model
{

class MemberFilter
{

public:
    void setDeleted ( const bool aBoolean );

    QString getFilter() const;

private:
    QStringList columns;
};

}
}

#endif /* MEMBERFILTER_H_ */
