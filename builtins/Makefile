#DEPS

INC = $(wildcard */*.h)
SRC = $(wildcard */*.c)

#RULES
all: $(INC) $(SRC)
	@$(MAKE) -C ./dir_echo
	@$(MAKE) -C ./dir_env
	@$(MAKE) -C ./dir_export
	@$(MAKE) -C ./dir_pwd
	@$(MAKE) -C ./dir_unset

clean:
	@$(MAKE) -C ./dir_echo clean
	@$(MAKE) -C ./dir_env clean
	@$(MAKE) -C ./dir_export clean
	@$(MAKE) -C ./dir_pwd clean
	@$(MAKE) -C ./dir_unset clean

fclean:
	@$(MAKE) -C ./dir_echo fclean
	@$(MAKE) -C ./dir_env fclean
	@$(MAKE) -C ./dir_export fclean
	@$(MAKE) -C ./dir_pwd fclean
	@$(MAKE) -C ./dir_unset fclean
	@rm -f echo
	@rm -f env
	@rm -f export
	@rm -f pwd
	@rm -f unset

re: fclean
	@rm -f echo
	@rm -f env
	@rm -f export
	@rm -f pwd
	@rm -f unset
	@$(MAKE) -C ./dir_echo re
	@$(MAKE) -C ./dir_env re
	@$(MAKE) -C ./dir_export re
	@$(MAKE) -C ./dir_pwd re
	@$(MAKE) -C ./dir_unset re

#OTHER
.PHONY: all clean fclean re
