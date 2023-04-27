/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:48:17 by avast             #+#    #+#             */
/*   Updated: 2023/04/27 15:03:22 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/params.h"
#include "../includes/proto.h" 
#include "../libft/libft.h"

double	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	vec3_unit_vector(t_vec3 a)
{
	double	length;

	length = sqrt(vec3_dot(a, a));
	return (a.xyz / length);
}

/* 
t_vec3	vec3_mult(t_vec3 vec, double a)
{
	t_vec3	result;

	result.x = a * vec.x;
	result.y = a * vec.y;
	result.z = a * vec.z;
	//result.xyz = a * vec.yxz
	return (result);
}

t_vec3	vec3_div(t_vec3 vec, double a)
{
	t_vec3	result;

	result.x = vec.x / a;
	result.y = vec.y / a;
	result.z = vec.z / a;
	//result.xyz = vec.xyz / a;
	return (result);
}

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
} */

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	//result.xyz = a.yzx * b.zxy - a.zxy * b.yzx;
	return (result);
}
