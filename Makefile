CC = gcc -g
CFLAGS = -Wall -Wextra -Werror
SRC_PIPEX = ft_split.c pipex.c ft_strlen.c ft_strnstr.c ft_substr.c pipex_utils.c  ft_strjoin.c #ft_strdup.c 
PIPEX = pipex
PIPEX_OBJ = $(SRC_PIPEX:%.c=%.o)

all : $(PIPEX) 

clean :
	@rm -rf *.o
	@printf "\033[1;36mObject Files Deleted !\033[0m\n"

fclean : clean
	@rm -rf $(PIPEX)
	@printf "\033[1;36mProgram Deleted !\033[0m\n"

re : fclean all


$(PIPEX) :  $(PIPEX_OBJ) 
	@$(CC) $(CFLAGS) $(PIPEX_OBJ) -o $(PIPEX)
	@printf "\n\033[1;33m**** PIPEX compiled Succesfully ! ****\033[0m\n\n"

%.o:%.c
	@$(CC) $(CFLAGS) -c $^ 