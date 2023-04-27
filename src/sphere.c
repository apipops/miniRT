/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:54:22 by avast             #+#    #+#             */
/*   Updated: 2023/04/27 11:35:54 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/params.h"
#include "../includes/proto.h"
#include "../libft/libft.h"

bool	hit_sphere(t_vec3 center, double radius, t_ray r, t_vec2 limit, t_hit_rec *rec)
{
	t_vec3	oc;
	double	a;
	double	half_b;
	double	c;
	double	root;
	t_vec3	out_normal;

	/*oc = r.origin - center */
	oc = vec3_sub(r.origin, center);
	a = vec3_dot(r.direction, r.direction);
	half_b = vec3_dot(oc, r.direction);
	c = vec3_dot(oc, oc) - radius * radius;
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
 	rec->t = root;
	rec->p = vec3_at(r, root);
	out_normal = vec3_div(vec3_sub(rec->p, center), radius);
	set_face_normal(r, out_normal, rec);
	return (true);
}
