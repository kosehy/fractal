/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 11:41:34 by sko               #+#    #+#             */
/*   Updated: 2019/11/20 11:41:56 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		put_pixel(t_fractal *fractal, int depth)
{
	int		pos;

	pos = (fractal->fractal.height + (fractal->fractal.width * W_WIDTH)) * 4;
	if (fractal->fractal.height < W_WIDTH \
			&& fractal->fractal.width < W_HEIGHT \
			&& depth == fractal->fractal.iteration)
	{
		fractal->image.data[pos] = 0x00;
		fractal->image.data[pos + 1] = 0x00;
		fractal->image.data[pos + 2] = 0x00;
	}
	else if (fractal->fractal.height < W_WIDTH \
			&& fractal->fractal.width < W_HEIGHT)
	{
		fractal->image.data[pos] = fractal->color.red + (depth * 2.42);
		fractal->image.data[pos + 1] = fractal->color.green + (depth * 2.42);
		fractal->image.data[pos + 2] = fractal->color.blue + (depth * 2.42);
	}
}

/*
** mandelbrot fractal
** @param fractal
** @return
*/

int				mandelbrot(t_fractal *fractal)
{
	float	zr;
	float	zi;
	float	cr;
	float	ci;
	float	tmp_zr;

	fractal->fractal.depth = 0;
	zr = (fractal->mouse.pos_x - W_WIDTH) / ((float)W_WIDTH * 2) + 0.25;
	zi = (fractal->mouse.pos_y - W_HEIGHT) / ((float)W_HEIGHT) + 0.50;
	ci = fractal->fractal.width / fractal->fractal.scale + fractal->fractal.yi;
	cr = fractal->fractal.height / fractal->fractal.scale + fractal->fractal.xr;
	while (zr * zr + zi * zi < 4 \
			&& fractal->fractal.depth < fractal->fractal.iteration)
	{
		tmp_zr = zr;
		zr = zr * zr - zi * zi + cr;
		zi = (2 * zi) * tmp_zr + ci;
		++fractal->fractal.depth;
	}
	return (fractal->fractal.depth);
}

/*
** draw the fractal based on the fractal.type
** @param slot
** @return
*/

static void		*draw_fractal(void *slot)
{
	t_fractal	*fractal;
	int			depth;
	float		tmp;

	fractal = (t_fractal *)slot;
	tmp = fractal->fractal.width;
	while (fractal->fractal.height < W_WIDTH)
	{
		fractal->fractal.width = tmp;
		while (fractal->fractal.width < fractal->fractal.limit)
		{
			depth = (fractal->fractal.type == 1) ? mandelbrot(fractal) : depth;
			put_pixel(fractal, depth);
			++fractal->fractal.width;
		}
		++fractal->fractal.height;
	}
	return (slot);
}

/*
** do the image process with multi-threading
** @param fractal
*/

void			fractal_pthread(t_fractal *fractal)
{
	t_fractal	thread[THREADS];
	pthread_t	p_th[THREADS];
	int			i;

	i = 0;
	while (i < THREADS)
	{
		ft_memcpy((void *)&thread[i], (void *)fractal, sizeof(t_fractal));
		thread[i].fractal.width = ((float)(1.00 / THREADS) * W_WIDTH) * i;
		thread[i].fractal.limit = ((float)(1.00 / THREADS) * W_WIDTH) * (i + 1);
		++i;
	}
	i = 0;
	while (i < THREADS) {
		pthread_create(&p_th[i], NULL, draw_fractal, &thread[i]);
		++i;
	}
	while (i)
	{
		--i;
		pthread_join(p_th[i], NULL);
	}
	mlx_put_image_to_window(fractal->mlx.init, fractal->mlx.win, \
							fractal->mlx.img, 0, 0);
}

//void			fractal(t_fdf *fdf, float left, float top, float xside, float yside)
//{
//	float	xscale;
//	float	yscale;
//	float	zx;
//	float	zy;
//	float	cx;
//	float	tempx;
//	float	cy;
//	int		x;
//	int		y;
//	int		i;
//	int		j;
//	int		maxx;
//	int		maxy;
//	int		count;
//
//	maxx = W_WIDTH;
//	maxy = W_HEIGHT;
//	xscale = xside / maxx;
//	yscale = yside / maxy;
//	draw_rectangle(fdf, height, width);
//	y = 1;
//	while (y <= maxy - 1)
//	{
//		x = 1;
//		while (x <= maxx - 1)
//		{
//			cx = x * xscale + left;
//			cy = y * xscale + top;
//			zx = 0;
//			zy = 0;
//			count = 0;
//			while ((zx * zx + zy * zy < 4) && (count < 10))
//			{
//				tempx = zx * zx - zy * zy + cx;
//				zy = 2 * zx * zy + cy;
//				zx = tempx;
//				++count;
//			}
//			fdf->map.values
//			++x;
//		}
//		++y;
//	}
//}
