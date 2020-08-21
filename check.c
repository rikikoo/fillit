/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 13:52:40 by orantane          #+#    #+#             */
/*   Updated: 2019/12/09 18:14:32 by orantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		valid_tetriminos(char *str, int i, int j)
{
	int		connections;

	while (str[j] != '\0')
	{
		connections = 0;
		i = 0;
		while (str[j + i] != '\0' && !(str[j + i] == '\n' && (str[j + i + 1] ==
				'\0' || str[i + j + 1] == '\n')))
		{
			if (str[j + i] == '#' && str[i + j + 1] == '#')
				connections++;
			if (str[j + i] == '#' && str[j + i - 1] == '#' && i > 0)
				connections++;
			if (str[j + i] == '#' && str[j + i + 5] == '#' && i < 15)
				connections++;
			if (str[j + i] == '#' && str[j + i - 5] == '#' && i > 4)
				connections++;
			i++;
		}
		j = j + i + 1;
		if (!(connections == 6 || connections == 8))
			return (0);
	}
	return (1);
}

int		check_dots(char *str)
{
	int		i;
	int		dots;

	i = 0;
	dots = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '.')
			dots++;
		if (str[i] == '\n' && (str[i + 1] == '\n' || str[i + 1] == '\0'))
		{
			if (dots != 12)
				return (0);
			dots = 0;
		}
		i++;
	}
	return (1);
}

int		check_row(char *str, int i, int row)
{
	if (str[i + 1] == '\n' && row % 4 != 0)
		return (0);
	if (str[i] == '\n' && (str[i + 1] == '\n' || str[i + 1] == '\0') &&
			row % 16 != 0)
		return (0);
	return (1);
}

int		hash_count(char *str, int i, int row)
{
	int		count;

	row = 0;
	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '#' || str[i] == '.')
		{
			row++;
			if (!(check_row(str, i, row)))
				return (0);
		}
		if (str[i] == '#')
			count++;
		if ((str[i] == '\n' && (str[i + 1] == '\n' || str[i + 1] == '\0')
				&& ((count % 4) != 0)))
			return (0);
		i++;
	}
	if (!valid_tetriminos(str, i, 0) || !check_dots(str))
		return (0);
	return (count);
}

int		validate(char *blocks, int block_count)
{
	int		i;
	int		newline_count;

	i = 0;
	newline_count = 0;
	while (blocks[i] != '\0')
	{
		if (blocks[i] == '.' || blocks[i] == '#' || blocks[i] == '\n')
		{
			if (blocks[i] == '\n')
				newline_count++;
			if (newline_count == 4 || (newline_count % 5) == 4)
			{
				if (!(blocks[i] == '\n' && (blocks[i + 1] == '\0' ||
						blocks[i + 1] == '\n')))
					return (0);
			}
		}
		else
			return (0);
		i++;
	}
	if (!(((newline_count / 5) + 1) == block_count))
		return (0);
	return (hash_count(blocks, i, newline_count));
}
