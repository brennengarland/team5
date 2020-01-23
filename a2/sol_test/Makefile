
#
include ../makedefs

PGM = sol_test

OBJS = \
	main.o

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(CPPFLAGS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
