/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_coordinates.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kradoste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 19:07:06 by kradoste          #+#    #+#             */
/*   Updated: 2019/07/02 19:07:24 by kradoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "klim_filler.h"

void	parse_piece(t_coor *co, t_init *vars)
{
	int	x;
	int y;
	int key;

	key = 0;
	y = -1;
	co->piece_l = -1;
	while (++y < vars->piecey)
	{
		x = -1;
		while (++x < vars->piecex)
			if (vars->piece[y][x] == '*')
			{
				if (co->piece_x > x || co->piece_x == -1)
					co->piece_x = x;
				if (co->piece_l < x || co->piece_l == -1)
					co->piece_l = x;
				if (key == 0)
				{
					key = 1;
					co->piece_y = y;
				}
				co->piece_d = y;
			}
	}
}

int		place_piece(t_init *vars, t_coor *co)
{
	int	x;
	int	y;
	int	play_c;

	y = co->piece_y - 1;
	play_c = 0;
	while (++y <= co->piece_d)
	{
		x = co->piece_x - 1;
		while (++x <= co->piece_l)
			if (vars->piece[y][x] == '*')
			{
				if (vars->map[co->y + (y - co->piece_y)]
[co->x + (x - co->piece_x)] == vars->player)
					play_c++;
				else if (vars->map[co->y + (y - co->piece_y)]
[co->x + (x - co->piece_x)] == vars->enemy)
					return (0);
			}
	}
	if (play_c == 1)
		return (1);
	return (0);
}

int		current_winner(t_coor *co)
{
	if (co->sml == -1 || co->sml > co->sml_i)
	{
		co->sml = co->sml_i;
		co->qn_sml = co->qn_sml_i;
		return (1);
	}
	else if (co->sml == co->sml_i && co->qn_sml < co->qn_sml_i)
	{
		co->qn_sml = co->qn_sml_i;
		return (1);
	}
	return (0);
}

int		best_piece(int **heat_map, t_init *vars, t_coor *co)
{
	int	x;
	int	y;

	y = co->piece_y - 1;
	co->sml_i = -1;
	while (++y <= co->piece_d)
	{
		x = co->piece_x - 1;
		while (++x <= co->piece_l)
			if (vars->piece[y][x] == '*')
			{
				if (co->sml_i == -1 || heat_map[co->y +
(y - co->piece_y)][co->x + (x - co->piece_x)] < co->sml_i)
				{
					co->sml_i = heat_map[co->y +
(y - co->piece_y)][co->x + (x - co->piece_x)];
					co->qn_sml_i = 1;
				}
				else
					co->qn_sml_i++;
			}
	}
	return (current_winner(co));
}

void	find_coordinates(int **heat_map, t_init *vars)
{
	t_coor		co;

	co.y = -1;
	co.god_y = 0;
	co.god_x = 0;
	co.piece_y = 0;
	co.piece_x = -1;
	co.sml = -1;
	co.qn_sml = -1;
	parse_piece(&co, vars);
	while (++co.y + (co.piece_d - co.piece_y) < vars->mapy)
	{
		co.x = -1;
		while (++co.x + (co.piece_l - co.piece_x) < vars->mapx)
		{
			if (place_piece(vars, &co))
				if (best_piece(heat_map, vars, &co))
				{
					co.god_y = co.y - co.piece_y;
					co.god_x = co.x - co.piece_x;
				}
		}
	}
	ft_printf("%d %d\n", co.god_y, co.god_x);
}
