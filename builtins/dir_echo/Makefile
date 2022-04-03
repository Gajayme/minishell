#NAME
NAME		= echo

#SRC
SRC			= echo.c\

#OBJ
OBJ			= $(patsubst %.c,%.o,$(SRC))

#D_FILES
D_FILES 	= $(patsubst %.c,%.d,$(SRC))

#COMP
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

#DEPS
$(NAME): $(OBJ)
	@echo "making echo..."
	$(CC) $(OBJ) -o $(NAME)
	@echo "echo is made >_<"
	cp echo ../

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ -MD

include $(wildcard $(D_FILES))

#RULES
all:	$(NAME)

clean:
		@rm -f $(OBJ) && rm -f $(D_FILES)

fclean:	clean
		@rm -f $(NAME)

re:		fclean all

#OTHER
.PHONY: all clean fclean re

