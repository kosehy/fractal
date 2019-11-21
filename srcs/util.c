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

#include "fdf.h"

/*
**	free the double string pointer.
*/

void	free_2d_str(char **nums)
{
	int		len;

	len = 0;
	while (nums[len])
	{
		free(nums[len]);
		++len;
	}
	free(nums);
}

void	display_manual(t_fdf *fdf)
{
	int		x;

	x = 0;
	mlx_string_put(fdf->mlx.init, fdf->mlx.win, x, 0, fdf->map.man_color,\
	"[ESC]                     exit fdf program");
	mlx_string_put(fdf->mlx.init, fdf->mlx.win, x, 20, fdf->map.man_color,\
	"[Key |W|S|A|D|]           move up/down/left/right by 1 pixel");
	mlx_string_put(fdf->mlx.init, fdf->mlx.win, x, 40, fdf->map.man_color,\
	"[Key |Q|E|]               zoom in/out");
	mlx_string_put(fdf->mlx.init, fdf->mlx.win, x, 60, fdf->map.man_color,\
	"[Key |R|]                 Reset the map");
	mlx_string_put(fdf->mlx.init, fdf->mlx.win, x, 80, fdf->map.man_color,\
	"[Key |X|]                 Random Colorization!");
	mlx_string_put(fdf->mlx.init, fdf->mlx.win, x, 100, fdf->map.man_color,\
	"[Mouse Wheel up/down      Increase/Decrease the Z value");
	mlx_string_put(fdf->mlx.init, fdf->mlx.win, x, 120, fdf->map.man_color,\
	"[Key |V|]                 random color manual");
	mlx_string_put(fdf->mlx.init, fdf->mlx.win, x, 140, fdf->map.man_color,\
	"[Key |Space|]             chane the camera view isometric <-> plain");
}

/*
** Colorize the manual with a random color.
*/

void	random_color_letter(t_fdf *fdf)
{
	fdf->map.man_color = (rand() % 0xFFFFFF);
}

/*
** initialize fractal parameter
** @param fractal
** @1 : Mandelbrot Set
** @2 : Julia Set
** @3 : ?
*/

void	fractal_init(t_fractal *fractal)
{
	fractal->fractal.xr = -2.60;
	fractal->fractal.yi = -1.20;
	fractal->fractal.scale = 300.00;
	fractal->fractal.iteration = 42;
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
                    ft_itoa((int) fractal->fractal.scale)));
}