/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:13:23 by sel-mars          #+#    #+#             */
/*   Updated: 2022/09/08 19:50:15 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	init_gun_var(t_cub_bonus *cub_bonus)
{
	cub_bonus->mouse.clicked_left = false;
	cub_bonus->mouse.clicked_right = false;
	cub_bonus->gun.counter = 0;
	cub_bonus->gun.idx = 0;
	cub_bonus->gun.gun = (void **)malloc(sizeof(void *) * 13);
	cub_bonus->gun.gun_data = (int **)malloc(sizeof(int *) * 13);
}

static void	init_gun(t_cub_bonus *cub_bonus)
{
	int		tmp;
	int		idx;
	char	*tmp_char;
	char	*filename;

	init_gun_var(cub_bonus);
	idx = 0;
	while (idx <= 11)
	{
		cub_bonus->cub->buff = ft_itoa(idx);
		tmp_char = ft_strjoin(cub_bonus->cub->buff, ".xpm");
		free(cub_bonus->cub->buff);
		filename = ft_strjoin("./textures/gun/", tmp_char);
		free(tmp_char);
		cub_bonus->gun.gun[idx] = mlx_xpm_file_to_image(cub_bonus->cub->mlx.mlx,
				filename, &tmp, &cub_bonus->gun.gun_height);
		free(filename);
		cub_bonus->gun.gun_data[idx] = (int *)mlx_get_data_addr(
				cub_bonus->gun.gun[idx], &tmp, &cub_bonus->gun.gun_side, &tmp);
		idx++;
	}
	cub_bonus->gun.gun_side /= 4;
	cub_bonus->gun.gun[idx] = NULL;
	cub_bonus->gun.gun_data[idx] = NULL;
}

static void	init_door(t_cub_bonus *cub_bonus)
{
	int	tmp;

	cub_bonus->door.door = (void **)malloc(sizeof(void *) * 3);
	cub_bonus->door.door_data = (int **)malloc(sizeof(int *) * 3);
	cub_bonus->door.door[0] = mlx_xpm_file_to_image(cub_bonus->cub->mlx.mlx,
			"./textures/door/closed.xpm", &tmp, &tmp);
	cub_bonus->door.door_data[0] = (int *)mlx_get_data_addr(
			cub_bonus->door.door[0], &tmp, &cub_bonus->door.door_side, &tmp);
	cub_bonus->door.door[1] = mlx_xpm_file_to_image(cub_bonus->cub->mlx.mlx,
			"./textures/door/open.xpm", &tmp, &tmp);
	cub_bonus->door.door_data[1] = (int *)mlx_get_data_addr(
			cub_bonus->door.door[1], &tmp, &cub_bonus->door.door_side, &tmp);
	cub_bonus->door.door_side /= 4;
	cub_bonus->door.door[2] = NULL;
	cub_bonus->door.door_data[2] = NULL;
	cub_bonus->door.door_open = false;
}

static t_cub_bonus	*init_cub_bonus(t_cub *cub)
{
	t_cub_bonus	*cub_bonus;

	cub_bonus = (t_cub_bonus *)malloc(sizeof(t_cub_bonus));
	cub_bonus->cub = cub;
	cub_bonus->mouse.angle = 0;
	return (cub_bonus);
}

int	cub3d_bonus(int ac, char **av)
{
	t_cub		*cub;
	t_cub_bonus	*cub_bonus;

	cub = parsing(ac, av);
	ft_check_map_bonus(cub);
	init_mlx_ptrs(cub);
	cub_bonus = init_cub_bonus(cub);
	init_door(cub_bonus);
	init_gun(cub_bonus);
	init_mini_map(cub_bonus);
	mlx_hook(cub->mlx.win, ON_KEYPRESS, (1L << 0), key_press, cub);
	mlx_hook(cub->mlx.win, ON_KEYRELEASE, (1L << 1), key_release, cub);
	mlx_hook(cub->mlx.win, ON_BUTTONPRESS, (1L << 4), button_press, cub_bonus);
	mlx_hook(cub->mlx.win, ON_BUTTONRELEASE, (1L << 5),
		button_release, cub_bonus);
	mlx_hook(cub->mlx.win, ON_MOUSEMOVE, (1L << 6), mouse_move, cub_bonus);
	mlx_hook(cub->mlx.win, ON_DESTROY, 0L, leave_bonus, cub_bonus);
	mlx_loop_hook(cub->mlx.mlx, render_frame_bonus, cub_bonus);
	mlx_loop(cub->mlx.mlx);
	return (0);
}
