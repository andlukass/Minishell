/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:36:06 by llopes-d          #+#    #+#             */
/*   Updated: 2023/12/08 14:53:26 by llopes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_length(long int i)
{
	int	length;

	length = 0;
	if (i == 0)
		return (1);
	if (i < 0)
	{
		i *= -1;
		length++;
	}
	while (i > 0)
	{
		i /= 10;
		length++;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			length;
	long int	nb;

	nb = n;
	length = get_length(nb);
	str = malloc(length * sizeof(char) + 1);
	if (str == NULL)
		return (NULL);
	if (nb == 0)
		str[0] = 0 + '0';
	str[length] = '\0';
	length--;
	if (nb < 0)
	{
		str[0] = '-';
		nb = nb * -1;
	}
	while (nb > 0)
	{
		str[length] = nb % 10 + 48;
		nb = nb / 10;
		length--;
	}
	return (str);
}
