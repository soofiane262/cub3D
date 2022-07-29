/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 16:50:43 by sel-mars          #+#    #+#             */
/*   Updated: 2022/07/29 19:34:18 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// void	raycast(t_cub *cub)
// {
// 	int		i;
// 	double	ray_angle;

// 	cub->ray = (double *)malloc(sizeof(double) * NB_RAYS);
// 	ray_angle = cub->player.rotation - (FOV * M_PI / 360);
// 	i = -1;
// 	while (++i < NB_RAYS)
// 	{
// 		cub->ray[i] = ray_angle;
// 		ray_angle += ((((double)FOV * M_PI) / (180 * NB_RAYS)));
// 	}
// }
