/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 16:22:02 by sko               #+#    #+#             */
/*   Updated: 2019/10/04 16:22:04 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

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

# define MAX_X			(10)
# define MAX_ZOOM		(5)
# define MAGIC_ZOOM		(2)
# define W_WIDTH		(1600)
# define W_HEIGHT		(1200)
# define THREADS		1

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
	int state;
	int pos_x;
	int pos_y;
}				t_mouse;

typedef struct	s_fractal
{
	t_mlx		mlx;
	t_image		image;
	t_color		color;
	t_type		fractal;
	t_mouse		mouse;
	int			manual_color;
}				t_fractal;

/*
** Prototypes of the read file and draw functions.
*/

void			display_manual(t_fractal *fractal);

/*
**	fractal.c
*/

void			fractal_pthread(t_fractal *fractal);

/*
** util.c
*/

void			fractal_init(t_fractal *fractal);
void			fractal_update(t_fractal *fractal);

#endif
