/*
 * MemberFilter.cpp
 *
 *  Created on: Jul 6, 2010
 *      Author: joerg
 */

#include "MemberFilter.h"

namespace ClubFrontend
{

void MemberFilter::setDeleted()
{
	QString deletedColumn("deleted=1");
	columns.append(deletedColumn);
}

QString MemberFilter::getFilter() const
{
	QString filter("");
	if (columns.size() > 0)
	{
		QVector<QString>::const_iterator iterator = columns.constBegin();
		do
		{
			filter.append(*iterator);
			iterator++;
		} while (isNext(iterator, filter));
	}
	return filter;
}

bool MemberFilter::isNext(const QVector<QString>::const_iterator &anIterator,
		QString &aFilter) const
{
	bool isNext = false;
	if (anIterator < columns.constEnd())
	{
		isNext = true;
		aFilter.append(" AND ");
	}
	return isNext;
}

}
