/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:46:19 by thacharo          #+#    #+#             */
/*   Updated: 2025/02/02 14:49:22 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# ifndef __LINUX__
#  define __LINUX__ 0
# endif
# if __APPLE__
#  define NULL_PTR "0x0"
# else
#  define __APPLE__ 0
#  define NULL_PTR "(nil)"
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdint.h>
# include <stdarg.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_arg
{
	int		len;
	int		width;
	int		precision;
	int		width_arg;
	int		precision_arg;
	int		minus;
	int		hash;
	int		space;
	int		plus;
	int		zero;
	int		isnull;
	char	*word;
	char	specifier;
}	t_arg;

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
size_t		ft_strlen(const char *s);
void		*ft_memset(void *s, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t len);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
int			ft_toupper(int c);
int			ft_tolower(int c);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t len);
int			ft_atoi(const char *nptr);
void		*ft_calloc(size_t nemb, size_t size);
char		*ft_strdup(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int			ft_printf(const char *s, ...)
			__attribute__ ((format (printf, 1, 2)));
int			ft_is_flag(char c);
int			ft_count_digit(int n);
int			ft_is_plus(t_arg *arg);
int			ft_is_specifier(char c);
int			ft_is_sharp(t_arg *arg);
int			ft_is_space(t_arg *arg);
int			ft_is_precision(t_arg *arg);
int			ft_width(t_arg *arg);
int			zero_number(t_arg *arg);
int			zero_hex(t_arg *arg);
int			zero_space(t_arg *arg);
int			ft_get_percent(t_arg *arg);
int			ft_get_hex(t_arg *arg, va_list *ptr);
int			ft_get_char(t_arg *arg, va_list *ptr);
int			ft_get_string(t_arg *arg, va_list *ptr);
int			ft_get_number(t_arg *arg, va_list *ptr);
int			ft_get_memmory(t_arg *arg, va_list *ptr);
int			ft_get_unsigned(t_arg *arg, va_list *ptr);
void		ft_get_flag(t_arg *arg, char c);
void		update_arg(t_arg *arg, char **tmp);
void		ft_get_specifier(t_arg *arg, const char *s, int *i);
void		ft_get_asterisk_arg(t_arg *arg, va_list *ptr, int n);
size_t		ft_power(int base, int n);
int			clear_remain(char **line, char **remain, char *tmp, int count);
char		*get_next_line(int fd);
char		*get_remain(char **remain, char *buffer, int *remain_check);
char		*get_read(char **line, char **remaining, char **buffer, int fd);
void		get_current_line(char **line, char *buffer);

#endif
