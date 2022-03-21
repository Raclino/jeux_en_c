##
## ETNA PROJECT, 14/06/2021 by dousse_r
## /home/slowiizz/Documents/etna/SummerProject
## File description:
##      make file du projet
##

CC		= 	gcc
CFLAGS	=	-Wall -Wextra -Werror -I./include -lSDL2 -lSDL2_image -lSDL2_ttf -std=c17
NAME	=	AstroRun
SRC		= 	./src/main.c	\
			./src/game.c	\
			./src/asteroids.c	\
			./src/player.c	\
			./src/window.c	\
			./src/draw.c	\
			./src/leaderboard.c

OBJ		=	$(SRC:%.c=%.o)
RM		=	rm -f

$(NAME):		$(OBJ)
				$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
all:			$(NAME)
clean:
				$(RM) $(OBJ)
fclean:			clean
				$(RM) $(NAME)
re:	fclean all
