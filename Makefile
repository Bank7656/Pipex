CC = cc
#CFLAGS = -g
CFLAGS = -Wall -Wextra -Werror

HEADER = pipex.h
HEADER_DIR = ./

SRC = main_pipex.c getter.c child.c parent.c parser.c error_handle.c
SRC_OBJS = $(SRC:.c=.o)

OBJ_DIR = ./objects/
OBJS = $(addprefix $(OBJ_DIR), $(SRC_OBJS))

BONUS_HEADER = pipex_bonus.h
BONUS_HEADER_DIR = ./

BONUS_SRC = main_pipex_bonus.c getter_bonus.c child_bonus.c parent_bonus.c parser_bonus.c error_handle_bonus.c
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

$(NAME): $(LIBFT) $(OBJS) $(HEADER)  
	$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -o $(NAME)

$(OBJ_DIR)%.o:%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(HEADER_DIR) -c  $< -o $@

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(LIBFT) $(BONUS_OBJS) $(BONUS_HEADER) 
	$(CC) $(CFLAGS) $(BONUS_OBJS) -L./libft -lft -o $(BONUS_NAME)	

$(BONUS_OBJ_DIR)%.o:%.c | $(BONUS_OBJ_DIR)
	$(CC) $(CFLAGS) -I $(BONUS_HEADER_DIR) -c  $< -o $@

$(OBJ_DIR) $(BONUS_OBJ_DIR):
	mkdir -p $@

$(LIBFT) : 
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR) $(BONUS_OBJ_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean:
	rm -rf $(NAME)
	rm -rf $(BONUS_NAME)
	rm -rf $(OBJ_DIR) $(BONUS_OBJ_DIR)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all bonus clean fclean re
