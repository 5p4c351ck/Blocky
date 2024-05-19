objs = grid.o rendering.o main.o options.o
executable = blocky

all: $(executable)

$(executable): $(objs) 
	gcc $(objs) -o $(executable) -lSDL2 -lSDL2_ttf

grid.o: grid.c
	gcc grid.c -c -o grid.o


rendering.o: rendering.c
	gcc rendering.c -c -o rendering.o

options.o: options.c
	gcc options.c -c -o options.o

main.o: main.c
	gcc main.c -c -g  -o main.o

clean:
	rm $(objs) $(executable)
