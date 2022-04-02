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

PIPPATH		=	pipex/

LIB			=	$(addprefix $(LIBPATH), $(LIBNAME))

BLTIN		=	builtins

GNL			=	GetNextLine

NAME		=	minishell

GCC			=	gcc -g -MMD

RM			=	rm -f

READLINE_EBANIY	= -lreadline -L ~/.brew/opt/readline/lib -I~/.brew/opt/readline/include

%.o: 		%.c
			$(GCC) -c -I$(LIBPATH) -I$(GNL) -I$(CD) -I$(EXIT) -I~/.brew/opt/readline/include $< -o $@

$(NAME):	$(HEADS) $(LIB) $(OBJS) $(BLTIN)
			$(GCC) $(OBJS) $(LIB) -o $(NAME) $(READLINE_EBANIY)
			

$(BLTIN):	bltin

bltin:
			$(MAKE) -C $(BLTIN)

all:		$(NAME)

$(LIB):		lib

lib:		
			@$(MAKE) -C $(LIBPATH)

bonus:		clean $(HEADS) $(B_OBJS) $(LIB)
			$(GCC) $(B_OBJS) $(LIB) -L$(MLX) -l$(MLX) $(FRAMEWORKS) -o $(NAME)

clean:
			@$(MAKE) -C $(LIBPATH) clean
			$(MAKE) -C $(BLTIN) clean
			$(RM) $(wildcard *.d)
			$(RM) ${wildcard GetNextLine/*.d}
			$(RM) $(OBJS)
			$(RM) $(B_OBJS)

fclean: 	clean
			@$(MAKE) -C $(LIBPATH) fclean
			$(MAKE) -C $(BLTIN) fclean
			$(RM) $(NAME)
			$(RM) $(B_NAME)

re:			fclean all

.PHONY:		all bonus clean fclean re lib