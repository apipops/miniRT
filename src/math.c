/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 18:29:27 by avast             #+#    #+#             */
/*   Updated: 2023/05/03 12:40:37 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/params.h"
#include "../includes/proto.h"
#include "../libft/libft.h"

double	deg_to_rad(double a)
{
	return (a / 180 * 3.14159265);
}

double	cal_cos(int a)
{
	return (cos(0.0174533 * a));
}

double	cal_sin(int a)
{
	return (sin(0.0174533 * a));
}

double	ft_abs(double a)
{
	if (a < 0)
		return (-a);
	return (a);
}

int	ft_sign(int a)
{
	if (a < 0)
		return (-1);
	else if (a > 0)
		return (1);
	return (0);
}
