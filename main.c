/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 12:53:27 by rkyttala          #+#    #+#             */
/*   Updated: 2019/12/13 16:36:33 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char	*open_file(int argc, char **argv)
{
	int		fd;
	int		i;
	char	*str;
	char	buf[BUFF_SIZE];

	if (argc != 2)
	{
		write(1, "usage: ./fillit tetriminos_file\n", 32);
		return (NULL);
	}
	fd = open(argv[1], O_RDONLY);
	if ((i = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[i] = '\0';
		if (!(str = ft_strdup(buf)))
			return (NULL);
	}
	close(fd);
	if (i <= 0 || i == BUFF_SIZE)
	{
		write(1, "error\n", 6);
		exit(0);
	}
	return (str);
}

int		main(int argc, char **argv)
{
	char	*str;
	t_block	*coordinates;
	int		block_count;
	int		i;

	block_count = 0;
	i = 1;
	if (!(str = open_file(argc, argv)))
		return (0);
	while (str[i++] != '\0')
	{
		if (str[i] == '\n' && (str[i + 1] == '\n' || str[i + 1] == '\0'))
			block_count++;
	}
	i = validate(str, block_count);
	if (i == 0 || block_count > 26)
	{
		write(1, "error\n", 6);
		exit(0);
	}
	if (!(coordinates = create_list(str, block_count)))
		exit(0);
	adjust_map(coordinates, i);
}
