CPP := g++
CPPFLAGS := -Wall -pedantic

OBJECTS := main.o bitboard.o

LeeChess: $(OBJECTS)
	$(CPP) $(CPPFLAGS) -o $@ $^

main.o: main.cpp bitboard.hpp
	$(CPP) $(CPPFLAGS) -c $@ $^

bitboard.o: bitboard.cpp bitboard.hpp
	$(CPP) $(CPPFLAGS) -c $@ $^

.PHONY: clean
clean:
	rm LeeChess $(OBJECTS) *.hpp.gch
