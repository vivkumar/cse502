include $(HCLIB_ROOT)/include/hclib.mak

EXE=fib_c++async fib_futures

all: $(EXE)

fib_c++async: fib_c++async.cpp
	g++ -std=c++11 -o $@ $^ -lpthread

fib_futures: fib_futures.cpp
	g++ $(PROJECT_CXXFLAGS) -o $@ $^ -L . $(PROJECT_LDLIBS) $(PROJECT_LDFLAGS)

clean:
	rm -rf *.o $(EXE)
