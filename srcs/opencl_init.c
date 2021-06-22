/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acami <acami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 19:27:11 by acami             #+#    #+#             */
/*   Updated: 2021/06/21 17:10:46 by acami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// Identifies device type. GPU is prioritized over CPU
static cl_device_id	initDevice(void)
{
	cl_platform_id	platform;
	cl_device_id	dev_id;

	if (clGetPlatformIDs(1, &platform, NULL) < 0)
		panic(OPENCL_IDENT_ERROR);
	if (clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &dev_id, NULL)
		== CL_DEVICE_NOT_FOUND)
		if (clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &dev_id, NULL) < 0)
			panic(OPENCL_DEVICE_ERROR);
	return (dev_id);
}

static cl_program	initProgram(cl_context context,
const char *program_filename)
{
	cl_program	program;
	FILE		*program_handle;
	char		*program_buffer;
	size_t		program_size;
	int32_t		err_code;

	program_handle = fopen(program_filename, "r");
	if (program_handle == NULL)
		panic(OPENCL_FILENAME_ERROR);
	fseek(program_handle, 0, SEEK_END);
	program_size = ftell(program_handle);
	rewind(program_handle);
	program_buffer = xMalloc(program_size + 1);
	program_buffer[program_size] = '\0';
	fread(program_buffer, sizeof(char), program_size, program_handle);
	fclose(program_handle);
	program = clCreateProgramWithSource(context, 1,
			(const char **)&program_buffer, &program_size, &err_code);
	if (err_code != CL_SUCCESS)
		panic(OPENCL_BUILD_ERROR);
	free(program_buffer);
	return (program);
}

// Creates a special program file and compiles it
static cl_program	buildProgram(cl_context context, cl_device_id dev,
const char *program_filename)
{
	cl_program	program;
	char		*program_log;
	size_t		log_size;

	program = initProgram(context, program_filename);
	if (clBuildProgram(program, 0, NULL, NULL, NULL, NULL) < 0)
	{
		clGetProgramBuildInfo(program, dev, CL_PROGRAM_BUILD_LOG,
			0, NULL, &log_size);
		program_log = xMalloc(log_size + 1);
		program_log[log_size] = '\0';
		clGetProgramBuildInfo(program, dev, CL_PROGRAM_BUILD_LOG,
			log_size + 1, program_log, NULL);
		printf("%s\n", program_log);
		free(program_log);
		exit(EXIT_FAILURE);
	}
	return (program);
}

// Initializes opencl kernel
static cl_kernel	initKernel(cl_device_id device_id, cl_context context,
const char *func_name)
{
	cl_kernel	kernel;
	cl_program	program;
	int32_t		err_code;

	program = buildProgram(context, device_id, PROGRAM_FILE);
	kernel = clCreateKernel(program, func_name, &err_code);
	if (err_code != CL_SUCCESS)
		panic(OPENCL_INIT_ERROR);
	return (kernel);
}

void	initOpenCL(t_fractolOCL *fractolOCL)
{
	int32_t		err_code;

	fractolOCL->device_id = initDevice();
	fractolOCL->context = clCreateContext(NULL, 1, &(fractolOCL->device_id),
			NULL, NULL, &err_code);
	if (err_code != CL_SUCCESS)
		panic(OPENCL_INIT_ERROR);
	fractolOCL->queue = clCreateCommandQueue(fractolOCL->context,
			fractolOCL->device_id, 0, &err_code);
	if (err_code != CL_SUCCESS)
		panic(OPENCL_INIT_ERROR);
	fractolOCL->kernel = initKernel(fractolOCL->device_id, fractolOCL->context,
			fractolOCL->fractol->fractal_func);
	fractolOCL->real = clCreateBuffer(fractolOCL->context, CL_MEM_READ_ONLY,
			fractolOCL->fractol->width * sizeof(double), NULL, &err_code);
	fractolOCL->imaginary = clCreateBuffer(fractolOCL->context,
			CL_MEM_READ_ONLY, fractolOCL->fractol->height * sizeof(double),
			NULL, &err_code);
	fractolOCL->result = clCreateBuffer(fractolOCL->context, CL_MEM_WRITE_ONLY,
			fractolOCL->fractol->width * fractolOCL->fractol->height
			* sizeof(int32_t), NULL, &err_code);
	if (err_code != CL_SUCCESS)
		panic(MALLOC_ERROR);
}
