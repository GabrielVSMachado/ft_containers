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

TEST_FT_PERFORMANCE = ft_containers_performance
TEST_STL_PERFORMANCE = stl_containers_performance

PERFORMANCE_FT_DIR = $(TESTDIR)/performance
PERFORMANCE_STL_DIR = $(TESTDIR)/original_performance

all: $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C $(TESTDIR)
	$(MAKE) clean -C $(PERFORMANCE_FT_DIR)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(TESTDIR)
	$(MAKE) fclean -C $(PERFORMANCE_FT_DIR)

re: fclean all

test:
	$(MAKE) -C $(TESTDIR)
	./$(TESTDIR)/$(TESTNAME)

test_ft_performance:
	$(MAKE) -C $(PERFORMANCE_FT_DIR)
	./$(PERFORMANCE_FT_DIR)/$(TEST_FT_PERFORMANCE)

test_with_valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./$(TESTDIR)/$(TESTNAME)

test_on_docker:
	docker build -t ft_containers:latest .
	docker run --rm ft_containers:latest

.PHONY: all clean fclean re test test_on_docker test_with_valgrind
