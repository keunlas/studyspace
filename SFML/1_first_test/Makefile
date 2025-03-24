SFML_FLAGS := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

all: main.out

main.out: main.cpp
	g++ $^ -o $@ $(SFML_FLAGS)

clean:
	rm *.out *.o

rebuild: clean all
