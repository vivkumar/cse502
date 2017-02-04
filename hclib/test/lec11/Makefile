include $(HCLIB_ROOT)/include/hclib.mak

EXE=matmul_seq matmul_forasync2D

all: $(EXE)

matmul_seq: matmul_seq.cpp
	g++ -O3 $(PROJECT_CXXFLAGS) -o $@ $^ -L . $(PROJECT_LDLIBS) $(PROJECT_LDFLAGS)

matmul_forasync2D: matmul_forasync2D.cpp
	g++ -O3 $(PROJECT_CXXFLAGS) -o $@ $^ -L . $(PROJECT_LDLIBS) $(PROJECT_LDFLAGS)

clean:
	rm -rf *.o $(EXE)
