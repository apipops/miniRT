/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:54:22 by avast             #+#    #+#             */
/*   Updated: 2023/05/02 17:36:05 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/params.h"
#include "../includes/proto.h"
#include "../libft/libft.h"

bool	hit_sphere(t_vec3 cent, double rad, t_ray r, t_vec2 limit, t_hit_rec *rec)
{
	double	a;
	double	half_b;
	double	c;
	double	root;

	a = vec3_dot(r.direction, r.direction);
	half_b = vec3_dot(r.origin.xyz - cent.xyz, r.direction);
	c = vec3_dot(r.origin.xyz - cent.xyz, r.origin.xyz - cent.xyz) - rad * rad;
	if (half_b * half_b - a * c < 0)
		return (false);
	root = (-half_b - sqrt(half_b * half_b - a * c)) / a;
	if (root < limit.x || limit.y < root)
	{
		root = (-half_b + sqrt(half_b * half_b - a * c)) / a;
		if (root < limit.x || limit.y < root)
			return (false);
	}
	set_sphere_hit_rec(r, root, rad, cent, rec);
	return (true);
}

void	set_sphere_hit_rec(t_ray r, double t, double rad, t_vec3 center, t_hit_rec *rec)
{
	t_vec3	outward_normal;

	if (rec)
	{
		rec->t = t;
		rec->p = ray_at(r, t);
		outward_normal = (rec->p.xyz - center.xyz) / rad;
		set_face_normal(r, outward_normal, rec);
	}
}

// tester d'exclure l'objet concerne
bool	hit_sphere_shadow(t_ray r, t_hit_rec rec)
{
	if (rec.obj_id == 2 || rec.obj_id == 3)
	{
		if (hit_sphere((t_vec3){0, 0, -1}, 0.5, r, (t_vec2){0, INFINITY}, NULL))
			return (true);
		else
			return (false);
	}
	else if (rec.obj_id == 1 || rec.obj_id == 3)
	{
		if (hit_sphere((t_vec3){0, -100.5, -1}, 100, r, (t_vec2){0, INFINITY}, NULL))
			return (true);
		else
			return (false);
	}
	return (false);
}
