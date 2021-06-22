/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acami <acami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 17:19:48 by acami             #+#    #+#             */
/*   Updated: 2021/06/22 13:26:56 by acami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	write_err_msg(const char *errstr)
{
	fprintf(stderr, "\033[0;31m%s\033[0m\n", errstr);
}

void	panic(const char *errstr)
{
	write_err_msg(errstr);
	exit(EXIT_FAILURE);
}
