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

#include "fractal.h"

/*
** initialize fractal parameter
** @param fractal
** @1 : Mandelbrot Set
** @2 : Julia Set
** @3 : sphere Set
*/

void			fractal_init(t_fractal *fractal)
{
	fractal->fractal.xr = -2.60;
	fractal->fractal.yi = -2.20;
	fractal->fractal.scale = 300.00;
	fractal->fractal.iteration = 42;
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
	fractal->mouse.state = 1;
	if (fractal->fractal.type == 2)
	{
		fractal->fractal.xr = -2.10;
		fractal->fractal.iteration = 100;
	}
}

/*
** get mouse position
** @param x
** @param y
** @param fractal
** @return
*/

int				follow_by_mouse(int x, int y, t_fractal *fractal)
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

/*
** fractal zoom in control
** @param x
** @param y
** @param f
*/

static void		zoom_in(int x, int y, t_fractal *f)
{
	if (f->fractal.scale >= MAX_ZOOM)
	{
		f->fractal.scale = MAX_ZOOM;
		return ;
	}
	if (f->mouse.state == 1)
	{
		f->mouse.pos_x = x;
		f->mouse.pos_y = y;
	}
	f->fractal.xr = (x / f->fractal.scale + f->fractal.xr) - \
					((f->fractal.scale * PRECISION) / 2);
	f->fractal.xr += ((f->fractal.scale * PRECISION) / 2) - \
					(x / (f->fractal.scale * PRECISION));
	f->fractal.yi = (y / f->fractal.scale + f->fractal.yi) - \
					((f->fractal.scale * PRECISION) / 2);
	f->fractal.yi += ((f->fractal.scale * PRECISION) / 2) - \
					(y / (f->fractal.scale * PRECISION));
	f->fractal.scale *= PRECISION;
	f->fractal.iteration += 1;
}

/*
** fractal zoom out control
** @param f
*/

static void		zoom_out(t_fractal *f)
{
	f->fractal.xr = (f->mouse.pos_x / f->fractal.scale + f->fractal.xr) - \
					((f->fractal.scale / PRECISION) / 2);
	f->fractal.xr += ((f->fractal.scale / PRECISION) / 2) - \
					(f->mouse.pos_x / (f->fractal.scale * PRECISION));
	f->fractal.yi = (f->mouse.pos_y / f->fractal.scale + f->fractal.yi) - \
					((f->fractal.scale / PRECISION) / 2);
	f->fractal.yi += ((f->fractal.scale / PRECISION) / 2) - \
					(f->mouse.pos_y / (f->fractal.scale * PRECISION));
	f->fractal.scale /= PRECISION;
	f->fractal.iteration += 1;
}

/*
** fractal mouse control
** @param mc
** @param x
** @param y
** @param fractal
** @return
*/

int				fractal_mouse(int mc, int x, int y, t_fractal *fractal)
{
	if (x > 0 && y > 0 && x < W_WIDTH && y < W_HEIGHT)
	{
		if (mc == MOUSE_UP_SCROLL)
			zoom_in(x, y, fractal);
		else if (mc == MOUSE_DOWN_SCROLL)
			zoom_out(fractal);
		else if (mc == MOUSE_MIDDLE_CLICK)
			fractal_init(fractal);
		else if (mc == MOUSE_LEFT_CLICK)
		{
			if (fractal->mouse.state == 1)
				fractal->mouse.state = 0;
			else
				fractal->mouse.state = 1;
		}
		fractal_update(fractal);
	}
	return (0);
}
