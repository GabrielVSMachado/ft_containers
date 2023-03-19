NAME = my_containers

SRC = main.cpp

TESTDIR = tests
TESTSRCS = $(wildcard $(TESTDIR)/*.cpp)
TESTNAME = containers_test
TESTOBJS = $(TESTSRCS:%.cpp=%.o)

PERFORMANCEDIR = tests/performance
PERFORMANCESRCS = $(wildcard $(PERFORMANCEDIR)/*.cpp)
PERFORMANCE_NAME = my_containers_performance
PERFORMANCEOBJS = $(PERFORMANCESRCS:%.cpp=%.o)

OBJ = main.o
DIRS = commons vector map stack set tests
INCLUDES = $(addprefix -I ,$(DIRS))
CXXFLAGS = -std=c++98 -Wall -Wextra -Werror $(INCLUDES)
CXX = c++


all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	$(RM) $(OBJ) $(TESTOBJS) $(PERFORMANCEOBJS)

fclean: clean
	$(RM) $(NAME) $(TESTNAME) $(PERFORMANCE_NAME)

re: fclean all

performance: $(PERFORMANCE_NAME)

test: $(TESTNAME)

$(PERFORMANCE_NAME): $(PERFORMANCEOBJS)
	$(CXX) $(CXXFLAGS) $< -o $@


$(TESTNAME): fclean $(TESTOBJS)
	$(CXX) $(CXXFLAGS) $(TESTOBJS) -o $@
	valgrind --leak-check=full --show-leak-kinds=all ./$(TESTNAME)

test_on_docker:
	docker build -t ft_containers:latest .
	docker run --rm ft_containers:latest

.PHONY: all clean fclean re test test_on_docker
