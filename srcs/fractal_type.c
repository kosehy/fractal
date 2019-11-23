/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 10:05:42 by sko               #+#    #+#             */
/*   Updated: 2019/11/22 10:05:52 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

/*
** mandelbrot fractal
** @param f
** @return
*/

int				mandelbrot_frac(t_fractal *f)
{
	float	scale;

	scale = f->fractal.scale;
	f->cp.zr = (f->mouse.pos_x - W_WIDTH) / ((float)W_WIDTH * 2) + 0.25;
	f->cp.zi = (f->mouse.pos_y - W_HEIGHT) / ((float)W_HEIGHT) + 0.50;
	f->cp.cr = f->fractal.width / scale + f->fractal.yi;
	f->cp.ci = f->fractal.height / scale + f->fractal.xr;
	while (SQUARE(f->cp.zr) + SQUARE(f->cp.zi) < 4 \
			&& f->fractal.depth < f->fractal.iteration)
	{
		f->cp.tmp_zr = f->cp.zr;
		f->cp.zr = SQUARE(f->cp.zr) - SQUARE(f->cp.zi) + f->cp.cr;
		f->cp.zi = (2 * f->cp.zi) * f->cp.tmp_zr + f->cp.ci;
		++f->fractal.depth;
	}
	return (f->fractal.depth);
}

/*
** julia fractal
** @param f
** @return
*/

int				julia_frac(t_fractal *f)
{
	float	w;
	float	h;
	float	scale;

	scale = f->fractal.scale;
	f->fractal.xr = -2.70;
	f->fractal.yi = -2.00;
	w = (210.0 / 2.0) + W_WIDTH;
	h = (320.0 / 2.0) + W_HEIGHT;
	f->cp.cr = (f->mouse.pos_x - w) / ((float)W_WIDTH * 2) + 0.15;
	f->cp.ci = (f->mouse.pos_y - h) / ((float)W_HEIGHT) - 0.15;
	f->cp.zi = f->fractal.width / scale + f->fractal.yi;
	f->cp.zr = f->fractal.height / scale + f->fractal.xr;
	while (SQUARE(f->cp.zr) + SQUARE(f->cp.zi) < 4 \
			&& f->fractal.depth < f->fractal.iteration)
	{
		f->cp.tmp_zr = f->cp.zr;
		f->cp.zr = SQUARE(f->cp.zr) - SQUARE(f->cp.zi) + f->cp.cr;
		f->cp.zi = (2 * f->cp.zi) * f->cp.tmp_zr + f->cp.ci;
		++f->fractal.depth;
	}
	return (f->fractal.depth);
//	float	scale;
//
//	scale = f->fractal.scale;
//	f->cp.zr = (f->mouse.pos_x - W_WIDTH) / ((float)W_WIDTH * 2) + 0.25;
//	f->cp.zi = (f->mouse.pos_y - W_HEIGHT) / ((float)W_HEIGHT) + 0.50;
//	f->cp.cr = f->fractal.width / scale + f->fractal.yi;
//	f->cp.ci = f->fractal.height / scale + f->fractal.xr;
//	while (SQUARE(f->cp.zr) + SQUARE(f->cp.zi) < 4 \
//			&& f->fractal.depth < f->fractal.iteration)
//	{
//		f->cp.tmp_zr = f->cp.zr;
//		f->cp.zr = SQUARE(f->cp.zr) - SQUARE(f->cp.zi) + f->cp.cr;
//		f->cp.zi = (2 * f->cp.zi) * f->cp.tmp_zr + f->cp.ci;
//		++f->fractal.depth;
//	}
//	return (f->fractal.depth);
}

int				frog_frac(t_fractal *f)
{
	float	w;
	float	h;
	float	scale;

	scale = f->fractal.scale;
	f->fractal.xr = -2.70;
	f->fractal.yi = -2.00;
	w = (210.0 / 2.0) + W_WIDTH;
	h = (320.0 / 2.0) + W_HEIGHT;
	f->cp.cr = (f->mouse.pos_x - w) / ((float)W_WIDTH * 2) + 0.15;
	f->cp.ci = (f->mouse.pos_y - h) / ((float)W_HEIGHT) - 0.15;
	f->cp.zi = f->fractal.width / scale + f->fractal.yi;
	f->cp.zr = f->fractal.height / scale + f->fractal.xr;
	while (SQUARE(f->cp.zr) + SQUARE(f->cp.zi) < 4 \
			&& f->fractal.depth < f->fractal.iteration)
	{
		f->cp.tmp_zr = f->cp.zr;
		f->cp.zr = SQUARE(f->cp.zr) - SQUARE(f->cp.zi) + f->cp.cr;
		f->cp.zi = -2 * SQUARE(f->cp.zi) * f->cp.tmp_zr + f->cp.ci;
		++f->fractal.depth;
	}
	return (f->fractal.depth);
}

int				butterfly_frac(t_fractal *f)
{
	float	w;
	float	h;
	float	scale;

	scale = f->fractal.scale;
	f->fractal.xr = -2.70;
	f->fractal.yi = -2.00;
	w = (210.0 / 2.0) + W_WIDTH;
	h = (320.0 / 2.0) + W_HEIGHT;
	f->cp.cr = (f->mouse.pos_x - w) / ((float)W_WIDTH * 2) + 0.15;
	f->cp.ci = (f->mouse.pos_y - h) / ((float)W_HEIGHT) - 0.15;
	f->cp.zr = f->fractal.width / scale + f->fractal.yi;
	f->cp.zi = f->fractal.height / scale + f->fractal.xr;
	while (SQUARE(f->cp.zr) + SQUARE(f->cp.zi) < 4 \
			&& f->fractal.depth < f->fractal.iteration)
	{
		f->cp.tmp_zr = SQUARE(f->cp.zr) - SQUARE(f->cp.zi) + f->cp.cr;
		f->cp.zi = fabs(2 * f->cp.zr * f->cp.zi) + f->cp.ci;
		f->cp.zr = f->cp.tmp_zr;
		++f->fractal.depth;
	}
	return (f->fractal.depth);
}

int				ginkgo_frac(t_fractal *f)
{
	float	scale;

	scale = f->fractal.scale;
	f->fractal.xr = -2.7;
	f->fractal.yi = -2.1;
	f->cp.cr = 0.29;
	f->cp.ci = 0.02;
	f->cp.zi = f->fractal.width / scale + f->fractal.yi;
	f->cp.zr = f->fractal.height / scale + f->fractal.xr;
	while (SQUARE(f->cp.zr) + SQUARE(f->cp.zi) < 4 \
			&& f->fractal.depth < f->fractal.iteration)
	{
		f->cp.tmp_zr = f->cp.zr;
		f->cp.zr = SQUARE(f->cp.zr) - SQUARE(f->cp.zi) + f->cp.cr;
		f->cp.zi = -2 * SQUARE(f->cp.zi) * f->cp.tmp_zr + f->cp.ci;
		++f->fractal.depth;
	}
	return (f->fractal.depth);
}
