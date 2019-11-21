/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:03:48 by sko               #+#    #+#             */
/*   Updated: 2019/10/08 16:03:49 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	store_pixel(t_fdf *fdf, int x, int y, double uvector)
{
	int		pos;

	if ((y > 0 && x > 0) && (y < W_WIDTH && x < W_HEIGHT))
	{
		pos = (y * 4) + (x * W_WIDTH * 4);
		fdf->image.data[pos] = fdf->color.red + uvector;
		fdf->image.data[pos + 1] = fdf->color.green + uvector;
		fdf->image.data[pos + 2] = fdf->color.blue + uvector;
		fdf->image.data[pos + 3] = 0x7F + uvector;
	}
}

static void	line_draw(t_fdf *fdf)
{
	double x;
	double y;
	double d_x;
	double d_y;
	double uvector;

	x = fdf->map.x0;
	y = fdf->map.y0;
	d_x = fdf->map.x1 - fdf->map.x0;
	d_y = fdf->map.y1 - fdf->map.y0;
	uvector = sqrt((pow(d_y, 2)) + (pow(d_x, 2)));
	d_x = d_x / uvector;
	d_y = d_y / uvector;
	while (uvector > 0)
	{
		store_pixel(fdf, x, y, uvector);
		uvector -= 1;
		x = x + d_x;
		y = y + d_y;
	}
}

static void	draw_h(t_fdf *fdf, int x, int y)
{
	int		xt;
	int		yt;

	xt = x - fdf->map.height / 2;
	yt = y - fdf->map.width / 2;
	fdf->map.x0 = fdf->map.angle_x * (yt + xt) * fdf->map.zoom;
	fdf->map.x0 -= fdf->map.values[x][y] * fdf->map.z_value;
	fdf->map.y0 = fdf->map.angle_y * (yt - xt) * fdf->map.zoom;
	fdf->map.x1 = fdf->map.angle_x * ((yt + 1) + xt) * fdf->map.zoom;
	fdf->map.x1 -= fdf->map.values[x][y + 1] * fdf->map.z_value;
	fdf->map.y1 = fdf->map.angle_y * ((yt + 1) - xt) * fdf->map.zoom;
	fdf->map.x0 += (W_HEIGHT / 2) + fdf->map.coord_x;
	fdf->map.x1 += (W_HEIGHT / 2) + fdf->map.coord_x;
	fdf->map.y0 += (W_WIDTH / 2) + fdf->map.coord_y;
	fdf->map.y1 += (W_WIDTH / 2) + fdf->map.coord_y;
	line_draw(fdf);
}

static void	draw_v(t_fdf *fdf, int x, int y)
{
	int		xt;
	int		yt;

	xt = x - fdf->map.height / 2;
	yt = y - fdf->map.width / 2;
	fdf->map.x0 = fdf->map.angle_x * (yt + xt) * fdf->map.zoom;
	fdf->map.x0 -= fdf->map.values[x][y] * fdf->map.z_value;
	fdf->map.x1 = fdf->map.angle_x * (yt + (xt + 1)) * fdf->map.zoom;
	fdf->map.x1 -= fdf->map.values[x + 1][y] * fdf->map.z_value;
	fdf->map.y0 = fdf->map.angle_y * (yt - xt) * fdf->map.zoom;
	fdf->map.y1 = fdf->map.angle_y * (yt - (xt + 1)) * fdf->map.zoom;
	fdf->map.x0 += (W_HEIGHT / 2) + fdf->map.coord_x;
	fdf->map.x1 += (W_HEIGHT / 2) + fdf->map.coord_x;
	fdf->map.y0 += (W_WIDTH / 2) + fdf->map.coord_y;
	fdf->map.y1 += (W_WIDTH / 2) + fdf->map.coord_y;
	line_draw(fdf);
}

int			generate_fdf_map(t_fdf *fdf)
{
	int		x;
	int		y;

	x = -1;
	fdf->mlx.img = mlx_new_image(fdf->mlx.init, W_WIDTH, W_HEIGHT);
	fdf->image.data = mlx_get_data_addr(fdf->mlx.img, &fdf->image.bpp, \
		&fdf->image.size, &fdf->image.endian);
	while (fdf->map.height > ++x)
	{
		y = -1;
		while (fdf->map.width > ++y)
		{
			fdf->map.x0 = x;
			fdf->map.y0 = y;
			if (fdf->map.height > x + 1)
				draw_v(fdf, x, y);
			if (fdf->map.width > y + 1)
				draw_h(fdf, x, y);
		}
	}
	mlx_put_image_to_window(fdf->mlx.init, fdf->mlx.win, fdf->mlx.img, 0, 0);
	display_manual(fdf);
	mlx_destroy_image(fdf->mlx.init, fdf->mlx.img);
	return (0);
}
