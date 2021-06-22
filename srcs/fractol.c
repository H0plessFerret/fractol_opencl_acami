/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acami <acami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 13:47:44 by acami             #+#    #+#             */
/*   Updated: 2021/06/21 17:36:15 by acami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_fractolOCL		fractolOCL;
	t_fractol			fractol;

	fractol.fract_id = parseInput(argc, argv, &fractol);
	fractolOCL.fractol = &fractol;
	fractolOCLInit(&fractolOCL);
	initOpenCL(&fractolOCL);
	fractolDraw(&fractolOCL);
	mlx_loop(fractol.mlx);
	return (0);
}
