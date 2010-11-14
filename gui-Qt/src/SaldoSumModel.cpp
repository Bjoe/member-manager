/*
 * Copyright (c) <year>, <copyright holder> All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution. Neither the name of
 * the <organization> nor the names of its contributors may be used to
 * endorse or promote products derived from this software without specific
 * prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY <copyright holder> ''AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
 * NO EVENT SHALL <copyright holder> BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

#include "SaldoSumModel.h"

#include "DatabaseStructure.h"

namespace ClubFrontend
{

	SaldoSumModel::SaldoSumModel(const QSqlDatabase & aDb)
	  : model(new QSqlQueryModel(this)) 
	{
	  QString query = QString("select sum(a.%1), b.%2, b.%3, b.%4, c.%5 "
				      "from %6 a, %7 b, %8 c "
				      "where a.%9=b.%10 "
				      "and c.%11=b.%10 "
				      "and b.%12='%13' "
				      "group by b.%2, b.%3, b.%4, c.%5")
				      .arg(SaldoTable::COLUMNNAME[SaldoTable::betrag])
				      .arg(MemberTable::COLUMNNAME[MemberTable::NickName])
				      .arg(MemberTable::COLUMNNAME[MemberTable::FirstName])
				      .arg(MemberTable::COLUMNNAME[MemberTable::Name])
				      .arg(RessourcenTable::COLUMNNAME[RessourcenTable::EmailAdress])
				      .arg(SaldoTable::TABLENAME)
				      .arg(MemberTable::TABLENAME)
				      .arg(RessourcenTable::TABLENAME)
				      .arg(SaldoTable::COLUMNNAME[SaldoTable::dorfmitglied_pkey])
				      .arg(MemberTable::COLUMNNAME[MemberTable::MemberId])
				      .arg(RessourcenTable::COLUMNNAME[RessourcenTable::MemberId])
				      .arg(MemberTable::COLUMNNAME[MemberTable::Deleted])
				      .arg(QString("false")); 
	  model->setQuery(query, aDb);
	}

	void SaldoSumModel::setTableView(QTableView* const aView)
	{
	  aView->setModel(model);
	  aView->setColumnHidden(5, true);
	}
}
