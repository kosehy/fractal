/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 15:58:41 by sko       0        #+#    #+#             */
/*   Updated: 2019/10/04 16:27:24 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

/*
** select fractal based on argument
** @param args
** @param fractal
** @return
*/

static int	fractal_selection(char *args, t_fractal *fractal)
{
	fractal->fractal.type = 0;
	if (ft_strequ(args, "mandelbrot"))
		fractal->fractal.type = 1;
	else if (ft_strequ(args, "julia"))
		fractal->fractal.type = 2;
	else if (ft_strequ(args, "ginkgo"))
		fractal->fractal.type = 3;
	else
	{
		ft_putstr(args);
		ft_putstr(" is not a valid parameter!");
		ft_putstr("Check the usage with ./fractal ");
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
	else if (ks == KEY_AS_V)
		random_color_letter(fractal);
	else if (ks == KEY_AS_X)
		random_color_fractal(fractal);
	fractal_update(fractal);
	return (0);
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
		mlx_hook(fractal->mlx.win, 4, 3, fractal_mouse, fractal);
		mlx_hook(fractal->mlx.win, 6, 3, follow_by_mouse, fractal);
		mlx_loop(fractal->mlx.init);
	}
	return (0);
}
