/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:53:19 by avast             #+#    #+#             */
/*   Updated: 2023/04/27 11:48:19 by avast            ###   ########.fr       */
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
	t_vec3		normal;
	double		t;
	t_hit_rec	rec;

	if (hit_anything(r, limit, &rec))
	{
		normal.x = 255.999 * (0.5 * (rec.normal.x + 1));
		normal.y = 255.999 * (0.5 * (rec.normal.y + 1));
		normal.z = 255.999 * (0.5 * (rec.normal.z + 1));
	}
	else
	{
		normal = vec3_unit_vector(r.direction);
		t = 0.5 * (normal.y + 1);
		normal.x = 255.999 * ((1 - t) + (t * 0.5));
		normal.y = 255.999 * ((1 - t) + (t * 0.7));
		normal.z = 255.999 * ((1 - t) + (t * 1));
	}
	return (get_color(normal));
}

void	set_face_normal(t_ray r, t_vec3 out_normal, t_hit_rec *rec)
{
	rec->front_face = (vec3_dot(r.direction, out_normal) < 0);
	if (rec->front_face)
		rec->normal = out_normal;
	else
		rec->normal = vec3_mult(out_normal, -1);
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
	if (hit_sphere((t_vec3){0, -100.5, -1}, 100, r, (t_vec2){limit.x, closest_so_far}, &temp_rec))
	{
		hit_anything = true;
		closest_so_far = temp_rec.t;
		*rec = temp_rec;
	}
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
