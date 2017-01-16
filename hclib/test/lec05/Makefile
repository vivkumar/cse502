include $(HCLIB_ROOT)/include/hclib.mak

EXE=fib_sequential fib_pthread fib_async_finish arraysum_async_finish arraysum_sequential

all: $(EXE)

fib_sequential: fib_sequential.cpp
	g++ -o $@ $^

fib_pthread: fib_pthread.cpp
	g++ -o $@ $^ -lpthread

fib_async_finish: fib_async_finish.cpp
	g++ $(PROJECT_CXXFLAGS) -o $@ $^ -L . $(PROJECT_LDLIBS) $(PROJECT_LDFLAGS)

arraysum_sequential: arraysum_sequential.cpp
	g++ -o $@ $^

arraysum_async_finish: arraysum_async_finish.cpp
	g++ $(PROJECT_CXXFLAGS) -o $@ $^ -L . $(PROJECT_LDLIBS) $(PROJECT_LDFLAGS)

clean:
	rm -rf *.o $(EXE)
