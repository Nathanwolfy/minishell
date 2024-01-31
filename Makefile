NAME = minishell

SRCS_MAIN_FILES = minishell.c \
					prompt.c \
					errors.c

SRCS_UTILS_FILES = utils.c \
					utils_tree.c \
					utils_envp.c

SRCS_LEXING_FILES = lexing.c \
						lexing_utils.c \
						ft_token.c

SRCS_PARSING_FILES = ft_tree.c \
						ast_tree/ast_builder.c			\
						ast_tree/ast_builder_utils.c	\
						ast_tree/ast_builder_utils2.c	\
						ast_tree/parse_functions.c		\
						ast_tree/parse_simple_cmd.c		\
						ast_tree/parse_io_redirect.c

SRCS_INTERPRETER_FILES = interpreter.c \
							interpreter_redirects.c \
							interpreter_pipes.c \
							cmd_process.c \
							cmd_infos_utils.c \
							quote_formating.c \
							quote_formating_utils.c

SRCS_MAIN = $(addprefix srcs/, $(SRCS_MAIN_FILES))

SRCS_UTILS = $(addprefix srcs/utils/, $(SRCS_UTILS_FILES))

SRCS_LEXING = $(addprefix srcs/lexing/, $(SRCS_LEXING_FILES))

SRCS_PARSING = $(addprefix srcs/parsing/, $(SRCS_PARSING_FILES))

SRCS_INTERPRETER = $(addprefix srcs/interpreter/, $(SRCS_INTERPRETER_FILES))

OBJS_MAIN = $(SRCS_MAIN:.c=.o)

OBJS_UTILS = $(SRCS_UTILS:.c=.o)

OBJS_LEXING = $(SRCS_LEXING:.c=.o)

OBJS_PARSING = $(SRCS_PARSING:.c=.o)

OBJS_INTERPRETER = $(SRCS_INTERPRETER:.c=.o)

OBJS = $(OBJS_MAIN) $(OBJS_UTILS) $(OBJS_LEXING) $(OBJS_PARSING) $(OBJS_INTERPRETER) 

###

LIBFT_NAME = libft.a

LIBFT_lib = ft

DIR_libft = libft/

LIBFT_SRC = $(addprefix $(DIR_libft), $(LIBFT_NAME))

###

DEF_COLOR = \033[0;39m

GREEN = \033[0;92m

###

CC = cc

CFLAGS = -Wall -Wextra -Werror

LIBS = -L. -lreadline -L$(DIR_libft) -l$(LIBFT_lib)

RM = rm -rf

INCLUDES = ./includes

###

%.o: %.c
	@$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@ 

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(DIR_libft)
	@$(CC) $(CFLAGS) -I$(INCLUDES) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)$(NAME) created successfully!$(DEF_COLOR)"

clean:
	@make clean -C $(DIR_libft)
	@$(RM) $(OBJS)

fclean: clean
	@make fclean -C $(DIR_libft)
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean all re
