
#
include ../makedefs

PGM = gameobject

OBJS = \
	main.o \
	Game.o \
	texture_utils.o \
	GameObject.o \
	Pacman.o \
	Tank.o \
	Chopper.o

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
