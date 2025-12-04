
NAME = main

SRC = ScalarType.cpp \
      main.cpp

OBJ = $(SRC:.cpp=.o)
DEP = $(SRC:.cpp=.d)

FLAGS = -Wall -Wextra -Werror -std=c++98 -g3 -MMD -MP
CC = c++
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(DEP)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re

-include $(DEP)
