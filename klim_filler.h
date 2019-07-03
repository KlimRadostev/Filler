/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_klim_wreks.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kradoste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 17:59:12 by kradoste          #+#    #+#             */
/*   Updated: 2019/07/02 19:33:27 by kradoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KLIM_FILLER_H
# define KLIM_FILLER_H

# include "libft/libft.h"

typedef struct	s_init
{
	char	player;
	char	enemy;
	int		mapx;
	int		mapy;
	char	**map;
	int		piecex;
	int		piecey;
	char	**piece;
	int		extra;
	int		keep_going;
}				t_init;

typedef struct	s_coor
{
	int	piece_x;
	int	piece_y;
	int	piece_l;
	int	piece_d;
	int	god_x;
	int	god_y;
	int	x;
	int	y;
	int	sml_i;
	int	sml;
	int	qn_sml_i;
	int	qn_sml;
}				t_coor;

int				**two_d_mallow_int(int x, int y);
int				**make_heat_map(t_init *vars);
void			find_coordinates(int **heat_map, t_init *vars);

#endif
