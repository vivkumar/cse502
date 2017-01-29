include $(HCLIB_ROOT)/include/hclib.mak

EXE=fib_async_finish fib_async_finish_with_falsesharing fib_async_finish_without_falsesharing

all: $(EXE)

fib_async_finish_with_falsesharing: fib_async_finish_with_falsesharing.cpp
	g++ $(PROJECT_CXXFLAGS) -o $@ $^ -L . $(PROJECT_LDLIBS) $(PROJECT_LDFLAGS)

fib_async_finish_without_falsesharing: fib_async_finish_without_falsesharing.cpp
	g++ $(PROJECT_CXXFLAGS) -o $@ $^ -L . $(PROJECT_LDLIBS) $(PROJECT_LDFLAGS)

fib_async_finish: fib_async_finish.cpp
	g++ $(PROJECT_CXXFLAGS) -o $@ $^ -L . $(PROJECT_LDLIBS) $(PROJECT_LDFLAGS)

clean:
	rm -rf *.o $(EXE)
