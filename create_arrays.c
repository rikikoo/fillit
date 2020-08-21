/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_arrays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:03:43 by orantane          #+#    #+#             */
/*   Updated: 2019/12/13 14:23:37 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** This function trims the coordinates so, that the top left of the block is
** always at the most top left position.
*/

void		trim_x(t_block *block, int i)
{
	int min_x;
	int array_size;

	array_size = 3;
	while (block)
	{
		min_x = 5;
		while (i < array_size)
		{
			if (block->hash_x[i] < min_x)
				min_x = block->hash_x[i];
			i++;
		}
		while (i >= 0)
		{
			block->hash_x[i] = block->hash_x[i] - min_x;
			i--;
		}
		block = block->next;
	}
}

t_coord		*place(t_coord *coord, char *str, t_block *block, int hash_count)
{
	coord->x = 0;
	coord->y = 0;
	while (hash_count < 4)
	{
		if (str[coord->i] == '\n')
		{
			coord->x = -1;
			coord->count++;
		}
		if (str[coord->i] == '#')
		{
			block->hash_x[hash_count] = coord->x;
			block->hash_y[hash_count] = coord->y;
			hash_count++;
		}
		if (hash_count != 0 && str[coord->i] == '\n')
			coord->y++;
		coord->x++;
		coord->i++;
		if (hash_count == 4)
			break ;
	}
	return (coord);
}

/*
** The fill_list does exactly that. It fills the arrays with the coordinates
** we get from reading the already validated string. It takes the x and y
** values and saves them to the correct slots in the arrays.
*/

void		fill_list(char *str, t_block *block)
{
	t_coord	*coord;

	if (!(coord = (t_coord*)malloc(sizeof(t_coord))))
		exit(0);
	coord->i = 0;
	coord->count = 0;
	while (str[coord->i] != '\0')
	{
		if ((coord->count % 5) == 0)
		{
			coord = place(coord, str, block, 0);
			if (block == NULL)
				break ;
			block = block->next;
		}
		if (str[coord->i] == '\n')
			coord->count++;
		coord->i++;
	}
	free(coord);
}

/*
** This function creates a new struct to the list and sets the pointer
** to NULL. It then returns the pointer to the new node.
*/

t_block		*new_block(char c, t_block *start)
{
	t_block		*new;

	if (!(new = (t_block *)malloc(sizeof(t_block))))
		return (NULL);
	new->c = c;
	new->start = start;
	new->next = NULL;
	return (new);
}

/*
** This function takes the validated string that contains the blocks.
** It then creates a list of structs, that all have two int arrays the
** size of [4] and one char, that has the alphabet we will use when
** printing the block. The function only assigns the char, arrays are
** filled at the functions above.
*/

t_block		*create_list(char *str, int block_count)
{
	t_block	*block;
	t_block *start;
	int		i;
	char	c;

	i = 0;
	c = 'A';
	if (!(block = (t_block *)malloc(sizeof(t_block))))
		return (NULL);
	start = block;
	block->c = c;
	block->next = NULL;
	block->start = start;
	while (++i < block_count)
	{
		c++;
		if (!(block->next = new_block(c, start)))
			return (NULL);
		block = block->next;
	}
	fill_list(str, start);
	trim_x(start, 0);
	return (start);
}
