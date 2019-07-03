/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kradoste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 13:44:40 by kradoste          #+#    #+#             */
/*   Updated: 2019/07/02 19:35:00 by kradoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "klim_filler.h"

char	**two_d_mallow(int x, int y)
{
	int		n;
	char	**two;

	if (!(two = (char **)malloc(sizeof(char *) * (y + 1))))
		return (NULL);
	n = -1;
	while (++n < y)
		if (!(two[n] = (char *)malloc(sizeof(char) * (x + 1))))
			return (NULL);
	two[y] = NULL;
	return (two);
}

void	initialize_vars_filler(t_init *vars, int *l_t)
{
	*l_t = 1;
	vars->mapx = 0;
	vars->mapy = 0;
	vars->piecex = 0;
	vars->piecey = 0;
	vars->extra = 0;
	vars->keep_going = 0;
}

void	get_all_info(t_init *vars, int l_t, char *line)
{
	if (l_t == 1 && !ft_strncmp("Plateau ", line, 8))
	{
		vars->mapy = ft_atoi(&line[8]);
		if (vars->mapy == 100)
			vars->extra = 1;
		vars->mapx = ft_atoi(&line[11 + vars->extra]);
		vars->map = two_d_mallow(vars->mapx, vars->mapy);
	}
	else if (l_t >= 3 && l_t < vars->mapy + 3)
		vars->map[l_t - 3] =
ft_strcapitalize(ft_strcpy(vars->map[l_t - 3], &line[4]));
	else if (l_t == 3 + vars->mapy && !ft_strncmp("Piece ", line, 6))
	{
		vars->extra = 0;
		vars->piecey = ft_atoi(&line[6]);
		if (vars->piecey > 9)
			vars->extra = 1;
		vars->piecex = ft_atoi(&line[8 + vars->extra]);
		vars->piece = two_d_mallow(vars->piecex, vars->piecey);
	}
	else if (l_t >= 4 + vars->mapy && l_t <= 4 + vars->mapy + vars->piecey)
		vars->piece[l_t - (4 + vars->mapy)] =
ft_strcpy(vars->piece[l_t - (4 + vars->mapy)], line);
}

void	main_two(t_init *vars)
{
	int	**heat_map;

	vars->enemy = (vars->player == 'O') ? 'X' : 'O';
	heat_map = make_heat_map(vars);
	find_coordinates(heat_map, vars);
}

int		main(void)
{
	char	*line;
	int		line_track;
	t_init	vars;
	int		j;

	if (get_next_line(0, &line) == 1)
		if (!ft_strncmp("$$$ exec p", line, 10))
			vars.player = (line[10] == '1') ? 'O' : 'X';
	j = 1;
	while (j)
	{
		initialize_vars_filler(&vars, &line_track);
		while (vars.keep_going == 0 && get_next_line(0, &line) > -1)
		{
			get_all_info(&vars, line_track, line);
			line_track++;
			if (line_track == vars.piecey + vars.mapy + 4)
				vars.keep_going = 1;
		}
		if (vars.mapy == 0)
			return (0);
		main_two(&vars);
	}
	return (0);
}
