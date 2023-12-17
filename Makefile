CXXFLAGS :=-g -std=c++17
LDFLAGS :=-lsfml-graphics -lsfml-window -lsfml-system

SOURCES := $(wildcard *.cc) $(wildcard */*.cc)
EXECUTABLES := $(patsubst %.cc,%,$(SOURCES))

main: $(SOURCES) 
	g++ $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: apple
apple: $(SOURCES) # Används vid körning på macOS
	g++ $(CXXFLAGS) -o $@ $^ -I/opt/homebrew/Cellar/sfml/2.6.1/include -L/opt/homebrew/Cellar/sfml/2.6.1/lib $(LDFLAGS)


.PHONY: clean
clean:
	rm -rf ./main ./apple
