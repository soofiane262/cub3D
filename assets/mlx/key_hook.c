/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 18:33:22 by sel-mars          #+#    #+#             */
/*   Updated: 2022/08/10 19:18:53 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	key_press(int key, t_cub *cub)
{
	if (key != ESC && key != W && key != S && key != A && key != D
		&& key != LEFT_ARROW && key != RIGHT_ARROW)
		return (0);
	if (key == ESC)
		leave(cub);
	else if (key == W || key == S || key == A || key == D)
		cub->player.mvt = key;
	else if (key == LEFT_ARROW || key == RIGHT_ARROW)
		cub->player.turn = key;
	return (0);
}

int	key_release(int key, t_cub *cub)
{
	if (key == W || key == S || key == A || key == D)
		cub->player.mvt = -1;
	else if (key == LEFT_ARROW || key == RIGHT_ARROW)
		cub->player.turn = -1;
	return (0);
}
