NAME = my_containers

SRC = main.cpp

TESTDIR = tests
TESTSRCS = $(wildcard $(TESTDIR)/*.cpp)
TESTNAME = containers_test
TESTOBJS = $(TESTSRCS:%.cpp=%.o)

OBJ = main.o
DIRS = commons vector
INCLUDES = $(addprefix -I ,$(DIRS))
CXXFLAGS = -std=c++98 -Wall -Wextra -Werror $(INCLUDES)
CXX = c++


all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@

clean:
	$(RM) $(OBJ) $(TESTOBJS)

fclean: clean
	$(RM) $(NAME) $(TESTNAME)

re: fclean all

$(TESTDIR)/%.o: $(TESTDIR)/%.cpp
	$(CXX) -std=c++11 $(INCLUDES) -c $< -o $@

test: $(TESTOBJS)
	$(CXX) $(TESTOBJS) -o $(TESTNAME) -lcriterion
	./$(TESTNAME)

test_on_docker:
	docker build -t ft_containers:latest .
	docker run --rm ft_containers:latest

.PHONY: all clean fclean re test
