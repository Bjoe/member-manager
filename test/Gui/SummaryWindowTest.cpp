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

#include "SummaryWindowTest.h"

#include "Gui/SummaryWindow.h"

#include <QtCore/QtCore>
#include <QtGui>

namespace ClubFrontendTest
{
  
SummaryWindowTest::SummaryWindowTest() : isClicked(false)
{}


void SummaryWindowTest::testShowSummary()
{
  ClubFrontend::SummaryWindow summary;
  
  summary.showSummary("foo");
  
  const QTextEdit *textEdit = summary.findChild<QTextEdit* >("textEdit");
  
  QCOMPARE(textEdit->toPlainText(), QString("foo"));
}

void SummaryWindowTest::testAddButton()
{
  isClicked = false;
  ClubFrontend::SummaryWindow summary;
  
  QPushButton *button = new QPushButton();
  button->setObjectName("testButton");
  button->connect(button, SIGNAL(clicked(bool)), this, SLOT(buttonClicked()));
  summary.addButton(button);

  QPushButton *testButton = summary.findChild<QPushButton* >("testButton");
  QTest::mouseClick(testButton, Qt::LeftButton);
  
  QVERIFY(isClicked);
}

void SummaryWindowTest::buttonClicked()
{
  isClicked = true;
}

}

QTEST_MAIN(ClubFrontendTest::SummaryWindowTest)
#include "SummaryWindowTest.moc"
