NAME = test_main
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:%.cpp=%.o)

DIRS = commons vector map stack set
INCLUDES = $(addprefix -I ,$(DIRS))
CXXFLAGS = -std=c++98 -Wall -Wextra -Werror
CXX = c++
RM = rm -rf

TESTNAME = ft_containers_unit_tests
TESTDIR = tests

TEST_PERFORMANCE = containers_performance

PERFORMANCE_DIR = $(TESTDIR)/performance
STD = 0

all: $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C $(TESTDIR)
	$(MAKE) clean -C $(PERFORMANCE_DIR)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(TESTDIR)
	$(MAKE) fclean -C $(PERFORMANCE_DIR)

re: fclean all

test:
	$(MAKE) -C $(TESTDIR)
	./$(TESTDIR)/$(TESTNAME)

test_performance: fclean
	$(MAKE) STD=$(STD) -C $(PERFORMANCE_DIR)
	./$(PERFORMANCE_DIR)/$(TEST_PERFORMANCE)

test_with_valgrind:
	$(MAKE) -C $(TESTDIR)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TESTDIR)/$(TESTNAME)

test_on_docker:
	docker build -t ft_containers:latest .
	docker run --rm ft_containers:latest

.PHONY: all clean fclean re test test_on_docker test_with_valgrind
