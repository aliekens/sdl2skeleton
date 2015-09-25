CXX=g++
CFLAGS=`sdl2-config --cflags` -O3
LIBS=`sdl2-config --libs` -lSDL2_gfx
OBJECTS=timer.o main.o

fsm: 

fsm: $(OBJECTS)
	$(CXX) $(CFLAGS) $(LIBS) $(OBJECTS) -o fsm

.cpp.o:
	$(CXX) $(CFLAGS) -c $<

clean:
	@rm -vf *.o *~ qonk screenshot.bmp DEADJOE
