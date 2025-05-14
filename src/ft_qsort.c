/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:46:49 by madel-va          #+#    #+#             */
/*   Updated: 2025/04/16 11:46:49 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_compar(const void *a, const void *b)
{
	int	x;
	int	y;

	x = *(const int *)a;
	y = *(const int *)b;
	while (1)
	{
		if (x < y)
			return (-1);
		if (x > y)
			return (1);
		break ;
	}
	return (0);
}

static size_t	ft_partition(t_partition_args *args, char *tmp)
{
	char	*p;
	char	*l;
	char	*r;

	p = args->base;
	l = (char *)args->base + args->size;
	r = (char *)args->base + (args->n - 1) * args->size;
	while (1)
	{
		while (l <= r && args->ft_compar(l, p) <= 0)
			l += args->size;
		while (l <= r && args->ft_compar(r, p) > 0)
			r -= args->size;
		if (l > r)
			break ;
		ft_memcpy(tmp, l, args->size);
		ft_memcpy(l, r, args->size);
		ft_memcpy(r, tmp, args->size);
		l += args->size;
		r -= args->size;
	}
	ft_memcpy(tmp, p, args->size);
	ft_memcpy(p, r, args->size);
	ft_memcpy(r, tmp, args->size);
	return ((r - (char *)args->base) / args->size);
}

void	ft_qsort(void *base, size_t n, size_t size,
		int (*ft_compar)(const void *, const void *))
{
	char				*tmp;
	size_t				left;
	t_partition_args	args;

	if (n < 2)
		return ;
	tmp = malloc(size);
	if (!tmp)
		return ;
	args.base = base;
	args.n = n;
	args.size = size;
	args.ft_compar = ft_compar;
	left = ft_partition(&args, tmp);
	ft_qsort(base, left, size, ft_compar);
	ft_qsort((char *)base + (left + 1) * size, n - left - 1, size, ft_compar);
	free(tmp);
}
