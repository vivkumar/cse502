EXE=data reduction orphan linked_tasks omp_nested

all: $(EXE)

omp_nested: omp_nested.c
	gcc -O3 -o $@ $^ -fopenmp

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
