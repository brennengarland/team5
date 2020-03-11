
#
include ../makedefs

PGM = sprite

OBJS = \
	main.o \
	Game.o \
	sdl_utils.o \
	Entity.o \
	EntityManager.o \
	AssetManager.o

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
