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

#include <stdio.h>

t_ray	*raycast(t_cub *cub)
{
	int		i;
	double	ray_angle;
	t_ray	*ray;
	t_ray	*ray_head;

	ray_angle = cub->player.rotation - (FOV * M_PI / 360);
	ray = NULL;
	ray_head = NULL;
	ray = (t_ray *)malloc(sizeof(t_ray));
	ray_head = ray;
	i = -1;
	while (++i < NB_RAYS)
	{
		ray->next = NULL;
		ray_angle = fmod(ray_angle, (2 * M_PI));
		if (ray_angle < 0)
			ray_angle += 2 * M_PI;
		ray->ray_angle = ray_angle;
		if (i < NB_RAYS - 1)
			ray->next = (t_ray *)malloc(sizeof(t_ray));
		ray = ray->next;
		ray_angle += ((((double)FOV * M_PI) / (180 * NB_RAYS)));
	}
	return (ray_head);
}

void	ray_free(t_cub *cub)
{
	t_ray	*tmp_ray;

	while (cub->ray)
	{
		tmp_ray = cub->ray;
		cub->ray = cub->ray->next;
		free(tmp_ray);
		tmp_ray = NULL;
	}
}
