/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:13:35 by avast             #+#    #+#             */
/*   Updated: 2023/05/03 12:48:10 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/params.h"
#include "../includes/proto.h"
#include "../libft/libft.h"

static int	get_color(t_vec3 color)
{
	int		new_color;

	color.xyz *= 255.999;
	if (color.x > 255)
		color.x = 255;
	if (color.y > 255)
		color.y = 255;
	if (color.z > 255)
		color.z = 255;
	new_color = (((int)color.x & 0x0ff) << 16)
		| (((int)color.y & 0x0ff) << 8) | ((int)color.z & 0x0ff);
	return (new_color);
}

static void	save_rec(double *closest, t_hit_rec tmp, t_hit_rec *rec, bool *hit)
{
	*hit = true;
	if (rec)
	{
		*closest = tmp.t;
		*rec = tmp;
	}
}

bool	hit_anything(t_ray r, t_elements elem, t_hit_rec *rec, int obj_excluded)
{
	double		closest;
	bool		hit_anything;
	t_hit_rec	tmp_rec;
	t_objects	*obj;

	closest = INFINITY;
	hit_anything = false;
	obj = elem.objects_head;
	while (obj)
	{
		if (obj->id != obj_excluded && obj->type == SPHERE
			&& hit_sphere(*obj, r, (t_vec3){0, closest}, &tmp_rec))
			save_rec(&closest, tmp_rec, rec);
		if (obj->id != obj_excluded && obj->type == PLANE
			&& hit_plane(*obj, r, (t_vec3){0, closest}, &tmp_rec))
			save_rec(&closest, tmp_rec, rec);
		// dans la cas ou on cherche une ombre, on peut sortir
		if (obj_excluded >= 0 && hit_anything)
			break ;
		obj = obj->next;
	}
	return (hit_anything);
}




t_vec3	update_color_shadow(t_hit_rec rec, t_elements elem)
{
	t_light	*light;
	t_vec3	color;
	int		light_count;
	t_ray	shadow_ray;

	light = elem.lights_head;
	color = (t_vec3){0, 0, 0};
	light_count = 0;
	while (light)
	{
		shadow_ray = get_shadow_ray(rec, *light);
		if (!hit_anything(shadow_ray, (t_vec3){0, INFINITY}, NULL, rec.obj_id))
		{
			light_count++;
			color.xyz += get_direct_light(rec, light, rec.obj_color);
			color.xyz += get_spec_light(*elem.camera, light, rec.obj_color);
		}
		light = light->next;
	}
	if (light_count > 0)
		color.xyz /= light_count;
	color.xyz += get_ambient_light(*elem.ambient, rec.obj_color);
	return (color.xyz / 3);
}

int	define_color(t_data *data, t_ray r)
{
	t_vec3		color;
	t_hit_rec	rec;

/* 	dir_light.position = (t_vec3){30, 2, -1};
	dir_light.color = (t_vec3){0, 0, 1};
	dir_light.intensity = 1;
	dir_light2.position = (t_vec3){-70, 50, -1};
	dir_light2.color = (t_vec3){1, 0, 0};
	dir_light2.intensity = 1;
	amb_light.color = (t_vec3){1, 1, 1};
	amb_light.intensity = 0.5;
	obj_color = (t_vec3){1, 1, 1}; */

	if (hit_anything(r, data->elements, &rec, ALL_OBJ))
		color = update_color_shadow(rec, data->elements);
	else
		color.xyz = get_ambient_light(*data->elements.ambient,
				rec.obj_color).xyz / 3;
	return (get_color(color));
}

/* bool	hit_anything(t_ray r, t_vec2 limit, t_hit_rec *rec)
{
	double		closest_so_far;
	bool		hit_anything;
	t_hit_rec	temp_rec;

	hit_anything = false;
	closest_so_far = limit.y;
	if (hit_sphere((t_vec3){0, 0, -1}, 0.5, r, (t_vec2){limit.x, closest_so_far}, &temp_rec))
	{
		hit_anything = true;
		if (rec) // cas ou on calcule un rayon et non pas un shadow rayon
		{
			temp_rec.obj_id = 1;
			closest_so_far = temp_rec.t;
				*rec = temp_rec;
		}
	}
   	if (hit_sphere((t_vec3){0, -100.5, -1}, 100, r, (t_vec2){limit.x, closest_so_far}, &temp_rec))
	{
		hit_anything = true;
		if (rec) // cas ou on calcule un rayon et non pas un shadow rayon
		{
			temp_rec.obj_id = 2;
			closest_so_far = temp_rec.t;
				*rec = temp_rec;
		}
	}
	if (hit_plan((t_vec3){0, -1, -1}, (t_vec3){1, -5, 0}, r, (t_vec2){limit.x, closest_so_far}, &temp_rec))
	{
		hit_anything = true;
		if (rec) // cas ou on calcule un rayon et non pas un shadow rayon
		{
			temp_rec.obj_id = 3;
			closest_so_far = temp_rec.t;
				*rec = temp_rec;
		}
	}
	return (hit_anything);
} */