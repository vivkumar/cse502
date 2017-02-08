include $(HCLIB_ROOT)/include/hclib.mak

EXE=arraysum_sequential arraysum_async_finish arraysum_async_finish_improved

all: $(EXE)

arraysum_sequential: arraysum_sequential.cpp
	$(CXX) $(PROJECT_CXXFLAGS) -o $@ $^ $(PROJECT_LDLIBS) $(PROJECT_LDFLAGS)

arraysum_async_finish: arraysum_async_finish.cpp
	$(CXX) $(PROJECT_CXXFLAGS) -o $@ $^ $(PROJECT_LDLIBS) $(PROJECT_LDFLAGS)

arraysum_async_finish_improved: arraysum_async_finish_improved.cpp
	$(CXX) $(PROJECT_CXXFLAGS) -o $@ $^ $(PROJECT_LDLIBS) $(PROJECT_LDFLAGS)

clean:
	rm -rf *.o $(EXE)
