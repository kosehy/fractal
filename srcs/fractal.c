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

#include "fractal.h"

/*
** dispatch table for various fractal type
*/

t_dt			g_dt[] =
{
	{1, mandelbrot_frac},
	{2, julia_frac},
	{3, frug_frac},
	{4, butterfly_frac},
	{5, ginkgo_frac}
};

/*
** put pixel function
** @param fractal
** @param depth
*/

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
** generate any fractal based on fractal.type value
** @param f
** @return
*/

int				f_generator(t_fractal *f)
{
	float	scale;
	int		i;

	i = 0;
	scale = f->fractal.scale;
	f->fractal.depth = 0;
	f->cp.zr = (f->mouse.pos_x - W_WIDTH) / ((float)W_WIDTH * 2) + 0.25;
	f->cp.zi = (f->mouse.pos_y - W_HEIGHT) / ((float)W_HEIGHT) + 0.50;
	f->cp.cr = f->fractal.width / scale + f->fractal.yi;
	f->cp.ci = f->fractal.height / scale + f->fractal.xr;
	while (i < 5)
	{
		if (g_dt[i].type == f->fractal.type)
		{
			f->fractal.depth = g_dt[i].ft(f);
			break ;
		}
		++i;
	}
	return (f->fractal.depth);
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
			depth = f_generator(fractal);
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

/*
** Update the fractal image.
** @param fractal
*/

void			fractal_update(t_fractal *fractal)
{
	int		x;

	x = 10;
	if (fractal->fractal.iteration <= 0)
		fractal->fractal.iteration = 0;
	fractal_pthread(fractal);
}
