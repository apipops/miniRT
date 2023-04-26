/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:53:19 by avast             #+#    #+#             */
/*   Updated: 2023/04/26 12:40:14 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/params.h"
#include "../includes/proto.h"
#include "../libft/libft.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

void	display_background(t_img *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			img_pix_put(img, j, i, WHITE);
			j++;
		}
		++i;
	}
}

bool	hit_sphere(t_vec3 center, double radius, t_ray r)
{
	t_vec3	oc;
	double	a;
	double	half_b;
	double	c;

	oc.x = r.origin.x - center.x;
	oc.y = r.origin.y - center.y;
	oc.z = r.origin.z - center.z;
	a = r.direction.x * r.direction.x + r.direction.y * r.direction.y + r.direction.z * r.direction.z;
	half_b = oc.x * r.direction.x + oc.y * r.direction.y + oc.z * r.direction.z;
	c = oc.x * oc.x + oc.y * oc.y + oc.z * oc.z - radius * radius;
	if (half_b * half_b - a * c < 0)
		return (false);
	return (true);
}

void	display_ray(t_data *data)
{
	int		j;
	int		i;
	double	u;
	double	v;
	t_ray	r;

	r.origin = data->origin;
	j = HEIGHT - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < WIDTH)
		{
			u = (double)i / (WIDTH - 1);
			v = (double)j / (HEIGHT - 1);
			r.direction.x = data->lower_left_corner.x + u * data->horizontal.x + v * data->vertical.x - data->origin.x;
			r.direction.y = data->lower_left_corner.y + u * data->horizontal.y + v * data->vertical.y - data->origin.y;
			r.direction.z = data->lower_left_corner.z + u * data->horizontal.z + v * data->vertical.z - data->origin.z;
			if (hit_sphere((t_vec3){0, -100.5, -1}, 100, r))
				img_pix_put(&data->img, i, j, GREEN_PIXEL);
			if (hit_sphere((t_vec3){0, 0, -1}, 0.5, r))
				img_pix_put(&data->img, i, j, RED_PIXEL);
			i++;
		}
		j--;
	}
}

int	display(t_data *data)
{
	if (data->win_ptr == NULL)
		return (MLX_ERROR);
	display_background(&data->img);
	display_ray(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.mlx_img, 0, 0);
	return (0);
}
