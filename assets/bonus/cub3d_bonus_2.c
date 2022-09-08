/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 19:44:32 by kid-bouh          #+#    #+#             */
/*   Updated: 2022/09/08 19:49:58 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	button_press(int button, int x, int y, t_cub_bonus *cub_bonus)
{
	(void)x;
	(void)y;
	if (button == 1)
		cub_bonus->mouse.clicked_left = true;
	if (button == 2)
		cub_bonus->mouse.clicked_right = true;
	return (0);
}

int	button_release(int button, int x, int y, t_cub_bonus *cub_bonus)
{
	(void)x;
	(void)y;
	if (button == 1)
		cub_bonus->mouse.clicked_left = false;
	return (0);
}

int	mouse_move(int x, int y, t_cub_bonus *cub_bonus)
{
	static int	last_mouse_x;

	if (int_in_range(y, 0, WIN_HEIGHT))
	{
		cub_bonus->mouse.angle = 2 * atan((last_mouse_x - x)
				/ ((WIN_WIDTH / 2) / tan(FOV * M_PI / 360)));
	}
	last_mouse_x = x;
	return (0);
}
