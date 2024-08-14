NAME = philo

INCLUDES = -I./

CFLAGS = -Wall -Wextra -Werror -g
#-fsanitize=thread
#-lpthread
SRCS = philo.c \
		free.c \
		ft_atoi.c \
		get_time.c\
		initialize_struct.c\
		monitor.c \
		mutex.c\
		print_shell.c\
		routines.c\
		actions.c\
		threads.c\
		valid_arg.c\
		left_right_forks.c

OBJS = ${SRCS:.c=.o}

all: ${NAME}

$(NAME): $(OBJS)
		@gcc $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS)
		@echo "\n$(Yellow)---------PHILOSOPHER_FINISHED---------$(Ending)\n"

$(OBJS): %.o: %.c 
		@gcc $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	@rm -f ${OBJS}
	@rm -rf *.dSYM
	@rm -rf .vscode
	@rm -rf .DS_Store

fclean: clean
	@rm -f ${NAME}
	@echo "\n$(Magenta)---------CLEANED_EVERYTHING---------$(Ending)\n"

re: fclean all

.PHONY: all clean fclean re


Red = \033[0;31m
Green = \033[0;32m
Yellow = \033[0;33m
Blue = \033[0;34m
Magenta = \033[0;35m
Cyan = \033[0;36m
White = \033[0;37m
Ending = \033[0m
