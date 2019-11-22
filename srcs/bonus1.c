/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 18:44:16 by sko               #+#    #+#             */
/*   Updated: 2019/11/21 18:44:28 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** random manual letter color
** @param fractal
*/

void	random_color_letter(t_fractal *fractal)
{
	fractal->manual_color = (rand() % 0xFFFFFF);
}

/*
** random fractal color
** @param fractal
*/

void	random_color_fractal(t_fractal *fractal)
{
	fractal->color.red = (rand() % 0xFFFFFF);
	fractal->color.blue = (rand() % 0xFFFFFF);
	fractal->color.green = (rand() % 0xFFFFFF);
}