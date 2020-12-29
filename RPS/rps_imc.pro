TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        base/model/gamemodel.cpp \
        base/model/playermodel.cpp \
        base/model/symbol.cpp \
        base/view/gameview.cpp \
        base/view/playerview.cpp \
        classicrps/classicgamemodel.cpp \
        classicrps/fancytextsymbolview.cpp \
        textview/streamentity.cpp \
        main.cpp \
        playermodels/randomplayermodel.cpp \
        playermodels/realplayermodel.cpp \
        playermodels/statisticalplayermodel.cpp \
        textview/textgameview.cpp \
        textview/textplayerview.cpp \
        textview/textsymbolview.cpp

HEADERS += \
    base/exception.h \
    base/model/gamemodel.h \
    base/model/playermodel.h \
    base/model/symbol.h \
    base/view/gameview.h \
    base/view/playerview.h \
    classicrps/classicgamemodel.h \
    classicrps/fancytextsymbolview.h \
    textview/streamentity.h \
    playermodels/randomplayermodel.h \
    playermodels/realplayermodel.h \
    playermodels/statisticalplayermodel.h \
    textview/textgameview.h \
    textview/textplayerview.h \
    textview/textsymbolview.h
