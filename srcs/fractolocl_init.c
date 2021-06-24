/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractolocl_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acami <acami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 17:06:02 by acami             #+#    #+#             */
/*   Updated: 2021/06/24 14:58:22 by acami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "key_codes.h"

static void	fractolHooksInit(t_fractolOCL *fractolOCL)
{
	mlx_hook(fractolOCL->fractol->window, DESTROYNOTIFY, NOEVENTMASK,
		(int (*)())closeWindow, NULL);
	mlx_hook(fractolOCL->fractol->window, KEYPRESS, NOEVENTMASK,
		(int (*)())keyPressHandler, fractolOCL);
	mlx_hook(fractolOCL->fractol->window, BUTTONPRESS, NOEVENTMASK,
		(int (*)())buttonPressHandler, fractolOCL);
	mlx_hook(fractolOCL->fractol->window, BUTTONRELEASE, NOEVENTMASK,
		(int (*)())buttonReleaseHandler, fractolOCL);
	mlx_hook(fractolOCL->fractol->window, MOTIONNOTIFY, NOEVENTMASK,
		(int (*)())motionHandler, fractolOCL);
}

void	fractolOCLInit(t_fractolOCL *fractolOCL)
{
	t_fractol	*fractol;

	fractol = fractolOCL->fractol;
	fractol->mlx = mlx_init();
	fractol->window = mlx_new_window(fractol->mlx, fractol->width,
			fractol->height, "Fract-ol");
	if (fractol->window == NULL)
		panic(WINDOW_INIT_ERROR);
	fractol->img = mlx_new_image(fractol->mlx, fractol->width,
			fractol->height);
	if (fractol->img == NULL)
		panic(IMAGE_INIT_ERROR);
	fractol->data_addr = mlx_get_data_addr(fractol->img,
			&(fractol->bpp), &(fractol->line_len),
			&(fractol->endian));
	fractol->lmb_pressed = false;
	fractolFunctionInit(fractolOCL->fractol);
	fractolHooksInit(fractolOCL);
}

void	fractolFunctionInit(t_fractol *fractol)
{
	static const t_fractalInfo	frac_info[FRACTALS_SUPPORTED] = {
		[Mandelbrot] = {-2., 1., -1.5, 1.5, "mandelbrotOCL", 50, 7, {0., 0.},
			DefaultColour},
		[Julia] = {-2., 2., -2., 2., "juliaOCL", 50, 6, {-0.89, -0.235000},
			DefaultColour},
		[BurningShip] = {-2., 1., -1., 2., "burningShipOCL", 50, 7, {0., 0.},
			DefaultColour}
	};
	t_fractalId					curr_id;

	curr_id = (fractol->fract_id) % FRACTALS_SUPPORTED;
	fractol->re_min = frac_info[curr_id].re_min_start;
	fractol->re_max = frac_info[curr_id].re_max_start;
	fractol->im_min = frac_info[curr_id].im_min_start;
	fractol->im_max = frac_info[curr_id].im_max_start;
	fractol->fractal_func = frac_info[curr_id].fractal_func;
	fractol->max_iterations = frac_info[curr_id].max_iterations_start;
	fractol->iteration_change = frac_info[curr_id].iteration_change;
	fractol->extra_param = frac_info[curr_id].extra_param_start;
	fractol->colour_scheme = frac_info[curr_id].colour_scheme_start;
}
