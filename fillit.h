/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:44:38 by rkyttala          #+#    #+#             */
/*   Updated: 2019/12/14 15:31:44 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# define BUFF_SIZE 1024

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct		s_pos
{
	int		x;
	int		y;
	int		count;
	size_t	i;
}					t_coord;

typedef	struct		s_block
{
	char				c;
	int					hash_x[4];
	int					hash_y[4];
	struct s_block		*next;
	struct s_block		*start;
}					t_block;

char				*open_file(int argc, char **argv);
int					validate(char *blocks, int block_count);
int					hash_count(char *str, int i, int row);
int					check_row(char *str, int i, int row);
int					valid_tetriminos(char *str, int i, int j);
t_block				*create_list(char *str, int block_count);
t_block				*new_block(char c, t_block *start);
void				fill_list(char *str, t_block *block);
t_coord				*place(t_coord *coord, char *str, t_block *block,
					int hash_count);
void				trim_x(t_block *block, int i);
void				adjust_map(t_block *tetros, int tiles);
int					scan_map(t_block *tetros, char **map);
char				**make_map(int tiles);
int					optimize(t_block *tetros, char **map, size_t x, int y);
int					find_solution(t_block *tetros, char **map, size_t x, int y);
int					new_solution(t_block *tetros, char **map, size_t x, int y);
int					check_area(t_block *tetros, char **map, size_t x, int y);
void				place_tetro(t_block *tetros, char **map, size_t x, int y);
void				delete_tetro(t_block *tetros, char **map, size_t x, int y);

#endif
