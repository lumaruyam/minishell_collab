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
		exec_family.c exec_redirs.c exec_utils1.c exec_utils2.c exec.c \
		expand_env.c expand_utils.c expand.c ft_arrys_utils.c ft_cd.c ft_echo.c \
		ft_env_pwd.c ft_exit.c ft_export.c ft_unset.c heredoc.c lexing_utils.c \
		lexing.c main_init.c main_free.c main.c parsing.c quotes_utils.c quotes.c \
		signal_utils.c signal.c tokens.c signal_utils2.c exec_utils3.c

SRCS = $(addprefix $(SRC_DIR), $(SRC))
OBJS = $(SRCS:.c=.o)
LIBFT_A = $(LIBFT_DIR)/libft.a

# **************************************************************************** #
#                            COMPILER & FLAGS                                  #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR)/inc
LFLAGS = -L$(LIBFT_DIR) -lft
LDFLAGS = -lreadline
RM = rm -rf

# **************************************************************************** #
#                               BUILD COMMANDS                                 #
# **************************************************************************** #

all: $(NAME)
	$(print_flag)

$(NAME): $(OBJS) $(LIBFT_A)
	@$(CC) $(FLAGS) $(OBJS) $(LFLAGS) -o $(NAME) $(LDFLAGS)

$(SRC_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(FLAGS) -c $< -o $@
	@echo "$(GREENB)--- ⛑️ Compiling $< to $@ ⛑️---$(COLOR_RESET)"

$(LIBFT_A):
	@make -C $(LIBFT_DIR)

clean:
	@$(RM) $(OBJS)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(LIBFT_DIR)

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
