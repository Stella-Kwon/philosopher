NAME = philo

INCLUDES = -I./

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=thread

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
		valid_arg.c


#-lpthread
# ThreadSanitizer (-fsanitize=thread):

# 목적: 데이터 경합(race conditions), 잠금 순서 위반(lock order violations), 그리고 기타 동시성 문제를 감지합니다.
# 사용 경우: 멀티쓰레드 프로그램에서의 동시성 문제를 찾기 위해 사용합니다.
# AddressSanitizer (-fsanitize=address):

# 목적: 메모리 관련 오류, 예를 들어 버퍼 오버플로, 사용 후 해제된 메모리 접근(use-after-free), 해제된 메모리 접근(double-free) 등을 감지합니다.
# 사용 경우: 메모리 관리 문제가 의심될 때 사용합니다.
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