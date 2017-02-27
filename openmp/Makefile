EXE=data reduction orphan linked_tasks

all: $(EXE)

linked_tasks: linked_tasks.c
	gcc -O3 -o $@ $^ -fopenmp

reduction: reduction.c
	gcc -O3 -o $@ $^ -fopenmp

orphan: orphan.c
	gcc -O3 -o $@ $^ -fopenmp

data: data.c
	gcc -O3 -o $@ $^ -fopenmp

clean:
	rm -rf *.o $(EXE)
