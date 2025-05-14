/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:47:29 by madel-va          #+#    #+#             */
/*   Updated: 2025/02/12 11:40:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_atoi(const char *str)
{
	long long	value;
	int			sign;

	sign = 1;
	value = 0;
	while ((*str == ' ') || (*str == '\f') || (*str == '\n') || (*str == '\r')
		|| (*str == '\t') || (*str == '\v'))
		str++;
	if (*str == '-')
		sign *= -1;
	if ((*str == '+') || (*str == '-'))
		str++;
	while (ft_isdigit(*str))
	{
		value = value * 10 + (*str - '0');
		str++;
	}
	value = value * sign;
	return (value);
}
