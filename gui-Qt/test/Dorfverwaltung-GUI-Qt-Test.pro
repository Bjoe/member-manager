LIBS += -L/usr/local/lib -lgmock -lgtest
INCLUDEPATH = /usr/local/include

CONFIG += qtestlib

SOURCES += main.cpp \
    membermock.cpp \
    memberdialogtest.cpp \
    ../src/memberdialog.cpp \
    controllermock.cpp \
    bankmock.cpp \
    contributionmock.cpp
HEADERS += membermock.h \
    memberdialogtest.h \
    ../src/memberdialog.h \
    ../src/controller.h \
    controllermock.h \
    ../src/bank.h \
    ../src/contribution.h \
    ../src/member.h \
    bankmock.h \
    contributionmock.h
FORMS += ../src/memberDialog.ui
