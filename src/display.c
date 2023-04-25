/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:53:19 by avast             #+#    #+#             */
/*   Updated: 2023/04/25 17:43:36 by avast            ###   ########.fr       */
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
			img_pix_put(img, j, i, W);
			j++;
		}
		++i;
	}
}

bool	hit_sphere(t_vec3 center, double radius, t_ray r)
{
	double	a;
	double	half_b;
	double	c;
	t_vec3	oc;

	oc.x = r.origin.x - center.x;
	oc.y = r.origin.y - center.y;
	oc.z = r.origin.z - center.z;
	a = pow(r.direction.x, 2) + pow(r.direction.y, 2) + pow(r.direction.z, 2);
	half_b = oc.x * r.direction.x + oc.x * r.direction.y + oc.z * r.direction.z;
	c = pow(oc.x, 2) + pow(oc.y, 2) + pow(oc.z, 2) - pow(radius, 2);
	return (half_b * half_b - a * c < 0);
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
			u = i / (WIDTH - 1);
			v = j / (HEIGHT - 1);
			r.direction.x = data->lower_left_corner.x + u * data->horizontal.x + v * data->vertical.x - data->origin.x;
			r.direction.y = data->lower_left_corner.y + u * data->horizontal.y + v * data->vertical.y - data->origin.y;
			r.direction.z = data->lower_left_corner.z + u * data->horizontal.z + v * data->vertical.z - data->origin.z;
			if (hit_sphere((t_vec3){0, 0, -1}, 0.5, r))
				img_pix_put(&data->img, j, i, RED_PIXEL);
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
