/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:53:19 by avast             #+#    #+#             */
/*   Updated: 2023/04/26 16:47:44 by avast            ###   ########.fr       */
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
			img_pix_put(img, j, i, BLACK);
			j++;
		}
		++i;
	}
}

double	hit_sphere(t_vec3 center, double radius, t_ray r)
{
	t_vec3	oc;
	double	a;
	double	half_b;
	double	c;
	//t_vec3	normal;
	//double	root;

	/*oc = r.origin - center */
	oc = vec3_sub(r.origin, center);
	a = vec3_dot(r.direction, r.direction);
	half_b = vec3_dot(oc, r.direction);
	c = vec3_dot(oc, oc) - radius * radius;
 	if (half_b * half_b - a * c < 0)
		return (-1);
	else
		return ((-half_b - sqrt(half_b * half_b - a * c)) / a);
	/* Calcul normal */

	/* trouver le nearest root that lies in the acceptable range */
/* 	root = (-half_b - sqrt(half_b * half_b - a * c)) / a;
	if (root < max.x || max.y < root)
	{
		root = (-half_b + sqrt(half_b * half_b - a * c)) / a;
		if (root < max.x || max.y < root)
			return (false);
	} */
	/* Enregistrer les donnees */
/* 	t = root;
	p = r.origin + root * r.direction;
	normal = (p - center) / radius; */
}

int	define_color(t_ray r, double t)
{
	t_vec3	normal;

	normal = vec3_unit_vector(vec3_sub(vec3_at(r, t), (t_vec3){0, 0, -1}));
	normal.x = 255.999 * (0.5 * (normal.x + 1));
	normal.y = 255.999 * (0.5 * (normal.y + 1));
	normal.z = 255.999 * (0.5 * (normal.z + 1));
	return (get_color(normal));
}

int	define_background_color(t_ray r)
{
	t_vec3	normal;
	double	t;

	normal = vec3_unit_vector(r.direction);
	t = 0.5 * (normal.y + 1);
	normal.x = 255.999 * ((1 - t) + (t * 0.5));
	normal.y = 255.999 * ((1 - t) + (t * 0.7));
	normal.z = 255.999 * ((1 - t) + (t * 1));
	return (get_color(normal));
}

void	display_ray(t_data *data)
{
	int		j;
	int		i;
	double	u;
	double	v;
	t_ray	r;
	double	t;

	r.origin = data->origin;
	j = 0;
	while (j < HEIGHT)
	{
		i = 0;
		while (i < WIDTH)
		{
			u = (double)i / (WIDTH - 1);
			v = (double)j / (HEIGHT - 1);
			r.direction.x = data->lower_left_corner.x + u * data->horizontal.x + v * data->vertical.x - data->origin.x;
			r.direction.y = data->lower_left_corner.y + u * data->horizontal.y + v * data->vertical.y - data->origin.y;
			r.direction.z = data->lower_left_corner.z + u * data->horizontal.z + v * data->vertical.z - data->origin.z;
			t = hit_sphere((t_vec3){0, 0, -1}, 0.5, r);
			if (t == -1)
				img_pix_put(&data->img, i, HEIGHT - j - 1, define_background_color(r));
			else
				img_pix_put(&data->img, i, HEIGHT - j - 1, define_color(r, t));
			i++;
		}
		j++;
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
