CXX           = g++
CXXFLAGS      = -std=c++17 -Wall -Wextra -pedantic
INCPATH       = -I.
LINKER        = g++
LFLAGS        = -Wall
DEL_FILE	  = rm -f
OBJECTS_DIR   = ./obj

SOURCES       = base/model/gamemodel.cpp \
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
OBJECTS       = obj/gamemodel.o \
		obj/playermodel.o \
		obj/symbol.o \
		obj/gameview.o \
		obj/playerview.o \
		obj/classicgamemodel.o \
		obj/fancytextsymbolview.o \
		obj/streamentity.o \
		obj/main.o \
		obj/randomplayermodel.o \
		obj/realplayermodel.o \
		obj/statisticalplayermodel.o \
		obj/textgameview.o \
		obj/textplayerview.o \
		obj/textsymbolview.o

DIST          =  base/exception.h \
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
		textview/textsymbolview.h base/model/gamemodel.cpp \
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

TARGET         = rps

all: rps

rps:  $(OBJECTS) 
	$(LINKER) $(LFLAGS) -o $(TARGET) $(OBJECTS)

clean: 
	-$(DEL_FILE) obj/gamemodel.o obj/playermodel.o obj/symbol.o obj/gameview.o obj/playerview.o obj/classicgamemodel.o obj/fancytextsymbolview.o obj/streamentity.o obj/main.o obj/randomplayermodel.o obj/realplayermodel.o obj/statisticalplayermodel.o obj/textgameview.o obj/textplayerview.o obj/textsymbolview.o

####### Compile

obj/gamemodel.o: base/model/gamemodel.cpp base/model/gamemodel.h \
		base/model/playermodel.h \
		base/model/symbol.h \
		base/exception.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/gamemodel.o base/model/gamemodel.cpp

obj/playermodel.o: base/model/playermodel.cpp base/model/playermodel.h \
		base/model/symbol.h \
		base/model/gamemodel.h \
		base/exception.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/playermodel.o base/model/playermodel.cpp

obj/symbol.o: base/model/symbol.cpp base/model/symbol.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/symbol.o base/model/symbol.cpp

obj/gameview.o: base/view/gameview.cpp base/view/gameview.h \
		base/model/gamemodel.h \
		base/model/playermodel.h \
		base/model/symbol.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/gameview.o base/view/gameview.cpp

obj/playerview.o: base/view/playerview.cpp base/view/playerview.h \
		base/model/playermodel.h \
		base/model/symbol.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/playerview.o base/view/playerview.cpp

obj/classicgamemodel.o: classicrps/classicgamemodel.cpp classicrps/classicgamemodel.h \
		base/model/gamemodel.h \
		base/model/playermodel.h \
		base/model/symbol.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/classicgamemodel.o classicrps/classicgamemodel.cpp

obj/fancytextsymbolview.o: classicrps/fancytextsymbolview.cpp classicrps/fancytextsymbolview.h \
		textview/textsymbolview.h \
		textview/streamentity.h \
		base/model/symbol.h \
		classicrps/classicgamemodel.h \
		base/model/gamemodel.h \
		base/model/playermodel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/fancytextsymbolview.o classicrps/fancytextsymbolview.cpp

obj/streamentity.o: textview/streamentity.cpp textview/streamentity.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/streamentity.o textview/streamentity.cpp

obj/main.o: main.cpp textview/textgameview.h \
		base/view/gameview.h \
		base/model/gamemodel.h \
		base/model/playermodel.h \
		base/model/symbol.h \
		base/view/playerview.h \
		textview/streamentity.h \
		textview/textsymbolview.h \
		classicrps/classicgamemodel.h \
		classicrps/fancytextsymbolview.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/main.o main.cpp

obj/randomplayermodel.o: playermodels/randomplayermodel.cpp playermodels/randomplayermodel.h \
		base/model/playermodel.h \
		base/model/symbol.h \
		base/exception.h \
		base/model/gamemodel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/randomplayermodel.o playermodels/randomplayermodel.cpp

obj/realplayermodel.o: playermodels/realplayermodel.cpp playermodels/realplayermodel.h \
		base/model/playermodel.h \
		base/model/symbol.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/realplayermodel.o playermodels/realplayermodel.cpp

obj/statisticalplayermodel.o: playermodels/statisticalplayermodel.cpp playermodels/statisticalplayermodel.h \
		base/model/playermodel.h \
		base/model/symbol.h \
		base/model/gamemodel.h \
		base/exception.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/statisticalplayermodel.o playermodels/statisticalplayermodel.cpp

obj/textgameview.o: textview/textgameview.cpp textview/textgameview.h \
		base/view/gameview.h \
		base/model/gamemodel.h \
		base/model/playermodel.h \
		base/model/symbol.h \
		base/view/playerview.h \
		textview/streamentity.h \
		textview/textsymbolview.h \
		textview/textplayerview.h \
		base/exception.h \
		playermodels/randomplayermodel.h \
		playermodels/statisticalplayermodel.h \
		playermodels/realplayermodel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/textgameview.o textview/textgameview.cpp

obj/textplayerview.o: textview/textplayerview.cpp textview/textplayerview.h \
		base/view/playerview.h \
		base/model/playermodel.h \
		base/model/symbol.h \
		textview/streamentity.h \
		textview/textsymbolview.h \
		base/model/gamemodel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/textplayerview.o textview/textplayerview.cpp

obj/textsymbolview.o: textview/textsymbolview.cpp textview/textsymbolview.h \
		textview/streamentity.h \
		base/model/symbol.h \
		base/exception.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/textsymbolview.o textview/textsymbolview.cpp


