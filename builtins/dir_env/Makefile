#NAME
NAME		= env

#LIBFT
LIBFT_DIR	= ./../../libft
LIBFT_INC	= -L $(LIBFT_DIR) -lft

#SRC
SRC			= env.c	env_utils.c \
			env_lib_utils.c	env_change.c \
			env_exit.c env_acess.c \
#INC
INC			= env.h

#OBJ
OBJ			= $(patsubst %.c,%.o,$(SRC))

#D_FILES
D_FILES 	= $(patsubst %.c,%.d,$(SRC))

#COMP
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

#DEPS
$(NAME): $(OBJ) $(INC)
	@echo "making env..."
	@$(CC) $(OBJ) $(LIBFT_INC) -o $(NAME)
	@echo "env is made >_<"
%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -MD

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

