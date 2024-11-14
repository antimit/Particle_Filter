CXX = g++
CXXFLAGS = -fdiagnostics-color=always -g
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
INCLUDE_DIR = $(PWD)
SRC = $(wildcard *.cpp) 
OBJ = $(SRC:.cpp=.o)
OUT = $(PWD)/myProgram


all: $(OUT)


$(OUT): $(OBJ)
	$(CXX) $(OBJ) -o $(OUT) $(LDFLAGS)


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@



clean:
	rm -rf $(OBJ) 

fclean:clean
	rm -rf $(OUT)


.PHONY: all clean
