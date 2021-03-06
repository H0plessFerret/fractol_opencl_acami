/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acami <acami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 14:48:01 by acami             #+#    #+#             */
/*   Updated: 2021/06/24 16:51:54 by acami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	closeWindow(int32_t key, t_fractol *fractol)
{
	(void)key;
	(void)fractol;
	exit(0);
}

void	resetFractal(int32_t key, t_fractol *fractol)
{
	(void)key;
	fractolFunctionInit(fractol);
}

void	updateFractal(int32_t key, t_fractol *fractol)
{
	(void)key;
	(void)fractol;
}

void	changeParam(int32_t x, int32_t y, int32_t button, t_fractol *fractol)
{
	(void)button;
	fractol->lmb_pressed = true;
	if (x < 0 || y < 0 || x > fractol->width || y >fractol->height)
		setComplex(&(fractol->extra_param),
			(double)x * (fractol->re_max - fractol->re_min) / fractol->width
			+ fractol->re_min,
			(double)y * -1. * (fractol->im_max - fractol->im_min)
			/ fractol->height + fractol->im_max);
}
