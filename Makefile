CC = cc  # Compiler
CFLAGS = -Wall -Wextra -Werror  # Compiler flags for warnings and errors

# Mandatory source files and header
MANDATORY_HEADER = pipex.h
MANDATORY_HEADER_DIR = ./
MANDATORY_SRC = main_pipex.c getter.c child.c parent.c parser.c error_handle.c
MANDATORY_SRC_OBJS = $(MANDATORY_SRC:.c=.o)
MANDATORY_OBJ_DIR = ./objects/
MANDATORY_OBJS = $(addprefix $(MANDATORY_OBJ_DIR), $(MANDATORY_SRC_OBJS))

# Bonus source files and header
BONUS_HEADER = pipex_bonus.h
BONUS_HEADER_DIR = ./
BONUS_SRC = main_pipex_bonus.c getter_bonus.c child_bonus.c parent_bonus.c parser_bonus.c error_handle_bonus.c
BONUS_SRC_OBJS = $(BONUS_SRC:.c=.o)
BONUS_OBJ_DIR = ./objects_bonus/
BONUS_OBJS = $(addprefix $(BONUS_OBJ_DIR), $(BONUS_SRC_OBJS))

# Executable name
NAME = pipex

# Libft library configuration
LIBFT_NAME = libft.a
LIBFT_DIR := ./libft/
LIBFT = $(addprefix $(LIBFT_DIR), $(LIBFT_NAME))

# Select whether to build mandatory or bonus
ifeq ($(WITH_BONUS), 1)
	OBJS = $(BONUS_OBJS)
	OBJ_DIR = $(BONUS_OBJ_DIR)
	HEADER = $(BONUS_HEADER)
	HEADER_DIR = $(BONUS_HEADER_DIR)
else
	OBJS = $(MANDATORY_OBJS)
	OBJ_DIR = $(MANDATORY_OBJ_DIR)
	HEADER = $(MANDATORY_HEADER)
	HEADER_DIR = $(MANDATORY_HEADER_DIR)
endif

# Default target - builds mandatory version
all:
	rm -rf $(BONUS_OBJ_DIR)
	make $(NAME) WITH_BONUS=0

# Build bonus version
bonus:
	rm -rf $(MANDATORY_OBJ_DIR)
	make $(NAME) WITH_BONUS=1

# Build the executable
$(NAME): $(LIBFT) $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -o $(NAME)

# Compile object files from source files
$(OBJ_DIR)%.o:%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(HEADER_DIR) -c  $< -o $@

# Create object directory if it does not exist
$(OBJ_DIR):
	mkdir -p $@

# Build Libft library
$(LIBFT) : 
	$(MAKE) -C $(LIBFT_DIR)

# Clean compiled object files
clean:
	rm -rf $(OBJ_DIR) $(BONUS_OBJ_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)

# Remove executable and object files
fclean:
	rm -rf $(NAME)
	rm -rf $(OBJ_DIR) $(BONUS_OBJ_DIR)
	$(MAKE) fclean -C $(LIBFT_DIR)

# Rebuild everything from scratch
re: fclean all

# Declare phony targets to prevent conflicts with actual file names
.PHONY: all bonus clean fclean re
