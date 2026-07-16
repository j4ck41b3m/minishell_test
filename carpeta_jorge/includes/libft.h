/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:26:27 by jcolina-          #+#    #+#             */
/*   Updated: 2026/06/05 11:48:52 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

void	ft_bzero(void	*s, size_t	n);
int		ft_isascii(int a);
int		ft_isalnum(int a);
int		ft_isalpha(int a);
int		ft_isdigit(int a);
int		ft_isprint(int a);
int		ft_tolower(int c);
size_t	ft_strlen(const char *c);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	ft_memfree(void *ptr);
void	ft_memfree_all(char **ptr);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_toupper(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *bi, const char *li, size_t le);
int		ft_atoi(const char *nptr);
long	ft_atol(const char *str);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
//FT_PRINTF
int		ft_printf(const char *str, ...);
int		nbrprinter(va_list args);
int		strprinter(va_list args);
int		uprinter(va_list args);
int		hexprinter(char type, unsigned long long test);
size_t	uint_len(unsigned long long n, int basenum);
char	*convert(char *tstr, int num, char *bchain, unsigned long long test);
//GET_NEXT_LINE
char	*get_next_line(int fd);
char	*newline_found(char *str);
char	*ft_gnl_strjoin(char *s1, char *s2);
void	*ft_gnl_calloc(size_t count, size_t size);
#endif
