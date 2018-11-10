TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    ../../src/runner/box.cpp \
    ../../src/runner/platform.cpp \
    ../../src/runner/runnergame.cpp \
    ../../src/runner/matrix.cpp \
    ../../src/runner/player.cpp

HEADERS += \
    ../../src/runner/box.h \
    ../../src/runner/platform.h \
    ../../src/runner/runnergame.h \
    ../../src/runner/matrix.h \
    ../../src/runner/player.h
