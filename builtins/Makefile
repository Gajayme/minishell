#RULES
all:
	@cd ./dir_echo && make all && mv echo ../echo
	@cd ./dir_env && make all && mv env ../env
	@cd ./dir_export && make all && mv export ../export
	@cd ./dir_pwd && make all && mv pwd ../pwd
	@cd ./dir_unset && make all && mv unset ../unset

clean:
	@cd ./dir_echo && make clean
	@cd ./dir_env && make clean
	@cd ./dir_export && make clean
	@cd ./dir_pwd && make clean
	@cd ./dir_unset && make clean

fclean:
	@cd ./dir_echo && make clean
	@rm -f echo
	@cd ./dir_env && make fclean
	@rm -f env
	@cd ./dir_export && make fclean
	@rm -f export
	@cd ./dir_pwd && make fclean
	@rm -f pwd
	@cd ./dir_unset && make fclean
	@rm -f unset

re:
	@cd ./dir_echo && make re && mv echo ../echo
	@cd ./dir_env && make re && mv env ../env
	@cd ./dir_export && make re && mv export ../export
	@cd ./dir_pwd && make re && mv pwd ../pwd
	@cd ./dir_unset && make re && mv unset ../unset

#OTHER
.PHONY: all clean fclean re
