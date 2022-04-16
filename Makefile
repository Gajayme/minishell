SRCS		=	${wildcard *.c}				\
				${wildcard GetNextLine/*.c}	\
				${wildcard funcs/*/*.c}		\

B_SRCS		=	${wildcard *_bonus.c}		\
				${wildcard GetNextLine/*.c}	\

OBJS		=	$(SRCS:.c=.o)	

B_OBJS		=	$(B_SRCS:.c=.o)	

HEADS		=	minishell.h

LIBNAME		=	libft.a

CD			=	funcs/cd

EXIT		=	funcs/exit

LIBPATH		=	libft/

LIB			=	$(addprefix $(LIBPATH), $(LIBNAME))

BLTIN		=	builtins

GNL			=	GetNextLine

NAME		=	minishell

GCC			=	gcc -g -MMD -Wall -Wextra -Werror

RM			=	rm -f

READCLUDE	= -I~/.brew/opt/readline/include

READLINE	= -lreadline -L ~/.brew/opt/readline/lib $(READCLUDE)

%.o: 		%.c
			$(GCC) -c -I$(LIBPATH) -I$(GNL) -I$(CD) -I$(EXIT) $(READCLUDE) $< -o $@

$(NAME):	$(HEADS) $(LIB) $(OBJS) $(BLTIN)
			$(GCC) $(OBJS) $(LIB) -o $(NAME) $(READLINE)
			

$(BLTIN):	bltin

bltin:
			@$(MAKE) -C $(BLTIN)

all:		$(NAME)

$(LIB):		lib

lib:		
			@$(MAKE) -C $(LIBPATH)

bonus:		$(NAME)
			@echo "o, privet! tut takoe delo, nashi bonusy "
			@echo "vshity v kod iznachal'no i razorvat' proekt na "
			@echo "2 chasti ves'ma problematichno, poetomu vse "
			@echo "kompilitsya srazu. v realizacii bonusov my ne "
			@echo "ispol'zovali ni odnoy zapreschennoy funkcii, "
			@echo "potomu problem c chitami i normoy net. v to je vremya, "
			@echo "subj trebuet otdel'noe pravilo pod bonusy, poetomu ty "
			@echo "schas eto i chitaesh'))00)"

clean:
			@$(MAKE) -C $(LIBPATH) clean
			@$(MAKE) -C $(BLTIN) clean
			$(RM) $(wildcard *.d)
			$(RM) ${wildcard GetNextLine/*.d}
			$(RM) $(OBJS)
			$(RM) $(B_OBJS)

fclean: 	clean
			@$(MAKE) -C $(LIBPATH) fclean
			@$(MAKE) -C $(BLTIN) fclean
			$(RM) $(NAME)
			$(RM) $(B_NAME)

re:			fclean all

.PHONY:		all bonus clean fclean re lib