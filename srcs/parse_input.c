/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acami <acami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 14:27:35 by acami             #+#    #+#             */
/*   Updated: 2021/06/23 16:08:59 by acami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// Show possible inputs and quit
static void	xShowHelp(char *bad_param)
{
	char	*buffer_space;

	buffer_space = " ----- ";
	fprintf(stdout, "Error!\nBad input or unknown parameter: %s\n", bad_param);
	fprintf(stdout, "Usage: ./fractol [-W %d < WIDTH < 3841] \
		[-H %d < HEIGHT < 2161] <FRACTAL_NAME>\n",
		WORKGROUP_SIZE, WORKGROUP_SIZE);
	fprintf(stdout, "Fractals supported:\n");
	fprintf(stdout, "%sMandelbrot\n", buffer_space);
	fprintf(stdout, "%sJulia\n", buffer_space);
	fprintf(stdout, "%sBurningShip\n", buffer_space);
	exit(EXIT_FAILURE);
}

static t_fractalId	parseName(char *name)
{
	int					count;
	static const char	*names[FRACTALS_SUPPORTED] = {
		[Mandelbrot] = "Mandelbrot",
		[Julia] = "Julia",
		[BurningShip] = "Burning Ship"
	};

	count = 0;
	while (count < FRACTALS_SUPPORTED)
	{
		if (ft_strequ(names[count], name))
			return (count);
		++count;
	}
	return (Error);
}

static int32_t	parseParams(char **argv, t_fractol *fractol, int32_t curr_arg)
{
	int32_t	param_val;

	if (ft_strequ(argv[curr_arg], "-W"))
	{
		param_val = atoi(argv[curr_arg + 1]);
		if (param_val < WORKGROUP_SIZE || param_val > 3840)
			xShowHelp(argv[curr_arg + 1]);
		fractol->width = param_val;
		return (2);
	}
	if (ft_strequ(argv[curr_arg], "-H"))
	{
		param_val = atoi(argv[curr_arg + 1]);
		if (param_val < WORKGROUP_SIZE || param_val > 2160)
			xShowHelp(argv[curr_arg + 1]);
		fractol->height = param_val;
		return (2);
	}
	xShowHelp(argv[curr_arg]);
	return (-1);
}

t_fractalId	parseInput(int argc, char **argv, t_fractol *fractol)
{
	t_fractalId	res;
	int32_t		curr_arg;

	if (argc < 2)
		xShowHelp("Too few arguments");
	curr_arg = 1;
	fractol->width = WIN_WIDTH;
	fractol->height = WIN_HEIGHT;
	while (argv[curr_arg][0] == '-')
		curr_arg += parseParams(argv, fractol, curr_arg);
	res = parseName(argv[curr_arg]);
	if (res == Error || curr_arg + 1 < argc)
		xShowHelp(argv[curr_arg]);
	return (res);
}
