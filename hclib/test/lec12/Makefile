include $(HCLIB_ROOT)/include/hclib.mak

EXE=fib_reducer pointer_increment bank_transactions

all: clean $(EXE) clean-obj

fib_reducer: fib_reducer.cpp
	$(CXX) $(PROJECT_CXXFLAGS) -o $@ $^ $(PROJECT_LDLIBS) $(PROJECT_LDFLAGS)

pointer_increment: pointer_increment.cpp
	$(CXX) $(PROJECT_CXXFLAGS) -o $@ $^ $(PROJECT_LDLIBS) $(PROJECT_LDFLAGS)

bank_transactions: bank_transactions.cpp
	$(CXX) $(PROJECT_CXXFLAGS) -o $@ $^ $(PROJECT_LDLIBS) $(PROJECT_LDFLAGS)

clean-obj:
	rm -rf *.o *.dSYM

clean:
	rm -rf *.o $(EXE) *.dSYM
