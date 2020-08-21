/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 15:49:53 by rkyttala          #+#    #+#             */
/*   Updated: 2019/12/14 15:44:05 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		optimize(t_block *tetros, char **map, size_t x, int y)
{
	t_block		*temp;
	int			i;
	int			map_left;

	i = 0;
	map_left = 0;
	temp = tetros->start;
	while (temp)
	{
		if (temp->c == tetros->c)
			i = -1;
		i++;
		temp = temp->next;
	}
	i = i * 4;
	while (map[y] != NULL)
	{
		y++;
		map_left++;
	}
	map_left = y * map_left - x;
	if (map_left < i && tetros->c != 'A')
		return (1);
	return (0);
}

/*
** find_solution utilizes backtracking to check all possible tetromino
** placements within the current map.
** once all tetrominos have been successfully fitted in the map, the function
** returns 0.
*/

int		find_solution(t_block *tetros, char **map, size_t x, int y)
{
	if (tetros == NULL)
		return (0);
	while (map[y] != NULL)
	{
		while (map[y][x] != '\n')
		{
			if (check_area(tetros, map, x, y))
			{
				place_tetro(tetros, map, x, y);
				if (optimize(tetros, map, x, y) ||
					find_solution(tetros->next, map, 0, 0))
					delete_tetro(tetros, map, x, y);
				else
					return (0);
			}
			x++;
		}
		y++;
		x = 0;
	}
	if (tetros->next == NULL && scan_map(tetros->start, map))
		return (0);
	return (1);
}

int		new_solution(t_block *tetros, char **map, size_t x, int y)
{
	if (tetros == NULL)
		return (0);
	while (map[y] != NULL)
	{
		while (map[y][x] != '\n')
		{
			if (check_area(tetros, map, x, y))
			{
				place_tetro(tetros, map, x, y);
				if (new_solution(tetros->next, map, 0, 0))
					delete_tetro(tetros, map, x, y);
				else
					return (0);
			}
			x++;
		}
		y++;
		x = 0;
	}
	if (tetros->next == NULL && scan_map(tetros->start, map))
		return (0);
	return (1);
}

/*
** Scans the filled map for tetrimino blocks. If the map doesn't contain
** all the tetriminos that are in the list, it returns 0, which signals
** adjust_map to create a bigger map and try again.
*/

int		scan_map(t_block *tetros, char **map)
{
	int		i;
	int		found;

	while (tetros)
	{
		found = 0;
		i = 0;
		while (map[i] != NULL)
		{
			if (ft_strchr(map[i], tetros->c))
				found = 1;
			i++;
		}
		tetros = tetros->next;
		if (found == 0)
			return (0);
	}
	return (1);
}
