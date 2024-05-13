/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:06:41 by paula             #+#    #+#             */
/*   Updated: 2024/05/08 11:50:29 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	image_inicialize(t_main *main)
{
	int	i;

	main->picture.p_north = mlx_xpm_file_to_image(main->mlx,
			main->textures.north, &i, &i);
	main->picture.p_south = mlx_xpm_file_to_image(main->mlx,
			main->textures.south, &i, &i);
	main->picture.p_west = mlx_xpm_file_to_image(main->mlx, main->textures.west,
			&i, &i);
	main->picture.p_east = mlx_xpm_file_to_image(main->mlx, main->textures.east,
			&i, &i);
}

void	util_image(t_main *main, int x, int y)
{
	if (main->file_content[y][x] == '1')
		mlx_put_image_to_window(main->mlx, main->win, main->picture.p_east, (x
				* 64), (y * 64));
	else if (main->file_content[y][x] == 'P' || main->file_content[y][x] == '0')
		mlx_put_image_to_window(main->mlx, main->win, main->picture.p_east, (x
				* 64), (y * 64));
	else if (main->file_content[y][x] == 'E')
		mlx_put_image_to_window(main->mlx, main->win, main->picture.p_east, (x
				* 64), (y * 64));
	else if (main->file_content[y][x] == 'C')
		mlx_put_image_to_window(main->mlx, main->win, main->picture.p_east, (x
				* 64), (y * 64));
}
//************nao vamos usar pq é por angulos *************

int	render_image(t_main *main)
{
	int	x;
	int	y;

	y = -1;
	while (main->file_content[++y] != NULL)
	{
		x = -1;
		while (main->file_content[y][++x] != '\0')
			util_image(main, x, y);
	}
	mlx_put_image_to_window(main->mlx, main->win, main->picture.p_east,
		(main->player.x * 64), (main->player.y * 64));
	return (0);
}
// podemos utilizar algo disso mas vai ter que adaptar