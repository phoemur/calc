TEMPLATE = app
TARGET = calculator
INCLUDEPATH += .
DEFINES += QT_DEPRECATED_WARNINGS

# Input
HEADERS += MainWindow.h parser.h
FORMS += MainWindow.ui
SOURCES += calculator.cpp MainWindow.cpp parser.cpp

# Custom config
QT += widgets
QMAKE_CXXFLAGS += -std=c++14
CONFIG += release
#CONFIG += debug
QMAKE_POST_LINK=$(STRIP) $(TARGET)
target.path = /usr/local/bin/
INSTALLS += target
