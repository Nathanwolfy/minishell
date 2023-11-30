NAME = minishell

SRCS_FILES = minishell.c

SRCS = $(addprefix srcs/, $(SRCS_FILES))

OBJS = $(SRCS:.c=.o)

###

DEF_COLOR = \033[0;39m

GREEN = \033[0;92m

###

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

###

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ 

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)$(NAME) created successfully!$(DEF_COLOR)"

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME) 

re: fclean all

.PHONY: all clean fclean all re
