main: main.o textdisplay.o trashbin.o board.o player.o piece.o king.o queen.o bishop.o rook.o knight.o pawn.o human.o computer.o level1AI.o level2AI.o level3AI.o window-v2.o
	g++ main.o textdisplay.o trashbin.o board.o player.o piece.o king.o queen.o bishop.o rook.o knight.o pawn.o human.o computer.o level1AI.o level2AI.o level3AI.o window-v2.o -o a5 -lX11

main.o: main.cc textdisplay.h trashbin.h board.h piece.h player.h window-v2.h
	g++ -c main.cc

textdisplay.o: textdisplay.h textdisplay.cc
	g++ -c textdisplay.cc

trashbin.o: trashbin.h trashbin.cc
	g++ -c trashbin.cc
 
board.o: board.h board.cc
	g++ -c board.cc

piece.o: piece.h piece.cc
	g++ -c piece.cc

king.o: king.cc piece.h
	g++ -c king.cc

queen.o: queen.cc piece.h
	g++ -c queen.cc

bishop.o: bishop.cc piece.h
	g++ -c bishop.cc

rook.o: rook.cc piece.h
	g++ -c rook.cc

knight.o: knight.cc piece.h
	g++ -c knight.cc

pawn.o: pawn.cc piece.h
	g++ -c pawn.cc

player.o: player.h player.cc
	g++ -c player.cc

human.o: human.cc player.h
	g++ -c human.cc

computer.o: computer.cc player.h
	g++ -o computer.cc

level1AI.o: levelAI.cc computer.h player.h
	g++ -o level1AI.cc

level2AI.o: level2AI.cc computer.h player.h
	g++ -o level2AI.cc

level3AI.o: level3AI.cc computer.h player.h
	g++ -o level3AI.cc
window-v2.o: window-v2.h window-v2.cc
	g++ -o window-v2.cc

.PHONY: clean
clean:
	rm *.o main


