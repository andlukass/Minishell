/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:36:06 by llopes-d          #+#    #+#             */
/*   Updated: 2023/11/19 19:02:26 by llopes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*final;
	int		index;
	int		count;

	index = 0;
	count = 0;
	while (s[index])
	{
		if ((char)c == s[index])
		{
			final = ((char *)(&s[index]));
			count++;
		}
		index++;
	}
	if (count)
		return (final);
	if ((char)c == s[index])
		return ((char *)(&s[index]));
	else
		return (0);
}
