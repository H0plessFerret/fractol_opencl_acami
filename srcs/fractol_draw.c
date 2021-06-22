/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acami <acami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 19:25:26 by acami             #+#    #+#             */
/*   Updated: 2021/06/21 19:46:50 by acami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	fractolDraw(t_fractolOCL *fractolOCL)
{
	double	*real;
	double	*imaginary;
	int32_t	count;
	int32_t	err_code;
	size_t	local_size;
	size_t	global_size;

	real = xMalloc(sizeof(double) * fractolOCL->fractol->width);
	imaginary = xMalloc(sizeof(double) * fractolOCL->fractol->height);
	count = 0;
	while (count < fractolOCL->fractol->width)
	{
		real[count] = 1. * (fractolOCL->fractol->re_max - fractolOCL->fractol->re_min) * count / fractolOCL->fractol->width
			+ fractolOCL->fractol->re_min;
		++count;
	}
	count = 0;
	while (count < fractolOCL->fractol->height)
	{
		imaginary[count] = -1. * (fractolOCL->fractol->im_max - fractolOCL->fractol->im_min) * count / fractolOCL->fractol->width
			+ fractolOCL->fractol->im_max;
		++count;
	}
	err_code = clEnqueueWriteBuffer(fractolOCL->queue, fractolOCL->real,
			CL_TRUE, 0, sizeof(double) * fractolOCL->fractol->width, real,
			0, NULL, NULL);
	err_code |= clEnqueueWriteBuffer(fractolOCL->queue, fractolOCL->imaginary,
			CL_TRUE, 0, sizeof(double) * fractolOCL->fractol->height, imaginary,
			0, NULL, NULL);
	if (err_code != CL_SUCCESS)
		panic(OPENCL_COPY_ERROR);
	err_code = clSetKernelArg(fractolOCL->kernel, 0, sizeof(cl_mem), &(fractolOCL->real));
	err_code |= clSetKernelArg(fractolOCL->kernel, 1, sizeof(cl_mem), &(fractolOCL->imaginary));
	err_code |= clSetKernelArg(fractolOCL->kernel, 2, sizeof(int32_t), &(fractolOCL->fractol->width));
	err_code |= clSetKernelArg(fractolOCL->kernel, 3, sizeof(int32_t), &(fractolOCL->fractol->max_iterations));
	err_code |= clSetKernelArg(fractolOCL->kernel, 4, sizeof(cl_mem), &(fractolOCL->result));
	if (err_code != CL_SUCCESS)
		panic(OPENCL_COPY_ERROR);
	local_size = WG_SIZE;
	global_size = ceil(fractolOCL->fractol->width / (double)local_size) * local_size;
	err_code = clEnqueueNDRangeKernel(fractolOCL->queue, fractolOCL->kernel, 1, NULL, &global_size, &local_size, 0, NULL, NULL);
	clFinish(fractolOCL->queue);
	clEnqueueReadBuffer(fractolOCL->queue, fractolOCL->result, CL_TRUE, 0, sizeof(int32_t) * fractolOCL->fractol->width * fractolOCL->fractol->height, fractolOCL->fractol->data_addr, 0, NULL, NULL);
	mlx_put_image_to_window(fractolOCL->fractol->mlx, fractolOCL->fractol->window, fractolOCL->fractol->img, 0, 0);
	free(real);
	free(imaginary);
}
