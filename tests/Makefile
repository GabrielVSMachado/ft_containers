NAME = ft_containers_unit_tests
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:%.cpp=%.o)

DIRS = commons vector map stack set
INCLUDES = -I . $(addprefix -I ../,$(DIRS))
CXXFLAGS = -std=c++98 -Wall -Wextra -Werror $(INCLUDES)
CXX = c++
RM = rm -rf
DEP = $(OBJS:%.o=%.d)

all: $(NAME)

clean:
	$(RM) $(OBJS) $(DEP)

fclean: clean
	$(RM) $(NAME)

-include $(DEP)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

re: fclean all

.PHONY: all clean fclean re
