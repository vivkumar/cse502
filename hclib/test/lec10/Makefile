include $(HCLIB_ROOT)/include/hclib.mak

EXE=asyncAtPlaces averaging_async_finish averaging_hpt

all: $(EXE)

asyncAtPlaces: asyncAtPlaces.cpp
	g++ $(PROJECT_CXXFLAGS) -o $@ $^ -L . $(PROJECT_LDLIBS) $(PROJECT_LDFLAGS)

averaging_hpt: averaging_hpt.cpp
	g++ $(PROJECT_CXXFLAGS) -o $@ $^ -L . $(PROJECT_LDLIBS) $(PROJECT_LDFLAGS)

averaging_async_finish: averaging_async_finish.cpp
	g++ $(PROJECT_CXXFLAGS) -o $@ $^ -L . $(PROJECT_LDLIBS) $(PROJECT_LDFLAGS)

clean:
	rm -rf *.o $(EXE)
