include $(HCLIB_ROOT)/include/hclib.mak

EXE=asyncAtPlaces averaging_async_finish averaging_hpt

all: $(EXE)

asyncAtPlaces: asyncAtPlaces.cpp
	$(CXX) $(PROJECT_CXXFLAGS) -o $@ $^ $(PROJECT_LDLIBS) $(PROJECT_LDFLAGS)

averaging_hpt: averaging_hpt.cpp
	$(CXX) $(PROJECT_CXXFLAGS) -o $@ $^ $(PROJECT_LDLIBS) $(PROJECT_LDFLAGS)

averaging_async_finish: averaging_async_finish.cpp
	$(CXX) $(PROJECT_CXXFLAGS) -o $@ $^ $(PROJECT_LDLIBS) $(PROJECT_LDFLAGS)

clean:
	rm -rf *.o $(EXE)
