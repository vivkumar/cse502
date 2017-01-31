include $(HCLIB_ROOT)/include/hclib.mak

EXE=asyncAtPlaces

all: $(EXE)

asyncAtPlaces: asyncAtPlaces.cpp
	g++ $(PROJECT_CXXFLAGS) -o $@ $^ -L . $(PROJECT_LDLIBS) $(PROJECT_LDFLAGS)

clean:
	rm -rf *.o $(EXE)
