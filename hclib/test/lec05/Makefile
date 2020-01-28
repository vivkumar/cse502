include $(HCLIB_ROOT)/include/hclib.mak

EXE=fib_sequential fib_pthread fib_async_finish

all: $(EXE)

fib_sequential: fib_sequential.cpp
	$(CXX) -o $@ $^

fib_pthread: fib_pthread.cpp
	$(CXX) -o $@ $^ -lpthread

fib_async_finish: fib_async_finish.cpp
	$(CXX) $(PROJECT_CXXFLAGS) $(PROJECT_LDFLAGS) -o $@ $^ $(PROJECT_LDLIBS)

clean:
	rm -rf *.o $(EXE)
