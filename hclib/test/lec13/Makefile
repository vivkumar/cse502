include $(HCLIB_ROOT)/include/hclib.mak

EXE=fib_ddt ddt future arraysum_futures fib_futures promise_future future2

all: clean $(EXE) clean-obj

ddt: ddt.cpp
	$(CXX) $(PROJECT_CXXFLAGS) -o $@ $^ $(PROJECT_LDLIBS) $(PROJECT_LDFLAGS)

fib_ddt: fib_ddt.cpp
	$(CXX) $(PROJECT_CXXFLAGS) -o $@ $^ $(PROJECT_LDLIBS) $(PROJECT_LDFLAGS)

future2: future2.cpp
	$(CXX) $(PROJECT_CXXFLAGS) -o $@ $^ $(PROJECT_LDLIBS) $(PROJECT_LDFLAGS)

promise_future: promise_future.cpp
	$(CXX) $(PROJECT_CXXFLAGS) -o $@ $^ $(PROJECT_LDLIBS) $(PROJECT_LDFLAGS)

future: future.cpp
	$(CXX) $(PROJECT_CXXFLAGS) -o $@ $^ $(PROJECT_LDLIBS) $(PROJECT_LDFLAGS)

arraysum_futures: arraysum_futures.cpp
	$(CXX) $(PROJECT_CXXFLAGS) -o $@ $^ $(PROJECT_LDLIBS) $(PROJECT_LDFLAGS)

fib_futures: fib_futures.cpp
	$(CXX) $(PROJECT_CXXFLAGS) -o $@ $^ $(PROJECT_LDLIBS) $(PROJECT_LDFLAGS)

clean-obj:
	rm -rf *.o *.dSYM

clean:
	rm -rf *.o $(EXE) *.dSYM
