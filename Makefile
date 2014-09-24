CXX = g++                                     # compiler
CXXFLAGS = -g -Wall -MMD                      # compiler flags
MAKEFILE NAME = ${firstword ${MAKEFILE LIST}} # makefile name

OBJECTS1 = p4driver.o Card.o Deck.o Trick.o CardPile.o HumanPlayer.o RandomPlayer.o SmartPlayer.o Player.o      
EXEC1 = Hearts                       			# executable name

OBJECTS = ${OBJECTS1}
EXECS = ${EXEC1}
DEPENDS = ${OBJECTS:.o=.d}                    # substitute ".o" with ".d"

.PHONY : all clean

all : ${EXECS}

${EXEC1} : ${OBJECTS1}                        # link step
	${CXX} ${CXXFLAGS} $^ -o $@           # make sure there is a tab at the start of this line


${OBJECTS} : ${MAKEFILE NAME}                 # OPTIONAL : changes to this file => recompile

-include ${DEPENDS}                           # include *.d files containing program dependences

clean :                                       # remove files that can be regenerated
	rm -f ${DEPENDS} ${OBJECTS} ${EXECS}
