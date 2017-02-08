include $(HCLIB_ROOT)/include/hclib.mak

EXE=matmul_seq matmul_forasync2D averaging_forasync1D

all: $(EXE)

averaging_forasync1D: averaging_forasync1D.cpp
	$(CXX) -O3 $(PROJECT_CXXFLAGS) -o $@ $^ $(PROJECT_LDLIBS) $(PROJECT_LDFLAGS)

matmul_seq: matmul_seq.cpp
	$(CXX) -O3 $(PROJECT_CXXFLAGS) -o $@ $^ $(PROJECT_LDLIBS) $(PROJECT_LDFLAGS)

matmul_forasync2D: matmul_forasync2D.cpp
	$(CXX) -O3 $(PROJECT_CXXFLAGS) -o $@ $^ $(PROJECT_LDLIBS) $(PROJECT_LDFLAGS)

clean:
	rm -rf *.o $(EXE)
