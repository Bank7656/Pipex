/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 10:55:15 by thacharo          #+#    #+#             */
/*   Updated: 2024/09/04 19:21:48 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	power(int n, int pow)
{
	int	i;
	int	number;

	i = 0;
	number = 1;
	while (i < pow)
	{
		number = number * n;
		i++;
	}
	return (number);
}

int	find_num_len(int n)
{
	int	len;

	len = 0;
	if (n == -2147483648)
		return (11);
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = n * (-1);
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

// 12345 / 10000 -> 1     | 1 % 10 -> 1
// 12345 / 1000 -> 12	  | 12 % 10 -> 2
// 12345 / 100 -> 123	  | 123 % 10 -> 3
// 1234 / 10 -> 1234	  | 1234 % 10 -> 4
// 12345 / 1 - > 12345    | 12345 % 10 -> 5

void	convert(char *arr, int n, int len)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		arr[i] = '-';
		i++;
		if (n == -2147483648)
		{
			arr[i] = '2';
			i++;
			n = -147483648;
		}
		n = n * (-1);
	}
	while (i < len)
	{
		arr[i] = ((n / power(10, len - 1 - i)) % 10) + 48;
		i++;
	}
	arr[i] = '\0';
}

char	*ft_itoa(int n)
{
	int		len;
	char	*number;

	len = find_num_len(n);
	number = (char *)malloc(sizeof(char) * (len + 1));
	if (number == NULL)
		return (NULL);
	convert(number, n, len);
	return (number);
}

// void	test_find_num_len(void)
// {
// 	printf("%d\n", find_num_len(0));
// 	printf("%d\n", find_num_len(12345));
// 	printf("%d\n", find_num_len(-12345));
// 	printf("%d\n", find_num_len(123456789));
// 	printf("%d\n", find_num_len(-123456789));
// 	printf("%d\n", find_num_len(INT_MAX));
// 	printf("%d\n", find_num_len(INT_MIN));
// }

// void	test_power(void)
// {
// 	printf("%d\n", power(5, 2));
// 	printf("%d\n", power(10, 6));
// 	printf("%d\n", power(0, 1));
// 	printf("%d\n", power(1, 0));
// 	printf("%d\n", power(0, 0));
// }

// int	main(void)
// {
// 	//test_find_num_len();
// 	//test_power();
// 	char	*num1;
// 	char	*num2;
// 	char	*num3;
// 	char	*num4;
// 	char	*num5;
// 	char	*num6;
// 	char	*num7;

// 	num1 = ft_itoa(0);
// 	num2 = ft_itoa(12345);
// 	num3 = ft_itoa(-12345);
// 	num4 = ft_itoa(123456789);
// 	num5 = ft_itoa(-123456789);
// 	num6 = ft_itoa(INT_MIN);
// 	num7 = ft_itoa(INT_MAX);

// 	printf("%s\n", num1);
// 	printf("%s\n", num2);
// 	printf("%s\n", num3);
// 	printf("%s\n", num4);
// 	printf("%s\n", num5);
// 	printf("%s\n", num6);
// 	printf("%s\n", num7);

// 	free(num1);
// 	free(num2);
// 	free(num3);
// 	free(num4);
// 	free(num5);
// 	free(num6);
// 	free(num7);
// 	return (0);
// }
