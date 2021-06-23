__kernel void mandelbrotOCLa(__global double const *real,
							__global double const *imag,
							int	width,
							int max_iterations,
							__global int *result)
{
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
__kernel void mandelbrotOCL(__global int const *lines,
							int width,
							int height,
							double re_min,
							double re_max,
							double im_min,
							double im_max,
							int max_iterations,
							int	colour_scheme,
							__global int *result)
{
	const int	index = get_global_id(0);
	int			curr_line, end_line;
	int			curr_pos;
	int			iteration;
	double		c_real, c_imag;
	double		curr_real, curr_imag, temp_real;
	double		step_real, step_imag;
	double		t;

	curr_line = lines[index];
	end_line = lines[index + 1];
	step_real = (re_max - re_min) / width;
	step_imag = (im_max - im_min) / height;
	c_imag = curr_line * step_imag + im_min;
	while (curr_line < end_line)
	{
		curr_pos = 0;
		c_real = re_min;
		while (curr_pos < width)
		{
			//printf("%lf --- %lf\n", c_imag, c_real);
			iteration = 0;
			curr_real = 0;
			curr_imag = 0;
			while ((curr_real * curr_real + curr_imag * curr_imag <= 4) && iteration < max_iterations)
			{
				temp_real = curr_real * curr_real - curr_imag * curr_imag + c_real;
				curr_imag = 2. * curr_real * curr_imag + c_imag;
				curr_real = temp_real;
				++iteration;
			}
			t = (double)iteration / max_iterations;
			result[curr_line * width + curr_pos] = 0x00000000 + (((int)(9 * (1 - t) * pow(t, 3) * 255) << 16) & 0xff0000)
			+ (((int)(15 * pow((1 - t), 2) * pow(t, 2) * 255) << 8) & 0xff00)
			+ ((int)(8.5 * pow((1 - t), 3) * t * 255) & 0xff);
			++curr_pos;
			c_real += step_real;
		}
		++curr_line;
		c_imag += step_imag;
	}
/*
	double		imag_max;
	double		c_real, c_imag;
	double		curr_real, curr_imag;
	double		temp_real;
	int			iteration = 0;

	//printf("%lf --- %d --- %lf\n", imag_borders[0], index, imag_borders[index]);
	c_imag = imag_borders[index];
	imag_max = imag_borders[index + 1];
	while (c_imag < imag_max)
	{
		c_real = re_min;
		while (c_real < re_max)
		{
			iteration = 0;
			while ((curr_real * curr_real + curr_imag * curr_imag <= 4) && iteration < max_iterations)
			{
				temp_real = curr_real * curr_real + curr_imag * curr_imag + c_real;
				curr_imag = 2. * curr_real * curr_imag + c_imag;
				curr_real = temp_real;
				++iteration;
			}
			c_real += step[0];
		}
		c_imag += step[1];
	}
	*/
}