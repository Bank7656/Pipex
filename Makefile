CC = cc
CFLAGS = -g
# CFLAGS = -Wall -Wextra -Werror

HEADER = pipex.h
HEADER_DIR = ./

SRC = main.c
SRC_OBJS = $(SRC:.c=.o)

OBJ_DIR = ./objects/
OBJS = $(addprefix $(OBJ_DIR), $(SRC_OBJS))

NAME = pipex

# Libft
LIBFT_NAME = libft.a
LIBFT_DIR := ./libft/
LIBFT = $(addprefix $(LIBFT_DIR), $(LIBFT_NAME))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -o $(NAME)

$(OBJ_DIR)%.o:%.c
	$(CC) $(CFLAGS) -I $(HEADER_DIR) -c  $< -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(LIBFT) : $(LIBFT_OBJS)
	$(MAKE) -C $(LIBFT_DIR)

$(LIBFT_OBJS):
	$(MAKE) -C $(LIBFT_DIR)

test: $(NAME)
# ./$(NAME) infile "cat -e" "wc -l" outfile
	./$(NAME) infile "ls -l" "wc -l" outfile

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean:
	rm -rf $(NAME)
	rm -rf $(OBJ_DIR)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: 
