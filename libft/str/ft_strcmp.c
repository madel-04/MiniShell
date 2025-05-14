/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:52:06 by madel-va          #+#    #+#             */
/*   Updated: 2025/04/09 18:06:33 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	if ((s1[i] == '\0' && s2[i] == '\0'))
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n && s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	if (i == n)
		return (0);
	if (i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	else
		return (0);
}
/*
int	main(void)
{
	printf("%d", ft_strncmp("Hello", "Hello1", 8));
	printf("\n%d", ft_strncmp("Hello", "He", 8));
	printf("\n%d", ft_strncmp("He", "Hello", 8));
	printf("\n%d", ft_strncmp("Hello", "Hello", 8));
}
*/
