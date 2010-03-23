CONFIG += qtestlib

SOURCES += main.cpp \
    memberdialogtest.cpp \
    ../src/memberdialog.cpp \
    mainwindowtest.cpp \
	../src/mainwindow.cpp
HEADERS += memberdialogtest.h \
    ../src/memberdialog.h \
    mainwindowtest.h \
	../src/mainwindow.h
FORMS += ../src/memberDialog.ui ../src/mainWindow.ui
