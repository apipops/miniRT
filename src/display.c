/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:53:19 by avast             #+#    #+#             */
/*   Updated: 2023/04/27 18:04:18 by avast            ###   ########.fr       */
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

int	define_color(t_ray r, t_vec2 limit)
{
	t_vec3		init_color;
	t_vec3		light_origin;
	t_vec3		l_vector;
	t_vec3		color;
	double		t;
	t_hit_rec	rec;

	init_color = (t_vec3){1, 0, 0};
	light_origin = (t_vec3){-2, 2, -1};
	if (hit_anything(r, limit, &rec))
	{
		// Position de l'objet ou de la camera ou rec.t ou rec.p ?
		// Position de la surface
		l_vector.xyz = vec3_unit_vector(light_origin.xyz - rec.p);
		//color.xyz = 0.5 * (rec.normal.xyz + 1);
/* 		if (vec3_dot(rec.normal, l_vector) >= 0)
			color.xyz = 0;
		else */
 			color.xyz = 1 * ft_abs(vec3_dot(rec.normal, l_vector)) * (t_vec3){0.75, 0, 1};
	}
	else
	{
 		color = vec3_unit_vector(r.direction);
		t = 0.5 * (color.y + 1);
		color.x = (1 - t) + (t * 0.5);
		color.y = (1 - t) + (t * 0.7);
		color.z = (1 - t) + (t * 1);
	}
	return (get_color(color));
}

bool	hit_anything(t_ray r, t_vec2 limit, t_hit_rec *rec)
{
	double		closest_so_far;
	bool		hit_anything;
	t_hit_rec	temp_rec;

	hit_anything = false;
	closest_so_far = limit.y;
	if (hit_sphere((t_vec3){0, 0, -1}, 0.5, r, (t_vec2){limit.x, closest_so_far}, &temp_rec))
	{
		hit_anything = true;
		closest_so_far = temp_rec.t;
		*rec = temp_rec;
	}
/* 	if (hit_sphere((t_vec3){0, -100.5, -1}, 100, r, (t_vec2){limit.x, closest_so_far}, &temp_rec))
	{
		hit_anything = true;
		closest_so_far = temp_rec.t;
		*rec = temp_rec;
	} */
	return (hit_anything);
}


void	display_ray(t_data *data)
{
	int			j;
	int			i;
	double		u;
	double		v;
	t_ray		r;
	int			color;

	j = 0;
	while (j < HEIGHT)
	{
		i = 0;
		while (i < WIDTH)
		{
			u = (double)i / (WIDTH - 1);
			v = (double)j / (HEIGHT - 1);
			r = get_ray(u, v, *data);
			color = define_color(r, (t_vec2){0, INFINITY});
			img_pix_put(&data->img, i, HEIGHT - j - 1, color);
			i++;
		}
		j++;
	}
}

int	display(t_data *data)
{
	if (data->win_ptr == NULL)
		return (MLX_ERROR);
	//display_background(&data->img);
	display_ray(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.mlx_img, 0, 0);
	return (0);
}
