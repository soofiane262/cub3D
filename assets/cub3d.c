/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:13:23 by sel-mars          #+#    #+#             */
/*   Updated: 2022/07/28 14:56:14 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	cub3d(int ac, char **av)
{
	t_cub	*cub;

	cub = parsing(ac, av);
	if (!cub)
		return (1);
	if (init_mlx_ptrs(cub) || ft_2d_map(cub))
		return (1);
	cub->tmp_int = 0;
	cub->tmp_int2 = 0;
	mlx_hook(cub->mlx.win, ON_KEYPRESS, 0, key_press, cub);
	mlx_hook(cub->mlx.win, ON_KEYRELEASE, 0, key_release, cub);
	mlx_hook(cub->mlx.win, ON_DESTROY, 0, leave, cub);
	mlx_loop_hook(cub->mlx.mlx, render_frame, cub);
	mlx_loop(cub->mlx.mlx);
	return (0);
}
