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

/*md
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
	fractal->fractal.scale = 300.00;
	fractal->fractal.iteration = 30;
	fractal->color.green = 0x22;
	fractal->color.blue = 0x32;
	fractal->color.red = 0x42;
	fractal->mouse.pos_x = W_WIDTH / 2;
	fractal->mouse.pos_y = W_HEIGHT / 2;
	fractal->manual_color = 0XFFFFFF;
	fractal->cp.zr = 0.0;
	fractal->cp.zi = 0.0;
	fractal->cp.cr = 0.0;
	fractal->cp.ci = 0.0;
	fractal->cp.a = 0.0;
	fractal->cp.b = 0.0;
}

/*md
** Update the fractal image.
** @param fractal
*/

void	fractal_update(t_fractal *fractal)
{
	int		x;

	x = 10;
	if (fractal->fractal.iteration <= 0)
		fractal->fractal.iteration = 0;
	fractal_pthread(fractal);
	mlx_string_put(fractal->mlx.init, fractal->mlx.win, x, 5,\
	fractal->manual_color, ft_strjoin("# of iterations : ", \
	ft_itoa(fractal->fractal.iteration)));
	mlx_string_put(fractal->mlx.init, fractal->mlx.win, x, 35,\
	fractal->manual_color, ft_strjoin("Scale : ", \
	ft_itoa((int) fractal->fractal.scale)));
	mlx_string_put(fractal->mlx.init, fractal->mlx.win, x, 65,\
	fractal->manual_color, "[ESC]                       exit fdf program");
	mlx_string_put(fractal->mlx.init, fractal->mlx.win, x, 95,\
	fractal->manual_color, "[Key |I|O|]                 Change iteration");
}

/*md
** fractal manipulate
** @param x
** @param y
** @param fractal
** @return
*/

int		fractal_manipulate(int x, int y, t_fractal *fractal)
{
	if (fractal->mouse.state == 1 && (x > 0 && y > 0) \
			&& (x < W_WIDTH && y < W_HEIGHT))
	{
		fractal->mouse.pos_x = x;
		fractal->mouse.pos_y = y;
		fractal_update(fractal);
	}
	return (0);
}

int		fractal_mouse(int mc, int x, int y, t_fractal *fractal)
{
	if (x > 0 && y > 0 && x < W_WIDTH && y < W_HEIGHT)
	{
		if (mc == MOUSE_LEFT_CLICK)
		{
			if (fractal->mouse.state == 1)
				fractal->mouse.state = 0;
			else
				fractal->mouse.state = 1;
		}
	}
	return (0);
}

