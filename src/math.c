/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 18:29:27 by avast             #+#    #+#             */
/*   Updated: 2023/04/27 17:21:28 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/params.h"
#include "../includes/proto.h"
#include "../libft/libft.h"

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

double	ft_clamp(double x, double min, double max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}
