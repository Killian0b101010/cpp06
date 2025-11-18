NAME = main 
SRC = main.cpp 
OBJ = $(SRC:.cpp=.o)
DEP = $(SRC:.cpp=.d)
FLAGS = -Wall -Wextra -Werror -std=c++98 -g3 -MMD -MP 
CC = c++
RM = rm -rf

all : $(NAME)

$(NAME): $(OBJ)
		$(CC) $(FLAGS) $(OBJ) -o ($NAME) 

main.o : main.cpp 
	$(CC) $(FLAGS) -o $@ -c $<  

clean : 
	$(RM) $(OBJ) $(DEP)

fclean : 
	$(RM) $(OBJ) $(NAME)

 re : fclean all 

.PHONY : fclean clean 

-include $DEP	
