NAME = my_containters

SRC = main.cpp

TESTDIR = tests
OBJ = main.o
DIRS = commons vector
INCLUDES = -I $(DIRS)
CXXFLAGS = -std=c++98 -Wall -Wextra -Werror $(INCLUDES)
CXX = c++


all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) clean -C $(TESTDIR)

re: fclean all

test:
	$(MAKE) -C $(TESTDIR)
	./tests/unittests
	$(MAKE) clean -C $(TESTDIR)

.PHONY: all clean fclean re test
