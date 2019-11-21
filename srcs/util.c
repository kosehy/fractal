/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 20:41:05 by sko               #+#    #+#             */
/*   Updated: 2019/10/15 20:41:07 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** initialize fractal parameter
** @param fractal
** @1 : Mandelbrot Set
** @2 : Julia Set
** @3 : ?
*/

void	fractal_init(t_fractal *fractal)
{
	fractal->fractal.xr = -3;
	fractal->fractal.yi = -2;
	fractal->fractal.scale = 200.00;
	fractal->fractal.iteration = 30;
	fractal->color.green = 0x22;
	fractal->color.blue = 0x32;
	fractal->color.red = 0x42;
	fractal->mouse.pos_x = W_WIDTH / 2;
	fractal->mouse.pos_y = W_HEIGHT / 2;
	if (fractal->fractal.type == 2 || fractal->fractal.type == 4 \
			|| fractal->fractal.type == 3) {
		fractal->fractal.xr = -2.10;
		fractal->mouse.state = 1;
		if (fractal->fractal.type == 2 || fractal->fractal.type == 4)
			fractal->fractal.iteration = 100;
		if (fractal->fractal.type == 3)
			fractal->fractal.iteration = 10;
	}
	if (fractal->fractal.type == 5)
	{
		fractal->fractal.xr = -2.20;
		fractal->fractal.yi = -1.60;
		fractal->fractal.iteration = 14;
	}
	display_manual(fractal);
}

/*
** Update the fractal image.
** @param fractal
*/

void	fractal_update(t_fractal *fractal)
{
	if (fractal->fractal.iteration <= 0)
		fractal->fractal.iteration = 0;
	fractal_pthread(fractal);
	mlx_string_put(fractal->mlx.init, fractal->mlx.win, 10, 5, 0XFFFFFF, \
                    ft_strjoin("# of iterations : ", \
                    ft_itoa(fractal->fractal.iteration)));
	mlx_string_put(fractal->mlx.init, fractal->mlx.win, 10, 35, 0XFFFFFF, \
                    ft_strjoin("Scale : ", \
                    ft_itoa((int) fractal->fractal.scale)));
}