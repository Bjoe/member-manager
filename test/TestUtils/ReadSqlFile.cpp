/*
    Copyright (c) <year>, <copyright holder>
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
        * Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.
        * Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.
        * Neither the name of the <organization> nor the
        names of its contributors may be used to endorse or promote products
        derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY <copyright holder> ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL <copyright holder> BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#include "TestUtils/ReadSqlFile.h"

namespace Utils
{

ReadSqlFile::ReadSqlFile ( const QString aFilename, const QSqlDatabase &aDatabase ) :
        file ( aFilename )
{
}

ReadSqlFile::~ReadSqlFile()
{
    file.close();
}

bool ReadSqlFile::open()
{
    return file.open ( QIODevice::ReadOnly | QIODevice::Text );
}

bool ReadSqlFile::read()
{
    QTextStream stream ( &file );

    QRegExp regex ( "(.*);" );
    QRegExp comment ( "(.*)--" );
    QString sql;
    while ( !stream.atEnd() )
    {
        QString line = stream.readLine();

        if ( line.contains ( comment ) )
        {
            line = comment.cap ( 1 );
        }

        if ( line.contains ( regex ) )
        {
            QString grep = regex.cap ( 1 );
            sql.append ( grep );
            execStatement ( sql );
            sql.clear();
        }
        else
        {
            sql.append ( line );
        }
    }
}

void ReadSqlFile::execStatement ( const QString& aSql )
{
    QSqlQuery sqlQuery;
    if ( !sqlQuery.exec ( aSql ) )
    {
        const QString msg = QString ( "%1\n%2" ).arg ( sqlQuery.lastError().text() ).arg ( aSql );
        qWarning ( msg.toAscii() );
    }
}

}
