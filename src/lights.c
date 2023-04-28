/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:20:31 by avast             #+#    #+#             */
/*   Updated: 2023/04/28 13:11:36 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/params.h"
#include "../includes/proto.h"
#include "../libft/libft.h"

t_vec3	get_direct_light(t_hit_rec rec, t_dir_ligth light, t_vec3 obj_col)
{
	t_vec3	directional_light;
	double	dot_produt;
	t_vec3	color;

	directional_light.xyz = vec3_unit_vector(light.position.xyz - rec.p.xyz);
	dot_produt = vec3_dot(rec.normal, directional_light);
	if (dot_produt < 0)
		color.xyz = 0;
	else
		color.xyz = light.intensity * dot_produt * (light.color.xyz + obj_col.xyz);
	return (color);
}
