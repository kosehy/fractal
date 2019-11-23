/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 10:06:32 by sko               #+#    #+#             */
/*   Updated: 2019/11/22 10:07:00 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H
# define FRACTAL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <time.h>
# include <pthread.h>

# include "libft.h"
# include "mlx.h"
# include "keys.h"

# define MAX_ZOOM		500000000
# define W_WIDTH		1600
# define W_HEIGHT		1200
# define THREADS		8
# define PRECISION		1.045

# define SQUARE(x) (x * x)

typedef struct	s_dispatch_table
{
	int			type;
	int			(*ft)();
}				t_dt;

typedef struct	s_image
{
	char		*data;
	int			size;
	int			endian;
	int			bpp;
}				t_image;

typedef struct	s_color
{
	int			blue;
	int			green;
	int			red;
}				t_color;

typedef struct	s_mlx
{
	void		*init;
	void		*win;
	void		*img;
}				t_mlx;

typedef struct	s_type
{
	int			type;
	int			depth;
	int			iteration;
	float		width;
	float		height;
	float		scale;
	float		limit;
	float		xr;
	float		yi;
}				t_type;

typedef struct	s_mouse
{
	int			state;
	int			pos_x;
	int			pos_y;
}				t_mouse;

typedef struct	s_complex
{
	float		zr;
	float		zi;
	float		cr;
	float		ci;
	float		tmp_zr;
	float		a;
	float		b;
	float		w;
	float		h;
}				t_complex;

typedef struct	s_fractal
{
	t_mlx		mlx;
	t_image		image;
	t_color		color;
	t_type		fractal;
	t_mouse		mouse;
	t_complex	cp;
	int			manual_color;
}				t_fractal;

/*
**	fractal.c
*/

void			fractal_pthread(t_fractal *fractal);
void			fractal_update(t_fractal *fractal);

/*
** util.c
*/

void			fractal_init(t_fractal *fractal);
int				follow_by_mouse(int x, int y, t_fractal *fractal);
int				fractal_mouse(int mc, int x, int y, t_fractal *fractal);

/*
** fractal_type.c
*/

int				mandelbrot_frac(t_fractal *f);
int				julia_frac(t_fractal *f);
int				frog_frac(t_fractal *f);
int				butterfly_frac(t_fractal *f);
int				ginkgo_frac(t_fractal *f);

/*
** bonus1.c
*/

void			random_color_letter(t_fractal *fractal);
void			random_color_fractal(t_fractal *fractal);

#endif
