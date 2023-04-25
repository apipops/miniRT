/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 17:30:54 by avast             #+#    #+#             */
/*   Updated: 2023/01/06 16:51:14 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/params.h"
#include "../includes/proto.h"
#include "../libft/libft.h"

int	close_window(t_data *data)
{
	free_tab_altcol((*data).map, (*data).size.y - 1);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->win_ptr = 0;
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	//mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit (0);
}

void	reset_user_type(t_data *data, int a)
{
	(*data).user = (t_params){0, 0, (t_size2d){0, 0}, 1,
		(*data).user.alti, a, (*data).user.color};
}

void	handle_keypress2(int keysym, t_data *data)
{
	if (keysym == XK_space)
		reset_user_type(data, -(*data).user.type);
	if (keysym == XK_2)
		(*data).user.alti *= 1.6;
	if (keysym == XK_1)
		(*data).user.alti /= 1.6;
	if (keysym == XK_c)
		(*data).user.color *= -1;
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		close_window(data);
	if (keysym == XK_Up)
		(*data).user.cent.y -= 20;
	if (keysym == XK_Down)
		(*data).user.cent.y += 20;
	if (keysym == XK_Left)
		(*data).user.cent.x -= 20;
	if (keysym == XK_Right)
		(*data).user.cent.x += 20;
	if (keysym == XK_w && (*data).user.a2 < 30)
		(*data).user.a2 += 1;
	if (keysym == XK_s && (*data).user.a2 > -30)
		(*data).user.a2 -= 1;
	if (keysym == XK_d)
		(*data).user.a1 += 2;
	if (keysym == XK_a)
		(*data).user.a1 -= 2;
	else
		handle_keypress2(keysym, data);
	return (0);
}

int	handle_mouse(int button, int x, int y, t_data *data)
{
	float	tsize1;
	float	tsize2;

	(void)x;
	(void)y;
	if (button == 4)
		(*data).user.tsize *= 1.4;
	if (button == 5)
	{
		tsize1 = roundf((WIDTH - WIDTH / 6) / roundf(sqrt((*data).size.x
						* (*data).size.x + (*data).size.y * (*data).size.y))
				* (*data).user.tsize);
		tsize2 = roundf((WIDTH - WIDTH / 6) / roundf(sqrt((*data).size.x
						* (*data).size.x + (*data).size.y * (*data).size.y))
				* ((*data).user.tsize / 1.4));
		if (tsize1 != tsize2)
			(*data).user.tsize /= 1.4;
	}
	return (0);
}
