CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD 
EXEC = chess
OBJECTS = move.o main.o piece.o board.o block.o window.o king.o queen.o pawn.o bishop.o rook.o knight.o ai.o human.o game.o player.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

