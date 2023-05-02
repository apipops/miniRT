/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:20:31 by avast             #+#    #+#             */
/*   Updated: 2023/05/02 12:22:14 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/params.h"
#include "../includes/proto.h"
#include "../libft/libft.h"

t_vec3	get_ambiant_light(t_amb_ligth light, t_vec3 obj_col)
{
	return (light.intensity * (light.color.xyz + obj_col.xyz));
}

t_vec3	get_direct_light(t_hit_rec rec, t_dir_ligth light, t_vec3 obj_col)
{
	t_vec3	directional_light;
	double	dot;
	t_vec3	color;

	directional_light.xyz = vec3_normalize(light.position.xyz - rec.p.xyz);
	dot = vec3_dot(rec.normal, directional_light);
	if (dot < 0)
		color.xyz = 0;
	else
		color.xyz = light.intensity * dot * (light.color.xyz + obj_col.xyz);
	return (color);
}

// Couleur de la lumiere + Portien de reflexion platique + Rugosite de la surface
t_vec3	get_spec_light(t_vec3 camera, t_hit_rec rec, t_dir_ligth light, t_vec3 obj_col)
{
	t_vec3	dir_l;
	t_vec3	ref_l;
	double	dot;
	t_vec3	color;

	dir_l = vec3_normalize(light.position.xyz - rec.p.xyz);
	ref_l.xyz = vec3_normalize(-dir_l.xyz + 2 * vec3_dot(dir_l, rec.normal)
			* rec.normal.xyz);
	dot = vec3_dot(ref_l, vec3_normalize(camera.xyz - rec.p.xyz));
	if (dot < 0)
		color.xyz = 0;
	else
		color.xyz = light.intensity * pow(dot, 23) * (light.color.xyz + ((1 - 0.5)
			* obj_col.xyz + 0.5));
	return (color);
}
