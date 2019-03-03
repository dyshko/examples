QT -= qt gui core

CONFIG += c++11 console
CONFIG -= app_bundle

INCLUDEPATH += C:\boost\boost_1_69_0

LIBS += -lws2_32 -lwsock32
LIBS += -L"C:\boost\boost_1_69_0\stage\lib"

SOURCES += \
        $${PWD}/message.cpp \
        $${PWD}/session.cpp \

HEADERS += \
        $${PWD}/message.h \
        $${PWD}/session.h \

INCLUDEPATH += $${PWD}
