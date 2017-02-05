include $(HCLIB_ROOT)/include/hclib.mak

EXE=pointer_increment bank_transactions

all: clean $(EXE) clean-obj

pointer_increment: pointer_increment.cpp
	g++ $(PROJECT_CXXFLAGS) -o $@ $^ -L . $(PROJECT_LDLIBS) $(PROJECT_LDFLAGS)

bank_transactions: bank_transactions.cpp
	g++ $(PROJECT_CXXFLAGS) -o $@ $^ -L . $(PROJECT_LDLIBS) $(PROJECT_LDFLAGS)

clean-obj:
	rm -rf *.o *.dSYM

clean:
	rm -rf *.o $(EXE) *.dSYM
