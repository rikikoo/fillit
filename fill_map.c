/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:36:39 by rkyttala          #+#    #+#             */
/*   Updated: 2019/12/14 15:31:22 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** make_map generates a "map" (2D array) based on the value of "tiles".
*/

char	**make_map(int tiles)
{
	char	**map;
	int		x;
	int		y;
	int		a;

	y = 0;
	a = 2;
	while ((a * a) < tiles)
		a++;
	if (!(map = (char**)malloc(sizeof(char*) * (a + 1))))
		return (0);
	while (y < a)
	{
		x = 0;
		if (!(map[y] = ft_strnew(a + 1)))
			return (0);
		while (x <= (a - 1))
			map[y][x++] = '.';
		map[y++][x] = '\n';
	}
	map[y] = NULL;
	y = 0;
	return (map);
}

/*
** check_area checks if the current tetromino's coordinates
** land on empty spaces.
*/

int		check_area(t_block *tetros, char **map, size_t x, int y)
{
	int			i;
	size_t		tetro_x;
	size_t		tetro_y;
	size_t		len;

	len = ft_strlen(map[0]);
	i = 0;
	while (i < 4)
	{
		tetro_x = tetros->hash_x[i];
		tetro_y = tetros->hash_y[i];
		if ((x + tetro_x) < len && (y + tetro_y) < (len - 1) &&
			map[y + tetro_y][x + tetro_x] == '.')
			i++;
		else
			return (0);
	}
	return (1);
}

void	delete_tetro(t_block *tetros, char **map, size_t x, int y)
{
	int			i;
	size_t		tetro_x;
	int			tetro_y;

	i = 0;
	while (i < 4)
	{
		tetro_x = tetros->hash_x[i];
		tetro_y = tetros->hash_y[i];
		map[y + tetro_y][x + tetro_x] = '.';
		i++;
	}
}

/*
** place_tetromino does extactly the same as check_area, but instead of
** checking whether there's space for the block, it overwrites the '.'
** with the current tetromino's alphabet char.
*/

void	place_tetro(t_block *tetros, char **map, size_t x, int y)
{
	int			i;
	size_t		tetro_x;
	int			tetro_y;

	i = 0;
	while (i < 4)
	{
		tetro_x = tetros->hash_x[i];
		tetro_y = tetros->hash_y[i];
		map[y + tetro_y][x + tetro_x] = tetros->c;
		i++;
	}
}

/*
** If find_solution can't place the tetrominos in any way, adjust_map calls
** itself again with a bigger "tiles" size, so that it generates a bigger
** map and does everything again on the bigger map.
*/

void	adjust_map(t_block *tetros, int tiles)
{
	char		**map;
	int			i;

	i = -1;
	map = make_map(tiles);
	find_solution(tetros, map, 0, 0);
	while (!scan_map(tetros, map))
	{
		while (map[++i] != NULL)
			free(map[i]);
		map = NULL;
		map = make_map(tiles);
		new_solution(tetros, map, 0, 0);
		if (scan_map(tetros, map))
			break ;
		i = 2;
		while ((i * i) < tiles)
			i++;
		adjust_map(tetros, (i * i + 1));
	}
	i = -1;
	while (map[++i] != NULL)
		ft_putstr(map[i]);
	exit(0);
}
