/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acami <acami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 18:57:28 by acami             #+#    #+#             */
/*   Updated: 2021/06/22 14:49:06 by acami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int32_t	closeWindow(void)
{
	exit(EXIT_SUCCESS);
}

int32_t	translateFractal(double re_shift, double im_shift,
t_fractolOCL *fractolOCL)
{
	fractolOCL->fractol->re_min += re_shift;
	fractolOCL->fractol->re_max += re_shift;
	fractolOCL->fractol->im_max += im_shift;
	fractolOCL->fractol->im_min += im_shift;
	fractolDraw(fractolOCL);
	return (0);
}

static double	interpolate(double start, double end, double interpolation)
{
	return (start + ((end - start) * interpolation));
}

int32_t	zoomFractal(int32_t x, int32_t y, double factor,
t_fractolOCL *fractolOCL)
{
	t_complex	mouse_pos;
	double		interpolation;
	t_fractol	*fractol;

	fractol = fractolOCL->fractol;
	setComplex(&(mouse_pos),
		(double)x * (fractol->re_max - fractol->re_min) / fractol->width
		+ fractol->re_min,
		(double)y * -1. * (fractol->im_max - fractol->im_min)
		/ fractol->height + fractol->im_max);
	interpolation = 1.0 / factor;
	fractol->re_min = interpolate(mouse_pos.real, fractol->re_min,
			interpolation);
	fractol->re_max = interpolate(mouse_pos.real, fractol->re_max,
			interpolation);
	fractol->im_min = interpolate(mouse_pos.imaginary, fractol->im_min,
			interpolation);
	fractol->im_max = interpolate(mouse_pos.imaginary, fractol->im_max,
			interpolation);
	fractolDraw(fractolOCL);
	return (0);
}
