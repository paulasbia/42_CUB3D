/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:06:41 by paula             #+#    #+#             */
/*   Updated: 2024/05/23 09:59:31 by paula            ###   ########.fr       */
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
	main->picture.floor = mlx_xpm_file_to_image(main->mlx, "./texture/map2d/floor.xpm",
			&i, &i);
	main->picture.wall = mlx_xpm_file_to_image(main->mlx, "./texture/map2d/test.xpm",
			&i, &i);
	main->picture.player2d = mlx_xpm_file_to_image(main->mlx, "./images/player2d_2.xpm" , &i, &i);
	// main->img->mlx_img = mlx_xpm_file_to_image(main->mlx, "./texture/map2d/floor.xpm",
	// 		main->img->width, main->img->height);
	// main->img->addr = mlx_get_data_addr(main->img->mlx_img, &(main->img->bpp), &(main->img->line_len),
	// 		&(main->img->endian));
	// main->picture.wall = mlx_xpm_file_to_image(main->mlx, "./texture/map2d/test.xpm",
	// 		&i, &i);
}

void	ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dest;

	if (y >= 0 && x >= 0 && y < WINDOW_HEIGHT && x < WINDOW_WIDTH)
	{
		dest = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(unsigned int *)dest = color;
	}
}
#pragma GCC push_options
#pragma GCC optimize ("O0")

void draw_line2(t_main *cub, double x1, double y1, double x2, double y2, int color){
	double del_x = x2 - x1;
	double del_y = y2 - y1;
	
	double pixels = sqrt((del_x * del_x) + (del_y * del_y)); // ???
	if (pixels > WINDOW_HEIGHT){
		pixels = WINDOW_HEIGHT;
	}
	if(pixels<0){ //!!!!!
		pixels = 0;
	}
	del_x /= pixels;
	del_y /= pixels;

	while (pixels > 0)
	{
		mlx_pixel_put(cub->mlx, cub->win, x1, y1, color);
		x1 += del_x;
		y1 += del_y;
		--pixels;
	}
}



void	draw_line(t_main *cub)
{
	double del_x = 20 - cub->player.x;
	double del_y = 20 - cub->player.y;
	int pixels = sqrt((del_x * del_x) + (del_y * del_y));
	del_x /= pixels;
	del_y /= pixels;
	double pixelX = cub->player.x;
	double pixelY = cub->player.y;
	while (pixels)
	{
		mlx_pixel_put(cub->mlx, cub->win, pixelX, pixelY, 0xFFFFFF);
		pixelX += del_x;
		pixelY += del_y;
		--pixels;
	}
}

void draw_player(t_main *cub)
{
		mlx_pixel_put(cub->mlx, cub->win, cub->player.x, cub->player.y, 0xFF0000);

		draw_line2(cub, cub->player.x, cub->player.y, cub->player.x - cub->player.vector_front.dx*15, cub->player.y - cub->player.vector_front.dy*15, 0xFF0000);


		t_vector lado_cima, lado_baixo, visao_cima, visao_baixo;
		rotate2(cub->player.angle+PI/2, &lado_cima);
		rotate2(cub->player.angle-PI/2, &lado_baixo);
		rotate2(cub->player.angle+PI/6, &visao_cima);
		rotate2(cub->player.angle-PI/6, &visao_baixo);
		
		draw_line2(cub, cub->player.x - cub->player.vector_front.dx*15, cub->player.y - cub->player.vector_front.dy*15, cub->player.x - cub->player.vector_front.dx*15 - lado_cima.dx*5, cub->player.y - cub->player.vector_front.dy*15 - lado_cima.dy*5, 0x0000FF);
		
		draw_line2(cub, cub->player.x - cub->player.vector_front.dx*15, cub->player.y - cub->player.vector_front.dy*15, cub->player.x - cub->player.vector_front.dx*15 - lado_baixo.dx*5, cub->player.y - cub->player.vector_front.dy*15 - lado_baixo.dy*5, 0x0000FF);

		double temp_x = cub->player.x;
		double temp_y = cub->player.y;
		while(!player_hit(cub, visao_cima, temp_x, temp_y))
		{
			temp_x -= visao_cima.dx;
			temp_y -= visao_cima.dy;
		}
		draw_line2(cub, cub->player.x, cub->player.y, temp_x, temp_y, 0xFF00FF);
		temp_x = cub->player.x;
		temp_y = cub->player.y;
		while(!player_hit(cub, visao_baixo, temp_x, temp_y))
		{
			temp_x -= visao_baixo.dx;
			temp_y -= visao_baixo.dy;
		}
		draw_line2(cub, cub->player.x, cub->player.y, temp_x, temp_y, 0xFF00FF);
}

void	util_image(t_main *main, int x, int y)
{
	if (main->map[y][x] == '1')
		mlx_put_image_to_window(main->mlx, main->win, main->picture.wall, (x
				* MINI_WIDTH), (y * MINI_WIDTH));
	else if (main->map[y][x] != '\n' || main->map[y][x] == '0')
	
		mlx_put_image_to_window(main->mlx, main->win, main->picture.floor, (x
				* MINI_WIDTH), (y * MINI_WIDTH));
	
}

void	render_mini(t_main *cub)
{
	static double angle = 0;
	static double px = 0;
	static double py = 0;

	if (cub->player.angle == angle && cub->player.x == px && cub->player.y == py) // otimizou o minimap porem para mudar do 3D para 2D assim precisa movimentar o player..
			return;
	int	x;
	int	y;
	angle = cub->player.angle;
	px = cub->player.x;
	py = cub->player.y;

	y = -1;
	while (cub->map[++y] != NULL)
	{
		x = -1;
		while (cub->map[y][++x] != '\0')
			util_image(cub, x, y);
	}

	draw_player(cub);
}

void	render_3D(t_main *cub)
{
	int 		x_screen;
	t_raycast	ray;

	x_screen = 0;
	//TENHO QUE COLOCAR O CEILING AND FLOOR, ACREDITO QUE POR IMAGEM...
	// int x = 0;
	// int y = 0;
	// while (y < WINDOW_HEIGHT)
	// {
	// 	x = 0;
	// 	if (y > WINDOW_HEIGHT / 2)
	// 		while (x < WINDOW_WIDTH)
	// 			mlx_pixel_put(cub->mlx, cub->win, x++, y, 0x550000);
	// 	else
	// 	{
	// 		while (x < WINDOW_WIDTH)
	// 			mlx_pixel_put(cub->mlx, cub->win, x++, y, 0x555500);
	// 	}
	// 	y++;
	// }
	while(x_screen < WINDOW_WIDTH)
	{
		t_vector	pos; //vou precisar criar a var posicao pq no minimap eu multipliquei
		pos.dx = cub->player.x /  MINI_WIDTH;
		pos.dy = cub->player.y / MINI_WIDTH;
		
		double cameraX;
		
		cameraX = 2 * x_screen / (double)WINDOW_WIDTH - 1;
		start_ray(&ray, cameraX, cub, pos);
		ray.hit = 0;
		
		//calculate step and initial sideDist
		ray_steps(&ray, pos);

		//performing DDA
		performing_dda(&ray, cub);
		draw_wall(&ray, cub, x_screen, pos);
		x_screen++;
	}
}

#pragma GCC pop_options

int	render_image(t_main *main)
{
	if(main->is_mini)
		render_mini(main);
	else
		//printf("teste\n");
		render_3D(main);
	return 0;	
}
