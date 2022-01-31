include $(HCLIB_ROOT)/include/hclib.mak

EXE=fib_sequential fib_pthread fib_async_finish array_sum_sequential array_sum_parallel

all: $(EXE)

fib_sequential: fib_sequential.cpp
	$(CXX) -o $@ $^

fib_pthread: fib_pthread.cpp
	$(CXX) -o $@ $^ -lpthread

fib_async_finish: fib_async_finish.cpp
	$(CXX) $(PROJECT_CXXFLAGS) $(PROJECT_LDFLAGS) -o $@ $^ $(PROJECT_LDLIBS)

array_sum_parallel: array_sum.cpp
	$(CXX) -DPARALLEL $(PROJECT_CXXFLAGS) $(PROJECT_LDFLAGS) -o $@ $^ $(PROJECT_LDLIBS)

array_sum_sequential: array_sum.cpp
	$(CXX) -o $@ $^

clean:
	rm -rf *.o $(EXE)
