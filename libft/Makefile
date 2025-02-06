CC = cc
CFLAGS = -g -Wall -Wextra -Werror

SRC = 	ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_atoi.c \
		ft_strncmp.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_printf.c \
		ft_is_specifier.c \
		ft_get_char.c \
		ft_get_string.c \
		ft_get_number.c \
		ft_get_unsigned.c \
		ft_get_hex.c \
		ft_get_memmory.c \
		ft_get_percent.c \
		ft_power_base.c \
		ft_is_flag.c \
		ft_get_flag.c \
		ft_is_space.c \
		ft_width.c \
		ft_is_precision.c \
		ft_get_specifier.c \
		ft_is_plus.c \
		ft_is_sharp.c \
		ft_is_zero.c \
		ft_count_digit.c \
		get_next_line.c \

OBJECTS = $(SRC:.c=.o)
HEADER = libft.h
NAME = libft.a

all: $(NAME)

$(NAME): $(OBJECTS) $(HEADER)
	ar -rcs $(NAME) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -I ./ -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
