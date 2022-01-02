#LIBS  = -lkernel32 -luser32 -lgdi32 -lopengl32
CFLAGS = -Wall

# Should be equivalent to your list of C files, if you don't build selectively
SRC=$(wildcard *.cpp)

test: $(SRC)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)
