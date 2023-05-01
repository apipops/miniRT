/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:20:31 by avast             #+#    #+#             */
/*   Updated: 2023/05/01 17:09:07 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/params.h"
#include "../includes/proto.h"
#include "../libft/libft.h"

t_vec3	get_ambiant_light(t_amb_ligth light, t_vec3 obj_col)
{
	return (light.intensity * light.color.xyz * obj_col.xyz);
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
		color.xyz = light.intensity * dot * light.color.xyz * obj_col.xyz;
	return (color);
}
