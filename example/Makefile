NAME		=	example
SRC			=	main.cpp
OBJ			=	$(SRC:.cpp=.o)
CXXFLAGS	=	-W -Wall -Wextra -Wshadow -I../Include
LFLAGS		=	-lsfml-graphics -lsfml-window -lsfml-system -L../ -lECS
CC			=	g++
RM			=	rm -rf

all:			$(NAME)

$(NAME):		$(OBJ)
				$(CC) $(OBJ) -o $(NAME) $(LFLAGS)

clean:
				$(RM) $(OBJ)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY: 		all clean fclean re
