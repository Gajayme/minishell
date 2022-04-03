#NAME
NAME		= unset

#LIBFT
LIBFT_DIR	= ../../libft
LIBFT_INC	= -L $(LIBFT_DIR) -lft

#SRC
SRC			= unset.c	unset_utils.c \

#INC
INC			= unset.h

#OBJ
OBJ			= $(patsubst %.c,%.o,$(SRC))

#D_FILES
D_FILES 	= $(patsubst %.c,%.d,$(SRC))

#COMP
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

#DEPS
$(NAME): $(OBJ) $(INC)
	@echo "making unset..."
	@$(CC) $(OBJ) $(LIBFT_INC) -o $(NAME)
	@echo "unset is made >_<"
	cp unset ../

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

