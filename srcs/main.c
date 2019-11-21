/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 15:58:41 by sko               #+#    #+#             */
/*   Updated: 2019/10/04 16:27:24 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	fractal_selection(char *args, t_fractal *fractal)
{
	fractal->fractal.type = 0;
	if (ft_strequ(args, "mandelbrot"))
		fractal->fractal.type = 1;
	else
	{
		ft_putstr(args);
		ft_putstr(" is not a valid parameter!");
		ft_putstr("See usage for a list of valid parameters!");
	}
	return (fractal->fractal.type);
}

/*
** Reset the map based on the initial values.
*/

static void	reset_map(t_fdf *fdf)
{
	fdf->map.coord_x = 0;
	fdf->map.coord_y = 0;
	fdf->map.z_value = 1.00;
	fdf->map.angle_y = cos(M_PI / 3);
	fdf->map.angle_x = fdf->map.angle_y * sin(M_PI / 6);
	fdf->map.zoom = ceil((fdf->map.width > fdf->map.height)) \
		? (W_WIDTH / fdf->map.width) + MAGIC_ZOOM \
		: (W_HEIGHT / fdf->map.height) + MAGIC_ZOOM;
	fdf->map.isometric = 1;
	fdf->map.man_color = 0xFFFFFF;
	fdf->color.blue = 0x4F;
	fdf->color.green = 0x4F;
	fdf->color.red = 0x4F;
}

/*
** Colorize the map with a random color which are from
** 0x00 to 0x7F to avoid integer overflow.
*/

static void	randomize_color(t_fdf *fdf)
{
	fdf->color.blue = (rand() % 0x7F);
	fdf->color.green = (rand() % 0x7F);
	fdf->color.red = (rand() % 0x7F);
}

/*
** Assign a key code to a specific task
*/

static int	fdf_keys(int ks, t_fdf *fdf)
{
	if (ks == KEY_NAS_ESCAPE)
		exit(0);
	else if (ks == KEY_AS_W || ks == KEY_NAS_UPARROW)
		fdf->map.coord_x -= 1;
	else if (ks == KEY_AS_S || ks == KEY_NAS_DOWNARROW)
		fdf->map.coord_x += 1;
	else if (ks == KEY_AS_A || ks == KEY_NAS_LEFTARROW)
		fdf->map.coord_y -= 1;
	else if (ks == KEY_AS_D || ks == KEY_NAS_RIGHTARROW)
		fdf->map.coord_y += 1;
	else if (ks == KEY_AS_Q)
		fdf->map.zoom += 1;
	else if ((ks == KEY_AS_E) && (fdf->map.zoom > MAX_ZOOM))
		fdf->map.zoom -= 1;
	else if (ks == KEY_AS_R)
		reset_map(fdf);
	else if (ks == KEY_AS_X)
		randomize_color(fdf);
	else if (ks == KEY_AS_V)
		random_color_letter(fdf);
	else if (ks == KEY_NAS_SPACE)
		fdf->map.angle_x *= (fdf->map.isometric++ % 2) ? 0.2 : 5;
	return (0);
}

//static int	mouse_control(int button, int x, int y, t_fdf *fdf)
//{
//	int		prev_x;
//	int		prev_y;
//
//	prev_x = x;
//	prev_y = y;
//	if ((button == 4) && (fdf->map.z_value < MAX_X))
//		fdf->map.z_value += 0.5;
//	else if ((button == 5) && (fdf->map.z_value > -MAX_X))
//		fdf->map.z_value -= 0.5;
//	return (0);
//}

int			main(int argc, char *argv[])
{
	t_fractal	*fractal;

	if (argc == 2)
	{
		if (!(fractal = (t_fractal *)malloc(sizeof(t_fractal))))
			ft_puterror("Memory Allocation Error!");
		if (!fractal_selection(argv[1], fractal))
			ft_puterror("Please, try again!");
		fractal->mlx.init = mlx_init();
		fractal->mlx.win = mlx_new_window(fractal->mlx.init, \
		W_WIDTH, W_HEIGHT, argv[1]);
		fractal->mlx.win = mlx_new_image(fractal->mlx.init, W_WIDTH, W_HEIGHT);
		fractal->image.data = mlx_get_data_addr(fractal->mlx.img, \
			&fractal->image.bpp, &fractal->image.size, &fractal->image.endian);
		fractal_init(fractal);
		fractal_update(fractal);
		mlx_hook(fractal->mlx.win, 2, 3, fdf_keys, fractal);
//		mlx_hook(fdf->mlx.win, 4, 3, mouse_control, fdf);
//		mlx_loop_hook(fdf->mlx.init, generate_fdf_map, fdf);
		mlx_loop(fractal->mlx.init);
	}
	return (0);
}
