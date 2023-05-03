/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:59:55 by avast             #+#    #+#             */
/*   Updated: 2023/05/03 16:26:39 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/params.h"
#include "../includes/proto.h"
#include "../libft/includes/libft.h"

t_ray	get_ray(float u, float v, t_data data)
{
	t_ray	ray;

	ray.origin = data.origin;
	ray.direction.xyz = vec3_normalize(data.corner.xyz + u * data.horizontal.xyz
			+ v * data.vertical.xyz - data.origin.xyz);
	return (ray);
}

t_ray	get_shadow_ray(t_hit_rec rec, t_light light)
{
	t_ray	ray;

	ray.origin = rec.p;
	ray.direction = vec3_normalize(light.origin - rec.p);
	return (ray);
}

t_vec3	ray_at(t_ray ray, float t)
{
	return (ray.origin.xyz + t * ray.direction.xyz);
}

void	set_face_normal(t_ray r, t_vec3 out_normal, t_hit_rec *rec)
{
	rec->front_face = (vec3_dot(r.direction, out_normal) < 0);
	if (rec->front_face)
		rec->normal = out_normal;
	else
		rec->normal = out_normal.xyz * -1;
}
