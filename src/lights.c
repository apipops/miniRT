/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:20:31 by avast             #+#    #+#             */
/*   Updated: 2023/05/03 12:25:16 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/params.h"
#include "../includes/proto.h"
#include "../libft/libft.h"

t_vec3	get_ambient_light(t_ambient ambient, t_vec3 obj_color)
{
	return (ambient.ratio * (ambient.colors.xyz + obj_color.xyz));
}

t_vec3	get_direct_light(t_hit_rec rec, t_light light, t_vec3 obj_color)
{
	t_vec3	directional_light;
	double	dot;
	t_vec3	color;

	directional_light.xyz = vec3_normalize(light.origin.xyz - rec.p.xyz);
	dot = vec3_dot(rec.normal, directional_light);
	if (dot < 0)
		color.xyz = 0;
	else
		color.xyz = light.ratio * dot * (light.colors.xyz + obj_color.xyz);
	return (color);
}

// Couleur de la lumiere + Portien de reflexion platique + Rugosite de la surface
t_vec3	get_spec_light(t_camera cam, t_hit_rec rec, t_light light, t_vec3 o_col)
{
	t_vec3	dir_l;
	t_vec3	ref_l;
	double	dot;
	t_vec3	color;

	dir_l = vec3_normalize(light.origin.xyz - rec.p.xyz);
	ref_l.xyz = vec3_normalize(-dir_l.xyz + 2 * vec3_dot(dir_l, rec.normal)
			* rec.normal.xyz);
	dot = vec3_dot(ref_l, vec3_normalize(cam.origin.xyz - rec.p.xyz));
	if (dot < 0)
		color.xyz = 0;
	else
		color.xyz = light.ratio * pow(dot, 23) * (o_col.xyz + ((1 - 0.5)
					* o_col.xyz + 0.5));
	return (color);
}
