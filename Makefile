NAME = minishell

SRCS_FILES = minishell.c \
			test_readline.c

SRCS = $(addprefix srcs/, $(SRCS_FILES))

OBJS = $(SRCS:.c=.o)

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

LIBS = -lreadline -L$(DIR_libft) -l$(LIBFT_lib)

RM = rm -rf

###

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ 

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(DIR_libft)
	@$(CC) $(CFLAGS) $(LIBS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)$(NAME) created successfully!$(DEF_COLOR)"

clean:
	@make clean -C $(DIR_libft)
	@$(RM) $(OBJS)

fclean: clean
	@make fclean -C $(DIR_libft)
	@$(RM) $(NAME) 

re: fclean all

.PHONY: all clean fclean all re
