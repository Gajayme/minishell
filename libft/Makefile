SRCS	= 	${wildcard *.c}			\
			${wildcard PressF/*.c}	\

OBJS	=	$(SRCS:.c=.o)

HEADS	=	libft.h

NAME	=	libft.a

GCC		=	gcc -g -c -Wall -Wextra -Werror -MMD

AR		=	ar -crs

RM		=	rm -f

%.o: 		%.c	$(HEADS)
			$(GCC) -I./ $< -o $@

$(NAME):	$(OBJS)
			$(AR) $(NAME) $?

all:		$(NAME)

clean:
			$(RM) ${wildcard PressF/*.d}
			$(RM) $(wildcard *.d)
			$(RM) $(OBJS)

fclean: 	clean
			$(RM) $(NAME)

re:			fclean all