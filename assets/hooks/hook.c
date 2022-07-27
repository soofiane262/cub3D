/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:28:23 by sel-mars          #+#    #+#             */
/*   Updated: 2022/07/27 18:23:34 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

#include <time.h>

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
	mlx_destroy_window(cub->mlx.mlx_ptr, cub->mlx.win_ptr);
	free(cub);
	cub = NULL;
	exit(0);
	return (0);
}

// void	update_player(t_cub *cub)
// {
// 	if (cub->player.mvt && !(cub->player.mvt % 3))
// 	{	// W	// S
// 		cub->player.y_pos += cub->player.mvt / 3;
// 	}
// 	if (cub->player.mvt && !(cub->player.mvt % 2))
// 	{	// A	// D
// 		cub->player.x_pos += cub->player.mvt / 2;
// 	}
// 		// <- (Left)	// -> (Right)
// 	cub->player.rotation += cub->player.turn * ROT_SPEED;
// }

int	render_frame(t_cub *cub)
{
	if (cub->tmp_int < 10)
	{

ft_putendl_fd("check", 1);

		mlx_clear_window(cub->mlx.mlx_ptr, cub->mlx.win_ptr);
		ft_2d_map(cub);
	}
	if (cub->tmp_int == 400)
		cub->tmp_int = 0;
	cub->tmp_int++;
	return (0);
}

int	key_press(int key, t_cub *cub)
{
	if (key == 53)
		leave(cub);
	else if (key == 13)
	{	// W
		// cub->player.mvt = -3;
		cub->player.y_pos--;
	}
	else if (key == 0)
	{	// A
		// cub->player.mvt = -2;
		cub->player.x_pos--;
	}
	else if (key == 1)
	{	// S
		// cub->player.mvt = 3;
		cub->player.y_pos++;
	}
	else if (key == 2)
	{	// D
		// cub->player.mvt = 2;
		cub->player.x_pos++;
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
	// update_player(cub);
	mlx_clear_window(cub->mlx.mlx_ptr, cub->mlx.win_ptr);
	ft_2d_map(cub);
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
	else if (key == 0)
	{	// A
		cub->player.mvt = 0;
	}
	else if (key == 1)
	{	// S
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
