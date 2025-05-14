/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:01:03 by madel-va          #+#    #+#             */
/*   Updated: 2025/02/12 11:40:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*buffer;

	if (nmemb == 0 || size == 0)
		return (NULL);
	buffer = (char *)malloc(nmemb * size);
	if (!buffer)
		return (NULL);
	ft_bzero(buffer, size * nmemb);
	return (buffer);
}
/* || nmemb > SIZE_MAX/ size (Para eviar un overflow)*/
/*SIZE_MAX s el valor max que puede almacenar un size_t, para
comprobar que nmemb * size no lo supera*/