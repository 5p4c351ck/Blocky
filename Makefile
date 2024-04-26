objs = grid.o rendering.o main.o
executable = blocky

all: $(executable)

$(executable): $(objs) 
	gcc $(objs) -o $(executable) -lSDL2 -lSDL2_ttf

grid.o: grid.c
	gcc grid.c -c -o grid.o


rendering.o: rendering.c
	gcc rendering.c -c -o rendering.o

main.o: main.c
	gcc main.c -c -o main.o

clean:
	rm $(objs) $(executable)
