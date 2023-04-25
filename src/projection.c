/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:47:40 by avast             #+#    #+#             */
/*   Updated: 2023/01/04 16:28:49 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/params.h"
#include "../includes/proto.h"
#include "../libft/libft.h"

float	setup_alti(int tsize, float a)
{
	if (a)
		return (70 / a);
	else
		return (tsize);
}

t_params	setup_param(t_size2d size, t_params user, float a)
{
	t_params	par;

	par.a1 = 0 + user.a1;
	par.tsize = roundf((WIDTH - WIDTH / 6) / roundf(sqrt(size.x
					* size.x + size.y * size.y)) * user.tsize);
	if (user.type == 1)
	{
		par.a2 = 30 + user.a2;
		par.cent.x = (int)roundf(-((float)size.x / 2 - (float)size.y / 2)
				* cal_cos(30) * par.tsize + WIDTH / 2) + user.cent.x;
		par.cent.y = (int)roundf(-((float)size.x / 2 + (float)size.y / 2)
				* cal_sin(par.a2) * par.tsize + HEIGHT / 2) + user.cent.y;
	}
	else
	{
		par.a2 = 45 + user.a2;
		par.cent.x = (int)roundf(-((float)size.x / 2 + 0.5 * cal_cos(par.a2)
					* (float)size.y / 2) * par.tsize + WIDTH / 2) + user.cent.x;
		par.cent.y = (int)roundf(-0.5 * cal_sin(par.a2) * (float)size.y / 2
				* par.tsize + HEIGHT / 2) + user.cent.y;
	}
	par.alti = setup_alti(par.tsize, a) * user.alti * user.tsize;
	par.type = user.type;
	par.color = user.color;
	return (par);
}

t_coor2d	get_2di(t_coor3d point, t_params params, t_size2d size)
{
	t_coor3d	tmp;
	t_coor2d	point2d;

	tmp.x = (point.x - (float)size.x / 2) * cal_cos(params.a1) - (point.y
			- (float)size.y / 2) * cal_sin(params.a1) + (float)size.x / 2;
	tmp.y = (point.x - (float)size.x / 2) * cal_sin(params.a1) + (point.y
			- (float)size.y / 2) * cal_cos(params.a1) + (float)size.y / 2;
	tmp.alt = point.alt;
	point2d.x = (int)roundf((tmp.x - tmp.y) * cal_cos(30)
			* params.tsize + params.cent.x);
	point2d.y = (int)roundf(((tmp.x + tmp.y) * cal_sin(params.a2)
				* params.tsize - tmp.alt.z * params.alti) + params.cent.y);
	if (params.color == 1 || (tmp.alt.color.r == 255 && tmp.alt.color.g == 255
			&& tmp.alt.color.b == 255))
		point2d.col = tmp.alt.color;
	else
		point2d.col = get_opp_color(tmp.alt.color);
	return (point2d);
}

t_coor2d	get_2dp(t_coor3d point, t_params params, t_size2d size)
{
	t_coor3d	tmp;
	t_coor2d	point2d;

	tmp.x = (point.x - (float)size.x / 2) * cal_cos(params.a1) - (point.y
			- (float)size.y / 2) * cal_sin(params.a1) + (float)size.x / 2;
	tmp.y = (point.x - (float)size.x / 2) * cal_sin(params.a1) + (point.y
			- (float)size.y / 2) * cal_cos(params.a1) + (float)size.y / 2;
	tmp.alt = point.alt;
	point2d.x = (int)roundf((tmp.x + 0.5 * cal_cos(params.a2) * tmp.y)
			* params.tsize + params.cent.x);
	point2d.y = (int)roundf(-tmp.alt.z * params.alti + 0.5 * cal_sin(params.a2)
			* tmp.y * params.tsize + params.cent.y);
	if (params.color == 1 || (tmp.alt.color.r == 255 && tmp.alt.color.g == 255
			&& tmp.alt.color.b == 255))
		point2d.col = tmp.alt.color;
	else
		point2d.col = get_opp_color(tmp.alt.color);
	return (point2d);
}

t_coor2d	**get_map_2d(t_data *data, t_altcol	**map, t_size2d size)
{
	int			i;
	int			j;
	t_coor2d	**map2;
	t_params	p;

	p = setup_param((*data).size, (*data).user, (*data).max_alti);
	map2 = malloc(sizeof(t_coor2d *) * (*data).size.y);
	if (!map2)
		return (0);
	i = -1;
	while (++i < (*data).size.y)
	{
		map2[i] = malloc((*data).size.x * sizeof(t_coor2d));
		if (!map2[i])
			return (free_tab_coor2d(map2, i - 1), (void *)0);
		j = -1;
		while (++j < (*data).size.x)
		{
			if ((*data).user.type == 1)
				map2[i][j] = get_2di((t_coor3d){j, i, map[i][j]}, p, size);
			else
				map2[i][j] = get_2dp((t_coor3d){j, i, map[i][j]}, p, size);
		}
	}
	return (map2);
}
