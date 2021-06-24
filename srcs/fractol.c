/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acami <acami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 13:47:44 by acami             #+#    #+#             */
/*   Updated: 2021/06/24 14:56:51 by acami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_fractolOCL		fractolOCL;
	t_fractol			fractol;

	parseInput(argc, argv, &fractol);
	fractolOCL.fractol = &fractol;
	fractolOCLInit(&fractolOCL);
	initOpenCL(&fractolOCL);
	fractolDraw(&fractolOCL);
	mlx_loop(fractol.mlx);
	return (0);
}
