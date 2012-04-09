WARNING_FLAGS := -Wall -Wextra -Werror -pedantic -Wconversion
OPT_FLAGS := -O2
all: libwtmedian.so
.PHONY: all

libwtmedian.so: partition.o heap_select.o median.o
	g++ $(WARNING_FLAGS) $(OPT_FLAGS) -shared -Wl,-soname,$@ -o $@ $^

%.o:	%.cpp
	g++ $(WARNING_FLAGS) $(OPT_FLAGS) -fPIC -c $^

clean:
	rm -rf lib*.so
	rm -rf *.o
.PHONY: clean

