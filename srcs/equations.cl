__kernel void CalculateColour(int iteration,
							int max_iterations,
							int	curr_pixel,
							__global int *result)
{
	double	t;

	t = (double)iteration / max_iterations;
	result[curr_pixel] = 0x00000000 + (((int)(9 * (1 - t) * pow(t, 3) * 255) << 16) & 0xff0000)
		+ (((int)(15 * pow((1 - t), 2) * pow(t, 2) * 255) << 8) & 0xff00)
		+ ((int)(8.5 * pow((1 - t), 3) * t * 255) & 0xff);
}

__kernel void	mandelbrotOCL(__global double const *real,
							__global double const *imag,
							int height,
							int	width,
							int max_iterations,
							__global int *result,
							double extra_param_real,
							double extra_param_imag)
{
	// Get Parallel Index
	const int curr_line = get_global_id(0);
	int		curr_pos;
	double	x;
	double	y;
	double	xtemp;
	int		iteration;

	if (curr_line > height)
		return ;
	curr_pos = 0;
	while (curr_pos < width)
	{
		x = 0;
		y = 0;
		iteration = 0;
		while ((x * x + y * y <= 2 * 2) && iteration < max_iterations)
		{
			xtemp = x * x - y * y + real[curr_pos];
			y = 2. * x * y + imag[curr_line];
			x = xtemp;
			++iteration;
		}
		CalculateColour(iteration, max_iterations, curr_line * width + curr_pos, result);
		curr_pos++;
	}
}

__kernel void	burningShipOCL(__global double const *real,
							__global double const *imag,
							int height,
							int	width,
							int max_iterations,
							__global int *result,
							double extra_param_real,
							double extra_param_imag)
{
	// Get Parallel Index
	const int curr_line = get_global_id(0);
	int		curr_pos;
	double	x;
	double	y;
	double	xtemp;
	int		iteration;

	if (curr_line > height)
		return ;
	curr_pos = 0;
	while (curr_pos < width)
	{
		x = 0;
		y = 0;
		iteration = 0;
		while ((x * x + y * y <= 2 * 2) && iteration < max_iterations)
		{
			xtemp = x * x - y * y + real[curr_pos];
			y = -2. * fabs(x * y) + imag[curr_line];
			x = xtemp;
			++iteration;
		}
		CalculateColour(iteration, max_iterations, curr_line * width + curr_pos, result);
		curr_pos++;
	}
}

__kernel void	juliaOCL(__global double const *real,
						__global double const *imag,
						int height,
						int	width,
						int max_iterations,
						__global int *result,
						double extra_param_real,
						double extra_param_imag)
{
	// Get Parallel Index
	const int curr_line = get_global_id(0);
	int		curr_pos;
	double	x;
	double	y;
	double	xtemp;
	int		iteration;

	if (curr_line > height)
		return ;
	curr_pos = 0;
	while (curr_pos < width)
	{
		x = real[curr_pos];
		y = imag[curr_line];
		iteration = 0;
		while ((x * x + y * y <= 2 * 2) && iteration < max_iterations)
		{
			xtemp = x * x - y * y + extra_param_real;
			y = 2. * x * y + extra_param_imag;
			x = xtemp;
			++iteration;
		}
		CalculateColour(iteration, max_iterations, curr_line * width + curr_pos, result);
		curr_pos++;
	}
}

