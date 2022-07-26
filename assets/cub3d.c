/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:13:23 by sel-mars          #+#    #+#             */
/*   Updated: 2022/07/26 17:27:07 by sel-mars         ###   ########.fr       */
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
	mlx_key_hook(cub->mlx.win_ptr, key_hook, cub);
	mlx_hook(cub->mlx.win_ptr, ON_DESTROY, 0, leave, cub);
	mlx_loop_hook(cub->mlx.mlx_ptr, render_frame, cub);
	mlx_loop(cub->mlx.mlx_ptr);
	return (0);
}
