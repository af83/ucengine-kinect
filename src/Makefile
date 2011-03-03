all: test

CFLAGS=-fPIC -g -Wall `pkg-config --cflags opencv`
LIBS = -Wl,--no-as-needed -lpthread `pkg-config --libs opencv`
INCLUDE = -I/usr/include
FREE_LIBS = -L/usr/lib -lfreenect

test: test.cpp
	$(CXX) $(INCLUDE) $(CFLAGS) $? -o $@  $(LIBS) $(FREE_LIBS)

%.o: %.cpp
	$(CXX) -c $(CFLAGS) $< -o $@

clean:
	rm -rf *.o test
