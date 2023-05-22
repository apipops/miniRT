/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cones.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:54:22 by avast             #+#    #+#             */
/*   Updated: 2023/05/12 15:25:23 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "params.h"
#include "proto.h"

static void	solve_cone_equa(t_objects co, t_ray r, float *r1, float *r2)
{
	float	w;
	t_vec3	va;
	t_vec3	ra0;
	float	vs;
	t_equa	equa;

	w = co.height - vec3_dot(r.origin.xyz - co.origin.xyz, co.dir);
	ra0 = vec3_cross(vec3_cross(co.dir, r.origin.xyz - co.origin.xyz), co.dir);
	va = vec3_cross(vec3_cross(co.dir, r.direction), co.dir);
	vs = vec3_dot(r.direction, co.dir);
	equa.a = vec3_dot(va, va) - powf(vs, 2) * (powf(co.radius, 2)
			/ powf(co.height, 2));
	equa.b = 2 * vec3_dot(ra0, va) + 2 * w * vs * (powf(co.radius, 2)
			/ powf(co.height, 2));
	equa.c = vec3_dot(ra0, ra0) - w * w * (powf(co.radius, 2)
			/ powf(co.height, 2));
	equa.delta = equa.b * equa.b - 4 * equa.a * equa.c;
	if (equa.delta < 0)
	{
		*r1 = -1;
		*r2 = -1;
		return ;
	}
	*r1 = (-equa.b - sqrtf(equa.delta)) / (2 * equa.a);
	*r2 = (-equa.b + sqrtf(equa.delta)) / (2 * equa.a);
}

static float	hit_cone_cap(t_objects cone, t_ray r, t_vec2 limit)
{
	t_vec3	normal;
	float	root;

	normal = cone.dir;
	if (vec3_dot(normal, r.direction) == 0)
		return (-1);
	root = vec3_dot(cone.origin.xyz - r.origin.xyz, normal)
		/ vec3_dot(normal, r.direction);
	if (root == 0 || root < limit.x || limit.y < root)
		return (-1);
	if (vec3_dot(ray_at(r, root).xyz - cone.origin.xyz,
			ray_at(r, root).xyz - cone.origin.xyz)
		<= cone.radius * cone.radius)
		return (root);
	else
		return (-1);
}

static float	min_positive(float a, float b, float c)
{
	float	min_pos;

	min_pos = -1;
	if (a > 0 && (a < min_pos || min_pos == -1))
		min_pos = a;
	if (b > 0 && (b < min_pos || min_pos == -1))
		min_pos = b;
	if (c > 0 && (c < min_pos || min_pos == -1))
		min_pos = c;
	return (min_pos);
}

static void	set_cone_rec(t_ray r, float roots[3], t_objects co, t_hit_rec *rec)
{
	t_vec3	projection;
	t_vec3	closest;
	t_vec3	dot;

	if (rec)
	{
		rec->obj_id = co.id;
		rec->obj_color = co.colors;
		rec->t = min_positive(roots[0], roots[1], roots[2]);
		rec->p = ray_at(r, rec->t);
		if (rec->t == roots[0] || rec->t == roots[1])
		{
			projection = vec3_dot(rec->p.xyz - co.origin.xyz, co.dir)
				* co.dir.xyz;
			closest = projection.xyz + co.origin.xyz;
			dot = vec3_dot(rec->p.xyz - closest.xyx, co.dir) * co.dir.xyz;
			rec->normal = vec3_normalize(rec->p.xyz - closest.xyz - dot.xyz);
		}
		else
			set_face_normal(r, co.dir, rec);
	}
}

bool	hit_cone(t_objects cone, t_ray r, t_vec2 limit, t_hit_rec *rec)
{
	float	roots[3];
	float	dot[2];

	solve_cone_equa(cone, r, &roots[0], &roots[1]);
	if (roots[0] < limit.x || roots[0] > limit.y)
		roots[0] = -1;
	if (roots[1] < limit.x || roots[1] > limit.y)
		roots[1] = -1;
	dot[0] = vec3_dot(ray_at(r, roots[0]).xyz - cone.origin.xyz, cone.dir);
	dot[1] = vec3_dot(ray_at(r, roots[1]).xyz - cone.origin.xyz, cone.dir);
	if (dot[0] < 0 || dot[0] > cone.height)
		roots[0] = -1;
	if (dot[1] < 0 || dot[1] > cone.height)
		roots[1] = -1;
	roots[2] = hit_cone_cap(cone, r, limit);
	if (roots[0] < 0 && roots[1] < 0 && roots[2] < 0)
		return (false);
	set_cone_rec(r, roots, cone, rec);
	return (true);
}
