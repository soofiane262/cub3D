/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:13:23 by sel-mars          #+#    #+#             */
/*   Updated: 2022/08/25 18:25:57 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	cub3d_bonus(int ac, char **av)
{
	t_cub		*cub;

	cub = parsing(ac, av);
	init_mlx_ptrs(cub);
	init_mini_map(cub);
	mlx_hook(cub->mlx.win, ON_KEYPRESS, (1L << 0), key_press, cub);
	mlx_hook(cub->mlx.win, ON_KEYRELEASE, (1L << 1), key_release, cub);
	mlx_hook(cub->mlx.win, ON_DESTROY, 0L, leave, cub);
	mlx_loop_hook(cub->mlx.mlx, render_frame_bonus, cub);
	mlx_loop(cub->mlx.mlx);
	return (0);
}
