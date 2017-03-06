EXE=pt2pt_hybrid pt2pt_reduce message_order deadlock_incorrect_pairs deadlock_incorrect_tag hello_world pt2pt_blocking pt2pt_nonblocking

all: $(EXE)

pt2pt_hybrid: pt2pt_hybrid.c
	mpicc -o $@ $^ -fopenmp

pt2pt_reduce: pt2pt_reduce.c
	mpicc -o $@ $^

message_order: message_order.c
	mpicc -o $@ $^

deadlock_incorrect_pairs: deadlock_incorrect_pairs.c
	mpicc -o $@ $^

deadlock_incorrect_tag: deadlock_incorrect_tag.c
	mpicc -o $@ $^

hello_world: hello_world.c
	mpicc -o $@ $^

pt2pt_nonblocking: pt2pt_nonblocking.c
	mpicc -o $@ $^

pt2pt_blocking: pt2pt_blocking.c
	mpicc -o $@ $^

clean:
	rm -rf *.o $(EXE)
