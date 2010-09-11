/*
 * MemberFilter.h
 *
 *  Created on: Jul 6, 2010
 *      Author: joerg
 */

#ifndef MEMBERFILTER_H_
#define MEMBERFILTER_H_

#include <QString>
#include <QVector>

namespace ClubFrontend {

class MemberFilter {

public:
	void setDeleted();

	QString getFilter() const;

private:
	QVector<QString> columns;

	bool isNext(const QVector<QString>::const_iterator &i, QString &aFilter) const;
};

}

#endif /* MEMBERFILTER_H_ */
