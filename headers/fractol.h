/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acami <acami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 15:25:22 by acami             #+#    #+#             */
/*   Updated: 2021/06/24 14:58:13 by acami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define FRACTALS_SUPPORTED	3
# define WIN_WIDTH			1280
# define WIN_HEIGHT			1280

# define COLOURS_SUPPORTED	4

# define WG_SIZE			128

# include <stdlib.h>
# include <unistd.h>
# include <inttypes.h>
# include <stdbool.h>
# include <pthread.h>
# include "mlx.h"
# include "error_messages.h"
# include <OpenCL/cl.h>
# include <stdio.h>
# include <math.h>

# define PROGRAM_FILE		"./srcs/equations.cl"

typedef enum e_fractalId		t_fractalId;
typedef enum e_colourScheme		t_colourScheme;
typedef struct s_complex		t_complex;
typedef struct s_fractol		t_fractol;
typedef struct s_fractolOCL		t_fractolOCL;
typedef struct s_fractalInfo	t_fractalInfo;
typedef int32_t					(*t_handerAction)();
typedef void					(*t_keyAction)(int32_t key, t_fractol *fractol);
typedef void					(*t_buttonAction)(int32_t x, int32_t y,
								int32_t key, t_fractol *fractol);

enum e_fractalId
{
	Error = -1,
	Mandelbrot,
	Julia,
	BurningShip
};

enum e_colourScheme
{
	DefaultColour = 0,
	RandomAll,
	Drugs,
	RandomDrugs
};

struct s_complex
{
	double	real;
	double	imaginary;
};

struct s_fractalInfo
{
	double			re_min_start;
	double			re_max_start;
	double			im_min_start;
	double			im_max_start;
	const char		*fractal_func;
	int32_t			max_iterations_start;
	int32_t			iteration_change;
	t_complex		extra_param_start;
	t_colourScheme	colour_scheme_start;
};

struct s_fractol{
	void			*mlx;
	void			*window;
	int32_t			width;
	int32_t			height;
	void			*img;
	char			*data_addr;
	int32_t			bpp;
	int32_t			line_len;
	int32_t			endian;
	t_fractalId		fract_id;
	double			re_max;
	double			re_min;
	double			im_max;
	double			im_min;
	const char		*fractal_func;
	int32_t			max_iterations;
	int32_t			iteration_change;
	t_complex		extra_param;
	t_colourScheme	colour_scheme;
	bool			lmb_pressed;
};

struct s_fractolOCL
{
	t_fractol			*fractol;
	cl_kernel			kernel;
	cl_context			context;
	cl_device_id		device_id;
	cl_command_queue	queue;
	cl_mem				real;
	cl_mem				imaginary;
	cl_mem				result;
};

// Parse arguments of the program call and return the correct fractal_id
void	parseInput(int argc, char **argv, t_fractol *fractol);

// Initializes all things needed for OpenCL to run
void	initOpenCL(t_fractolOCL *fractolOCL);

// Draw the fractal currently held in memory using OpenCL
void	fractolDraw(t_fractolOCL *fractolOCL);

// Initializes default values for the fractol function
void	fractolFunctionInit(t_fractol *fractol);

// Initializes t_fractol struct
void	fractolOCLInit(t_fractolOCL *fractolOCL);

// Prints error message and exits the program
void	panic(const char *errstr);

// Returns true if strings are equal and false if they are not
bool	ft_strequ(const char *str1, const char *str2);

// Sets new values for a complex number
void	setComplex(t_complex *number, double new_re, double new_im);

// Puts a pixel of a certain colour into an image
void	putPixel(t_fractol *fractol, int32_t x, int32_t y,
			int32_t colour);

// Malloc wrapper with error handling
void	*xMalloc(uintmax_t bytes_to_allocate);

// ---------------------- EVENT  HANDLING ---------------------- //
// Closes window (both from ESC and pressing the button on the window)
void	closeWindow(int32_t key, t_fractol *fractol);

// Maps key presses to actions
void	keyPressHandler(int32_t key, t_fractolOCL *fractolOCL);

// Maps button presses to actions
void	buttonPressHandler(int32_t button, int x, int y,
			t_fractolOCL *fractolOCL);

// Maps button releases to actions
void	buttonReleaseHandler(int32_t button, int x, int y,
			t_fractolOCL *fractolOCL);

// Handles mouse movements
void	motionHandler(int32_t x, int32_t y, t_fractolOCL *fractolOCL);

// Translates fractal x_shift to the right and im_shift up
void	translateFractal(int32_t key, t_fractol *fractol);

// Reset fractal to default values
void	resetFractal(int32_t key, t_fractol *fractol);

// Redraws fractal
void	updateFractal(int32_t key, t_fractol *fractol);

// Changes max_iteration param in fractol
void	changeIterations(int32_t key, t_fractol *fractol);

// Changes colour_scheme param in fractol
void	changeColour(int32_t key, t_fractol *fractol);

// Zooms in on the point (x, y) with the zoom factor factor
void	zoomFractal(int32_t x, int32_t y, int32_t button,
			t_fractol *fractol);

// Changes parameter for Julia-type of fractals according to the mouse position
void	changeParam(int32_t x, int32_t y, int32_t button,
			t_fractol *fractol);

#endif