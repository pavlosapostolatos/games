CC = g++
CPPFLAGS = -g3 -std=c++11

ergasia: classes.o objects.o DeckBuilder.o cards.o game.o 
	$(CC) $(CPPFLAGS) -o game classes.o objects.o DeckBuilder.o cards.o game.o 

classes.o: classes.cpp classes.hpp
	$(CC) $(CPPFLAGS) -c classes.cpp

objects.o: objects.cpp objects.hpp
	$(CC) $(CPPFLAGS) -c objects.cpp

DeckBuilder.o: DeckBuilder.cpp DeckBuilder.hpp
	$(CC) $(CPPFLAGS) -c DeckBuilder.cpp

cards.o: cards.cpp cards.hpp
	$(CC) $(CPPFLAGS) -c cards.cpp 

game.o: game.cpp 
	$(CC) $(CPPFLAGS) -c game.cpp

clean:
	rm -f game classes.o objects.o DeckBuilder.o cards.o game.o 
