objs = grid.o main.o
executable = blocky

all: $(executable)

$(executable): $(objs) 
	gcc $(objs) -o $(executable) -lSDL2

grid.o: grid.c
	gcc grid.c -c -o grid.o

main.o: main.c
	gcc main.c -c -o main.o

clean:
	rm $(objs) $(executable)
