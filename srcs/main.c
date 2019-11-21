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

#include "fractol.h"

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
** Assign a key code to a specific task
*/

static int	fractal_keys(int ks, t_fractal *fractal)
{
	if (ks == KEY_NAS_ESCAPE)
		exit(0);
	else if (ks == KEY_AS_I)
		fractal->fractal.iteration -= 1;
	else if (ks == KEY_AS_O)
		fractal->fractal.iteration += 1;
	fractal_update(fractal);
	return (0);
}

void		display_manual(t_fractal *fractal)
{
	int		x;

	x = 0;
	mlx_string_put(fractal->mlx.init, fractal->mlx.win, x, 65,\
	0XFFFFFF, "[ESC]                     exit fdf program");
	mlx_string_put(fractal->mlx.init, fractal->mlx.win, x, 95,\
	0XFFFFFF, "[Key |I|O|]                 Change iteration");
}

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
		fractal->mlx.img = mlx_new_image(fractal->mlx.init, W_WIDTH, W_HEIGHT);
		fractal->image.data = mlx_get_data_addr(fractal->mlx.img, \
			&fractal->image.bpp, &fractal->image.size, &fractal->image.endian);
		fractal_init(fractal);
		fractal_update(fractal);
		mlx_hook(fractal->mlx.win, 2, 3, fractal_keys, fractal);
//		mlx_hook(fdf->mlx.win, 4, 3, mouse_control, fdf);
//		mlx_loop_hook(fdf->mlx.init, generate_fdf_map, fdf);
		mlx_loop(fractal->mlx.init);
	}
	return (0);
}
