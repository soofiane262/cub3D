/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:28:23 by sel-mars          #+#    #+#             */
/*   Updated: 2022/07/28 20:15:02 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	leave(t_cub *cub)
{
	int	i;

	free(cub->map_path);
	free(cub->params.no_text);
	free(cub->params.so_text);
	free(cub->params.ea_text);
	free(cub->params.we_text);
	i = 0;
	while (i < cub->map.height)
	{
		free(cub->map.map[i]);
		cub->map.map[i++] = NULL;
	}
	free(cub->map.map);
	cub->map.map = NULL;
	mlx_destroy_window(cub->mlx.mlx, cub->mlx.win);
	free(cub);
	cub = NULL;
	exit(0);
	return (0);
}

int	render_frame(t_cub *cub)
{
	if (cub->tmp_int < 10)
	{

// ft_putendl_fd("check", 1);

		mlx_clear_window(cub->mlx.mlx, cub->mlx.win);
		ft_2d_map(cub);
	}
	if (cub->tmp_int == 400)
		cub->tmp_int = 0;
	cub->tmp_int++;
	return (0);
}

int	check_wall(int new_x, int new_y, t_cub *cub)
{
	int	x;
	int	y;

	if (new_x < 0 || new_y < 0 || new_x > cub->map.width * TILE_SIZE || new_y > cub->map.height * TILE_SIZE)
		return (1);
	x = floor(new_x / TILE_SIZE);
	y = floor(new_y / TILE_SIZE);
	if (cub->map.map[y][x] == '1')
		return (1);
	return (0);
}

int	key_press(int key, t_cub *cub)
{
	int	new_x;
	int	new_y;

	new_x = -10;
	new_y = -10;
	if (key == 53)
		leave(cub);
	else if (key == 13)
	{	// W
		new_x = cub->player.x_pos + MOVE_SPEED * cos(cub->player.rotation);
		new_y = cub->player.y_pos + MOVE_SPEED * sin(cub->player.rotation);
	}
	else if (key == 1)
	{	// S
		new_x = cub->player.x_pos - MOVE_SPEED * cos(cub->player.rotation);
		new_y = cub->player.y_pos - MOVE_SPEED * sin(cub->player.rotation);
	}
	else if (key == 0)
	{	// A
		new_x = cub->player.x_pos + MOVE_SPEED * cos(M_PI_2 - cub->player.rotation);
		new_y = cub->player.y_pos - MOVE_SPEED * sin(M_PI_2 - cub->player.rotation);
	}
	else if (key == 2)
	{	// D
		new_x = cub->player.x_pos - MOVE_SPEED * cos(M_PI_2 - cub->player.rotation);
		new_y = cub->player.y_pos + MOVE_SPEED * sin(M_PI_2 - cub->player.rotation);
	}
	else if (key == 123)
	{	// <- (Left)
		// cub->player.turn = -1;
		cub->player.rotation -= ROT_SPEED * M_PI / 180;
	}
	else if (key == 124)
	{	// -> (Right)
		// cub->player.turn = 1;
		cub->player.rotation += ROT_SPEED * M_PI / 180;
	}
	if (!check_wall(new_x, new_y, cub))
	{
		cub->player.x_pos = new_x;
		cub->player.y_pos = new_y;
	}
	// update_player(cub);
	// mlx_clear_window(cub->mlx.mlx, cub->mlx.win);
	// ft_2d_map(cub);
	// else if (key == 125)
	// {	// (Down)
	// }
	// else if (key == 126)
	// {	// ^ (Up)
	// }
	// ft_putnbr_fd(key, 1);
	// ft_putendl_fd("", 1);
	return (0);
}

int	key_release(int key, t_cub *cub)
{
	if (key == 13)
	{	// W
		cub->player.mvt = 0;
	}
	else if (key == 1)
	{	// S
		cub->player.mvt = 0;
	}
	else if (key == 0)
	{	// A
		cub->player.mvt = 0;
	}
	else if (key == 2)
	{	// D
		cub->player.mvt = 0;
	}
	else if (key == 123)
	{	// <- (Left)
		cub->player.turn = 0;
	}
	else if (key == 124)
	{	// -> (Right)
		cub->player.turn = 0;
	}
	// else if (key == 125)
	// {	// (Down)
	// }
	// else if (key == 126)
	// {	// ^ (Up)
	// }
	// ft_putnbr_fd(key, 1);
	// ft_putendl_fd("", 1);
	return (0);
}
