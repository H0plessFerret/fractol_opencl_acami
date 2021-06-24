/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acami <acami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 19:25:26 by acami             #+#    #+#             */
/*   Updated: 2021/06/24 15:17:02 by acami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	fillInputArrays(double **real, double **imaginary,
t_fractol *fractol)
{
	int32_t	count;

	*real = xMalloc(sizeof(double) * fractol->width);
	*imaginary = xMalloc(sizeof(double) * fractol->height);
	count = 0;
	while (count < fractol->width)
	{
		(*real)[count] = 1. * (fractol->re_max - fractol->re_min) * count
			/ fractol->width + fractol->re_min;
		++count;
	}
	count = 0;
	while (count < fractol->height)
	{
		(*imaginary)[count] = -1. * (fractol->im_max - fractol->im_min) * count
			/ fractol->width + fractol->im_max;
		++count;
	}
}

static void	enqueueBuffers(double *real, double *imaginary,
t_fractolOCL *fractolOCL)
{
	int32_t	err_code;

	err_code = clEnqueueWriteBuffer(fractolOCL->queue, fractolOCL->real,
			CL_TRUE, 0, sizeof(double) * fractolOCL->fractol->width, real,
			0, NULL, NULL);
	err_code |= clEnqueueWriteBuffer(fractolOCL->queue, fractolOCL->imaginary,
			CL_TRUE, 0, sizeof(double) * fractolOCL->fractol->height, imaginary,
			0, NULL, NULL);
	if (err_code != CL_SUCCESS)
		panic(OPENCL_COPY_ERROR);
}

static void	setKernelArgs(t_fractolOCL *fractolOCL)
{
	int32_t	err_code;

	err_code = clSetKernelArg(fractolOCL->kernel, 0, sizeof(cl_mem),
			&(fractolOCL->real));
	err_code |= clSetKernelArg(fractolOCL->kernel, 1, sizeof(cl_mem),
			&(fractolOCL->imaginary));
	err_code |= clSetKernelArg(fractolOCL->kernel, 2, sizeof(int32_t),
			&(fractolOCL->fractol->height));
	err_code |= clSetKernelArg(fractolOCL->kernel, 3, sizeof(int32_t),
			&(fractolOCL->fractol->width));
	err_code |= clSetKernelArg(fractolOCL->kernel, 4, sizeof(int32_t),
			&(fractolOCL->fractol->max_iterations));
	err_code |= clSetKernelArg(fractolOCL->kernel, 5, sizeof(cl_mem),
			&(fractolOCL->result));
	if (err_code != CL_SUCCESS)
		panic(OPENCL_COPY_ERROR);
}

void	fractolDraw(t_fractolOCL *fractolOCL)
{
	double	*real;
	double	*imaginary;
	int32_t	err_code;
	size_t	local_size;
	size_t	global_size;

	real = NULL;
	imaginary = NULL;
	fillInputArrays(&real, &imaginary, fractolOCL->fractol);
	enqueueBuffers(real, imaginary, fractolOCL);
	setKernelArgs(fractolOCL);
	local_size = WG_SIZE;
	global_size = ceil(fractolOCL->fractol->width / (double)local_size)
		* local_size;
	err_code = clEnqueueNDRangeKernel(fractolOCL->queue, fractolOCL->kernel,
			1, NULL, &global_size, &local_size, 0, NULL, NULL);
	clFinish(fractolOCL->queue);
	clEnqueueReadBuffer(fractolOCL->queue, fractolOCL->result, CL_TRUE, 0,
		fractolOCL->fractol->width * fractolOCL->fractol->height
		* sizeof(int32_t), fractolOCL->fractol->data_addr, 0, NULL, NULL);
	mlx_put_image_to_window(fractolOCL->fractol->mlx,
		fractolOCL->fractol->window, fractolOCL->fractol->img, 0, 0);
	free(real);
	free(imaginary);
}
