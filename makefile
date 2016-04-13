SRC=$(wildcard *.cc)
OBJ=$(SRC:%.cc=%.o)

CPPFLAGS	=	-std=c++0x -g

all: wish
	./wish

wish: $(OBJ)
	$(CXX) -o wish $(OBJ)

$(OBJ): %.o : %.cc
	$(CXX) -c $(CPPFLAGS) $< -o $@

clean:
	-rm *.o
	-rm wish

%.d: %.cc
	@set -e; rm -f $@; \
	 $(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	 sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	 rm -f $@.$$$$

include $(SRC:.cc=.d)
