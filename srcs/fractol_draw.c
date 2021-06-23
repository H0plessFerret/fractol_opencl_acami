/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acami <acami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 19:25:26 by acami             #+#    #+#             */
/*   Updated: 2021/06/22 16:26:27 by acami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	prepareInputArrays(t_fractolOCL *fractolOCL)
{
	int32_t	*lines;
	int32_t	count;
	int32_t	err_code;

	lines = xMalloc((WORKGROUP_SIZE + 1) * sizeof(double));
	count = 0;
	while (count < WORKGROUP_SIZE + 1)
	{
		lines[count] = count * fractolOCL->fractol->height / WORKGROUP_SIZE;
		++count;
	}
	err_code = clEnqueueWriteBuffer(fractolOCL->queue,
			fractolOCL->lines, CL_TRUE, 0, (WORKGROUP_SIZE + 1)
			* sizeof(double), lines, 0, NULL, NULL);
	if (err_code != CL_SUCCESS)
		panic(OPENCL_COPY_ERROR);
	free(lines);
}

void	fractolDraw(t_fractolOCL *fractolOCL)
{
	int32_t	err_code;
	size_t	local_size;
	size_t	global_size;

	prepareInputArrays(fractolOCL);
	// Pass params to the kernel
	err_code = clSetKernelArg(fractolOCL->kernel, 0, sizeof(cl_mem), &(fractolOCL->lines));
	err_code |= clSetKernelArg(fractolOCL->kernel, 1, sizeof(int32_t), &(fractolOCL->fractol->width));
	err_code |= clSetKernelArg(fractolOCL->kernel, 2, sizeof(int32_t), &(fractolOCL->fractol->height));
	err_code |= clSetKernelArg(fractolOCL->kernel, 3, sizeof(double), &(fractolOCL->fractol->re_min));
	err_code |= clSetKernelArg(fractolOCL->kernel, 4, sizeof(double), &(fractolOCL->fractol->re_max));
	err_code |= clSetKernelArg(fractolOCL->kernel, 5, sizeof(double), &(fractolOCL->fractol->im_min));
	err_code |= clSetKernelArg(fractolOCL->kernel, 6, sizeof(double), &(fractolOCL->fractol->im_max));
	err_code |= clSetKernelArg(fractolOCL->kernel, 7, sizeof(int32_t), &(fractolOCL->fractol->max_iterations));
	err_code |= clSetKernelArg(fractolOCL->kernel, 8, sizeof(int32_t), &(fractolOCL->fractol->colour_scheme));
	err_code |= clSetKernelArg(fractolOCL->kernel, 9, sizeof(cl_mem), &(fractolOCL->result));

	if (err_code != CL_SUCCESS)
		panic(OPENCL_COPY_ERROR);
	// some fucking magic, i don't get what that is ngl
	local_size = WORKGROUP_SIZE;
	global_size = local_size;
	// Make kernel go brrrrrrrr
	err_code = clEnqueueNDRangeKernel(fractolOCL->queue, fractolOCL->kernel, 1, NULL, &global_size, &local_size, 0, NULL, NULL);
	// Wait for all threads to be done
	clFinish(fractolOCL->queue);
	// Read info and put the image into the window
	clEnqueueReadBuffer(fractolOCL->queue, fractolOCL->result, CL_TRUE, 0, sizeof(int32_t) * fractolOCL->fractol->width * fractolOCL->fractol->height, fractolOCL->fractol->data_addr, 0, NULL, NULL);
	mlx_put_image_to_window(fractolOCL->fractol->mlx, fractolOCL->fractol->window, fractolOCL->fractol->img, 0, 0);
}
