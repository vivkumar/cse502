include $(HCLIB_ROOT)/include/hclib.mak

EXE=fib_sequential fib_pthread fib_async_finish arraysum_async_finish arraysum_sequential

all: $(EXE)

fib_sequential: fib_sequential.cpp
	$(CXX) -o $@ $^

fib_pthread: fib_pthread.cpp
	$(CXX) -o $@ $^ -lpthread

fib_async_finish: fib_async_finish.cpp
	$(CXX) $(PROJECT_CXXFLAGS) $(PROJECT_LDFLAGS) -o $@ $^ $(PROJECT_LDLIBS)

arraysum_sequential: arraysum_sequential.cpp
	$(CXX) -o $@ $^

arraysum_async_finish: arraysum_async_finish.cpp
	$(CXX) $(PROJECT_CXXFLAGS) $(PROJECT_LDFLAGS) -o $@ $^ $(PROJECT_LDLIBS)

clean:
	rm -rf *.o $(EXE)
