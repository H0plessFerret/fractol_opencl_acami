/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acami <acami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 17:24:16 by acami             #+#    #+#             */
/*   Updated: 2021/06/21 17:01:26 by acami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MESSAGES_H
# define ERROR_MESSAGES_H

# define	WINDOW_INIT_ERROR		"ERROR: A window can\'t be initialized"
# define	IMAGE_INIT_ERROR		"ERROR: An image can\'t be initialized"
# define	MALLOC_ERROR			"ERROR: Requested memory can\'t be allocated"

# define	OPENCL_INIT_ERROR		"ERROR: OpenCL can\'t be initialized"
# define	OPENCL_IDENT_ERROR		"ERROR: Platform can\'t be identified"
# define	OPENCL_DEVICE_ERROR		"ERROR: No devices can be found"
# define	OPENCL_FILENAME_ERROR	"ERROR: Kernel source file can\'t be found"
# define	OPENCL_BUILD_ERROR		"ERROR: Program source can\'t be built"
# define	OPENCL_MALLOC_ERROR		"ERROR: Requested opencl memory can\'t be allocated"
# define	OPENCL_COPY_ERROR		"ERROR: Copy process has failed"
# define	OPENCL_ARGS_ERROR		"ERROR: Args can\'t be passed to the kernel"

#endif