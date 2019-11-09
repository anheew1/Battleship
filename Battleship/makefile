# 소프트웨어 학부 20171646 안희운
cxx = g++ 
CFAGS = -W -Wall
TARGET = out
OBJECTS = CBattleShipApp.o GameManager.o InputPane.o Main.o Map.o Pane.o Player.o Ship.o StatPane.o ModePane.o  -lncurses 

all : $(TARGET)

$(TARGET): $(OBJECTS)
		$(cxx)  -o $@ $^ 

clean :
		rm -f $(TARGET)
		rm -f *.o
