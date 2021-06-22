__kernel void mandelbrotOCL(__global double const *real,
							__global double const *imag,
							int	width,
							int max_iterations,
							__global int *result)
{
	// Get Parallel Index
	unsigned int i = get_global_id(0);

	int		j;
	double	x;
	double	y;
	double	xtemp;
	int		iteration;
	int		colour;
	double	t;
	j = 0;
	y = 0;
	while (j < width)
	{
		x = 0;
		iteration = 0;
		y = 0;
		xtemp = 0;
		while ((x * x + y * y <= 2 * 2) && iteration < max_iterations)
		{
			xtemp = x * x - y * y + real[j];
			y = 2. * x * y + imag[i];
			x = xtemp;
			++iteration;
		}
		t = (double)iteration / max_iterations;
		result[i * width + j] = 0x00000000 + (((int)(9 * (1 - t) * pow(t, 3) * 255) << 16) & 0xff0000)
			+ (((int)(15 * pow((1 - t), 2) * pow(t, 2) * 255) << 8) & 0xff00)
			+ ((int)(8.5 * pow((1 - t), 3) * t * 255) & 0xff);
		j++;
	}
}
