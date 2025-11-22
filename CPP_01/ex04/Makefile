CC = c++
# CXXFLAGS = -Wall -Wextra -Werror -std=c++98
CXXFLAGS = -std=c++98

NAME = SedIsForLosers

SRCS = main.cpp Replace.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re