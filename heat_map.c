/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heat_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kradoste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 18:59:37 by kradoste          #+#    #+#             */
/*   Updated: 2019/07/02 17:48:03 by kradoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "klim_filler.h"

int		**two_d_mallow_int(int x, int y)
{
	int	n;
	int	**two;

	if (!(two = (int **)malloc(sizeof(int *) * (y + 1))))
		return (NULL);
	n = -1;
	while (++n < y)
		if (!(two[n] = (int *)malloc(sizeof(int) * (x))))
			return (NULL);
	two[y] = NULL;
	return (two);
}

int		catch_smallest(int **heat_map, int x, int y, t_init *vars)
{
	int	small;

	small = 2147483647;
	if (x + 1 < vars->mapx && heat_map[y][x + 1] < small)
		small = heat_map[y][x + 1];
	if (y + 1 < vars->mapy && x + 1 < vars->mapx &&
heat_map[y + 1][x + 1] < small)
		small = heat_map[y + 1][x + 1];
	if (y + 1 < vars->mapy && heat_map[y + 1][x] < small)
		small = heat_map[y + 1][x];
	if (x - 1 > -1 && y + 1 < vars->mapy && heat_map[y + 1][x - 1] < small)
		small = heat_map[y + 1][x - 1];
	if (x - 1 > -1 && heat_map[y][x - 1] < small)
		small = heat_map[y][x - 1];
	if (x - 1 > -1 && y - 1 > -1 && heat_map[y - 1][x - 1] < small)
		small = heat_map[y - 1][x - 1];
	if (y - 1 > -1 && heat_map[y - 1][x] < small)
		small = heat_map[y - 1][x];
	if (y - 1 > -1 && x + 1 < vars->mapx && heat_map[y - 1][x + 1] < small)
		small = heat_map[y - 1][x + 1];
	return (small);
}

void	create_heat(t_init *vars, int **heat_map)
{
	int	x;
	int	y;
	int	small;
	int	n;

	n = -1;
	small = -1;
	while (++n < vars->mapy)
	{
		y = -1;
		while (++y < vars->mapy)
		{
			x = -1;
			while (++x < vars->mapx)
			{
				if (heat_map[y][x] != -1)
				{
					small = catch_smallest(heat_map, x, y, vars);
					heat_map[y][x] = small + 1;
				}
			}
		}
	}
}

int		**make_heat_map(t_init *vars)
{
	int	**heat_map;
	int	x;
	int	y;

	y = -1;
	heat_map = two_d_mallow_int(vars->mapx, vars->mapy);
	while (++y < vars->mapy)
	{
		x = -1;
		while (++x < vars->mapx)
		{
			if ((vars->map[y][x] == 'X' && vars->player == 'O') ||
(vars->map[y][x] == 'O' && vars->player == 'X'))
				heat_map[y][x] = -1;
			else
				heat_map[y][x] = 0;
		}
	}
	create_heat(vars, heat_map);
	return (heat_map);
}
