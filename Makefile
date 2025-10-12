# **************************************************************************** #
#                                 NAME / MAIN                                  #
# **************************************************************************** #

NAME = minishell

# **************************************************************************** #
#                                 DIRECTORIES                                  #
# **************************************************************************** #

INC_DIR = inc
SRC_DIR = ./src/
LIBFT_DIR = libft

SRC = build_args.c build_filename.c build_to_exec.c build_utils.c builtins_env.c \
		builtins_err.c builtins_handler.c env.c exec_err.c exec_execution.c \
		exec_family.c exec_redirs.c

SRCS = $(addprefix $(SRC_PATH), $(SRC))
OBJS = $(SRCS:.c=.o)

CC = cc
FLAGS = -Wall -Wextra -Werror -I inc







all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re libft

# **************************************************************************** #
#                              COLOR SETTING                                   #
# **************************************************************************** #

COLOR_RESET = \033[0m
PINKB = \033[1;95m
REDB = \033[1;91m
ROSEB = \033[1;38;5;225m
BLUEB = \033[1;34m
BABEBLUEB = \033[1;38;5;153m
GREENB = \033[1;38;5;85m
PURPLEB = \033[1;38;5;55m
PSTL_YELLOWB = \033[1;38;2;255;253;208m
PSTL_ORGB = \033[1;38;2;255;179;102m
PSTL_PURPLEB =\033[1;38;2;204;153;255m

GREEN_BBG = \033[1;42m
BLUE_BBG = \033[1;44m
YELLOW_BBG = \033[1;43m
ORANGE_BBG = \033[1;48;5;214m
