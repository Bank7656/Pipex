CC = cc
#CFLAGS = -g
CFLAGS = -Wall -Wextra -Werror

HEADER = pipex.h
HEADER_DIR = ./

SRC = main.c getter.c child.c parent.c parser.c error_handle.c
SRC_OBJS = $(SRC:.c=.o)

OBJ_DIR = ./objects/
OBJS = $(addprefix $(OBJ_DIR), $(SRC_OBJS))

BONUS_HEADER = pipex_bonus.h
BONUS_HEADER_DIR = ./

BONUS_SRC = main_bonus.c getter_bonus.c child_bonus.c parent_bonus.c parser_bonus.c error_handle_bonus.c
BONUS_SRC_OBJS = $(BONUS_SRC:.c=.o)

BONUS_OBJ_DIR = ./objects_bonus/
BONUS_OBJS = $(addprefix $(BONUS_OBJ_DIR), $(BONUS_SRC_OBJS))

NAME = pipex
BONUS_NAME = pipex

# Libft
LIBFT_NAME = libft.a
LIBFT_DIR := ./libft/
LIBFT = $(addprefix $(LIBFT_DIR), $(LIBFT_NAME))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(HEADER) $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -o $(NAME)

$(OBJ_DIR)%.o:%.c
	$(CC) $(CFLAGS) -I $(HEADER_DIR) -c  $< -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

bonus: .bonus

.bonus: $(LIBFT) $(BONUS_OBJ_DIR) $(BONUS_HEADER) $(BONUS_OBJS) 
	$(CC) $(CFLAGS) $(BONUS_OBJS) -L./libft -lft -o $(BONUS_NAME)
	touch .bonus

$(BONUS_OBJ_DIR)%.o:%.c
	$(CC) $(CFLAGS) -I $(BONUS_HEADER_DIR) -c  $< -o $@

$(BONUS_OBJ_DIR):
	mkdir $(BONUS_OBJ_DIR)

$(LIBFT) : $(LIBFT_OBJS)
	$(MAKE) -C $(LIBFT_DIR)

$(LIBFT_OBJS):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BONUS_OBJ_DIR)
	rm -f .bonus
	$(MAKE) clean -C $(LIBFT_DIR)

fclean:
	rm -rf $(NAME)
	rm -rf $(OBJ_DIR)
	rm -rf $(BONUS_OBJ_DIR)
	rm -f .bonus
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: bonus clean fclean re
