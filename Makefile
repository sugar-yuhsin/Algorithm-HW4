###############################################################
# Linux/macOS makefile for hw4_bnb (CentOS / Darwin compatible) #
###############################################################
CXX=g++
CXXFLAGS=-std=c++11 -O2
EXEC=hw4_bnb.exe
SRC=$(wildcard hw4_bnb*.c*)
INPUT_DIR=data
INPUT_FILES=$(sort $(wildcard $(INPUT_DIR)/*.txt))

all: $(EXEC)

$(EXEC): $(SRC)
	@$(CXX) $(CXXFLAGS) -o $(EXEC) $(SRC)

test:
	@for f in $(INPUT_FILES); do \
		./$(EXEC) < "$$f"; \
	done

clean:
	@rm -f $(EXEC)
