/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:48:17 by avast             #+#    #+#             */
/*   Updated: 2023/05/02 11:41:15 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/params.h"
#include "../includes/proto.h" 
#include "../libft/libft.h"

double	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

/* double	vec3_distance(t_vec3 a, t_vec3 b)
{
	return (sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2)))
} */

t_vec3	vec3_normalize(t_vec3 a)
{
	double	length;

	length = sqrt(vec3_dot(a, a));
	return (a.xyz / length);
}

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	return (a.yzx * b.zxy - a.zxy * b.yzx);
}
