/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acami <acami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 15:24:37 by acami             #+#    #+#             */
/*   Updated: 2021/06/21 14:41:25 by acami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

bool	ft_strequ(const char *str1, const char *str2)
{
	size_t	count;

	count = 0;
	while (str1[count] != '\0' || str2[count] != '\0')
	{
		if (str1[count] != str2[count])
			return (false);
		++count;
	}
	if (str1[count] != str2[count])
		return (false);
	return (true);
}

void	*xMalloc(size_t bytes_to_allocate)
{
	void	*res;

	res = malloc(bytes_to_allocate);
	if (res == NULL)
		panic(MALLOC_ERROR);
	return (res);
}

void	setComplex(t_complex *number, double new_re, double new_im)
{
	number->real = new_re;
	number->imaginary = new_im;
}

void	putPixel(t_fractol *fractol, int32_t x, int32_t y, int32_t colour)
{
	char	*dst;

	dst = fractol->data_addr + (y * fractol->line_len + x * (fractol->bpp / 8));
	*(uint32_t *)dst = colour;
}
