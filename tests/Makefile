NAME = unittests
override CXX = c++
override DIRS = commons vector
override CXXFLAGS = -std=c++11
override INCLUDES = -I $(addprefix ../,$(DIRS))
override LDLIBS = -lcriterion

override SRC = $(wildcard *.cpp)

override OBJ = $(SRC:%.cpp=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(OBJ) -o $(NAME) $(LDLIBS)

clean:
	$(RM) $(OBJ) $(NAME)

.PHONY: all clean
