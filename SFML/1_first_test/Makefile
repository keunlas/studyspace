SFML_FLAGS := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

all: main.out

main.out: main.cpp
	g++ $^ -o $@ $(SFML_FLAGS) -g

clean:
	rm main.out

rebuild: clean all
