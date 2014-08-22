objects = draughts.o game.o gameboard.o scoreboard.o utility.o


draughts : $(objects)
	gcc -o draughts $(objects)

$(objects) : utility.h
gameboard.o draughts.o game.o : gameboard.h
socoreboard.o draughts.o game.o : scoreboard.h
game.o draughts.o : game.h
draughts.o : draughts.h


.PHONY : clean
clean :
	rm draughts $(objects)
