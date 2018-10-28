TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= QT

SOURCES += \
        test.cpp \
        ../src/snake.cpp \
        ../src/snakesolver.cpp

HEADERS += \
    ../src/snake.h \
    ../src/snakesolver.h
