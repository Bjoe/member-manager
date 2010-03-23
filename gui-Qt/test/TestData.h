/*
 * TestData.h
 *
 *  Created on: Mar 17, 2010
 *      Author: joerg
 */

#ifndef TESTDATA_H_
#define TESTDATA_H_

#include <QtCore>
#include <QtSql>

namespace ClubFrontendTest {

class TestData {

public:
	void createFakeAdressTable();
	void createFakeCashKontoTable();
	void createFakeContributionTable();
	void createFakeMemberTable();
	void createFakeKassaTable();
	void createFakeRessourcenTable();
	void createFakeKontenTable();
	void createFakeBankTable();
	void createFakeBalanceTable();


private:
	void execStatement(const QString &aSql);
};

}

#endif /* TESTDATA_H_ */
