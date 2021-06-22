/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acami <acami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 18:55:00 by acami             #+#    #+#             */
/*   Updated: 2021/06/21 17:41:01 by acami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "key_codes.h"

// Need to find a way to get rid of this ugly if else mountain :c
int32_t	keyPressHandler(int32_t key, t_fractolOCL *fractolOCL)
{
	t_fractol	*fractol;

	fractol = fractolOCL->fractol;
	if (key == KEYBOARD_ESC)
		closeWindow();
	if (key == KEYBOARD_A)
		translateFractal(-(fractol->re_max - fractol->re_min) / 128., 0.,
			fractolOCL);
	else if (key == KEYBOARD_S)
		translateFractal(0., -(fractol->im_max - fractol->im_min) / 128.,
			fractolOCL);
	else if (key == KEYBOARD_D)
		translateFractal((fractol->re_max - fractol->re_min) / 128., 0.,
			fractolOCL);
	else if (key == KEYBOARD_W)
		translateFractal(0., (fractol->im_max - fractol->im_min) / 128.,
			fractolOCL);
	else if (key == KEYBOARD_R)
	{
		fractolFunctionInit(fractolOCL);
		fractolDraw(fractolOCL);
	}
	else if (key == KEYBOARD_PLUS)
	{
		fractol->max_iterations = fractol->max_iterations * 14 / 10;
		fractolDraw(fractolOCL);
	}
	else if (key == KEYBOARD_MINUS)
	{
		fractolOCL->fractol->max_iterations = fractol->max_iterations * 10 / 14;
		fractolDraw(fractolOCL);
	}
	else if (key == KEYBOARD_UP)
	{
		fractol->colour_scheme = (fractol->colour_scheme
				+ 1) % COLOURS_SUPPORTED;
		fractolDraw(fractolOCL);
	}
	else if (key == KEYBOARD_DOWN)
	{
		fractol->colour_scheme = (fractol->colour_scheme
				+ COLOURS_SUPPORTED - 1) % COLOURS_SUPPORTED;
		fractolDraw(fractolOCL);
	}
	else if (key == KEYBOARD_Q)
		fractolDraw(fractolOCL);
	return (0);
}

int32_t	buttonPressHandler(int32_t button, int x, int y,
t_fractolOCL *fractolOCL)
{
	t_fractol	*fractol;

	fractol = fractolOCL->fractol;
	if (button == M_LMB)
	{
		fractol->lmb_pressed = true;
		setComplex(&(fractol->extra_param),
			(double)x * (fractol->re_max - fractol->re_min) / fractol->width
			+ fractol->re_min,
			(double)y * -1. * (fractol->im_max - fractol->im_min)
			/ fractol->height + fractol->im_max);
		fractolDraw(fractolOCL);
	}
	else if (button == M_SCROLL_UP)
	{
		fractol->max_iterations -= fractol->iteration_change;
		zoomFractal(x, y, 0.8, fractolOCL);
	}
	else if (button == M_SCROLL_DOWN)
	{
		fractol->max_iterations += fractol->iteration_change;
		zoomFractal(x, y, 1.2, fractolOCL);
	}
	return (0);
}

int32_t	buttonReleaseHandler(int32_t button, int x, int y,
t_fractolOCL *fractolOCL)
{
	(void)x;
	(void)y;
	if (button == M_LMB)
		fractolOCL->fractol->lmb_pressed = false;
	return (0);
}

int32_t	motionHandler(int32_t x, int32_t y, t_fractolOCL *fractolOCL)
{
	t_fractol	*fractol;

	fractol = fractolOCL->fractol;
	if (fractol->lmb_pressed)
	{
		setComplex(&(fractol->extra_param),
			(double)x * (fractol->re_max - fractol->re_min) / fractol->width
			+ fractol->re_min,
			(double)y * -1. * (fractol->im_max - fractol->im_min)
			/ fractol->height + fractol->im_max);
		fractolDraw(fractolOCL);
	}
	return (0);
}