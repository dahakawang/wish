SRC=$(wildcard *.cc)
OBJ=$(SRC:%.cc=%.o)
CXX=g++-4.8

CPPFLAGS	=	-std=c++0x -g

all: wish
	./wish

wish: $(OBJ)
	$(CXX) -o wish $(OBJ)

$(OBJ): %.o : %.cc
	$(CXX) -c $(CPPFLAGS) $< -o $@

clean:
	-rm *.o
	-rm wsh
