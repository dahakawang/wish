SRC=$(wildcard *.cc)
OBJ=$(SRC:%.cc=%.o)

CPPFLAGS	=	-std=c++0x -g

all: wsh
	./wsh

wsh: $(OBJ)
	$(CXX) $< -o wsh

$(OBJ): %.o : %.cc
	$(CXX) -c $(CPPFLAGS) $< -o $@

clean:
	-rm *.o
	-rm wsh
