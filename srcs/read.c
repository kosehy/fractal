/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:57:35 by sko               #+#    #+#             */
/*   Updated: 2019/10/13 11:39:57 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				check_num(char c)
{
	return (c >= '0' && '9' >= c);
}

static int		count_fdf_depth(char *line)
{
	int			len;
	char		**nums;
	int			count;

	nums = ft_strsplit(line, ' ');
	len = 0;
	while (nums[len] != '\0')
	{
		count = 0;
		while (count < (int)ft_strlen(nums[len]))
		{
			if (nums[ft_strlen(nums[len])] == '\0')
				break ;
			else if (nums[len][count] == '-' || check_num(nums[len][count]))
				count++;
			else if (nums[len][count] == ',' && nums[len][count + 1] == '0' \
			&& nums[len][count + 2] == 'x')
				break ;
			else
				ft_puterror("Invalid characters or read error");
		}
		len += 1;
	}
	free_2d_str(nums);
	return (len);
}

static int		count_fdf_lines(t_fdf *fdf, char *argv)
{
	int		fd;
	int		size;
	int		rows;
	int		cols;
	char	*line;

	if ((fd = open(argv, O_RDONLY)) < 0)
		ft_puterror("Error opening file!");
	cols = 0;
	rows = 0;
	while (get_next_line(fd, &line) == 1)
	{
		if (*line == '\0')
			break ;
		if ((size = count_fdf_depth(line)) > cols)
			cols = size;
		(cols == size) ? rows += 1 : ft_puterror("Not a valid file!");
		free(line);
	}
	if (close(fd) < 0)
		ft_puterror("Error closing file!");
	if (!(fdf->map.width = cols))
		ft_puterror("Not a valid file!");
	return (rows);
}

static void		get_values(t_fdf *fdf, int x, int y, char *line)
{
	int		i;
	char	**split;

	if ((split = ft_strsplit(line, ' ')))
	{
		i = 0;
		while (split[i] && (y != fdf->map.width))
		{
			fdf->map.values[x][y] = ft_atoi(split[i]);
			++i;
			y += 1;
		}
		free_2d_str(split);
	}
}

void			read_fdf_map(char *argv, t_fdf *fdf)
{
	int		y;
	int		x;
	int		fd;
	char	*line;

	y = 0;
	x = 0;
	fdf->map.height = count_fdf_lines(fdf, argv);
	if ((fd = open(argv, O_RDONLY)) < 0)
		ft_puterror("Error opening file!");
	if (!(fdf->map.values = (int **)malloc(sizeof(int *) * fdf->map.height)))
		ft_puterror("Memory Allocation failed!");
	while (get_next_line(fd, &line) == 1 && x != fdf->map.height)
	{
		if (!(fdf->map.values[x] = (int *)malloc(sizeof(int) * fdf->map.width)))
			ft_puterror("Memory ALlocation failed!");
		get_values(fdf, x, y, line);
		y = 0;
		x += 1;
		free(line);
	}
	if (close(fd) < 0)
		ft_puterror("Error closing file!");
}
