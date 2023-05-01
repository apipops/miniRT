/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:54:22 by avast             #+#    #+#             */
/*   Updated: 2023/05/01 15:28:47 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/params.h"
#include "../includes/proto.h"
#include "../libft/libft.h"

bool	hit_sphere(t_vec3 center, double radius, t_ray r, t_vec2 limit, t_hit_rec *rec)
{
	//t_vec3	oc;
	double	a;
	double	half_b;
	double	c;
	double	root;
	t_vec3	out_normal;

	/*oc = r.origin - center */
	//oc = vec3_sub(r.origin, center);
	a = vec3_dot(r.direction, r.direction);
	half_b = vec3_dot(r.origin.xyz - center.xyz, r.direction);
	c = vec3_dot(r.origin.xyz - center.xyz, r.origin.xyz - center.xyz) - radius * radius;
	if (half_b * half_b - a * c < 0)
		return (false);
	/* Voir la racine la plus proche qui entre dans les limites */
	root = (-half_b - sqrt(half_b * half_b - a * c)) / a;
	if (root < limit.x || limit.y < root)
	{
		root = (-half_b + sqrt(half_b * half_b - a * c)) / a;
		if (root < limit.x || limit.y < root)
			return (false);
	} 
	/* Enregistrer les donnees du hit record */
	if (rec)
	{
		rec->t = root;
		rec->p = ray_at(r, root);
		out_normal = (rec->p.xyz - center.xyz) / radius;
		set_face_normal(r, out_normal, rec);
	}
	return (true);
}

// tester d'exclure l'objet concerne
bool	hit_sphere_shadow(t_ray r, t_hit_rec rec)
{
	if (rec.obj_id == 2)
	{
		if (hit_sphere((t_vec3){0, 0, -1}, 0.5, r, (t_vec2){0, INFINITY}, NULL))
			return (true);
		else
			return (false);
	}
	else
	{
		if (hit_sphere((t_vec3){0, -100.5, -1}, 100, r, (t_vec2){0, INFINITY}, NULL))
			return (true);
		else
			return (false);
	}
}
