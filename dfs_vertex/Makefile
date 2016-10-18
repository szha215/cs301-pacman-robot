OPT = -O0




default:
	gcc $(OPT) -o maze dfs_vertex_test.c map.c dfs_vertex.c dfs_traverse.c


clean:
	rm -f *.o
	rm maze

run:
	./maze

all: clean default run

#mingw32-make all