/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:38:13 by avast             #+#    #+#             */
/*   Updated: 2023/04/26 15:21:00 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/params.h"
#include "../includes/proto.h"
#include "../libft/libft.h"

/* t_shade	read_shade(char *str)
{
	int		i;
	t_shade	color;

	i = 0;
	color = (t_shade){0, 0, 0};
	while (str[i] && str[i] != 32 && str[i] != 10 && str[i] != 9)
		i++;
	if (i <= 5)
	{
		color.b = ft_atoi_hexa(str + 3);
	}
	else if (i > 5 && i <= 7)
	{
		color.g = ft_atoi_hexa(str + 3);
		color.b = ft_atoi_hexa(str + 5);
	}
	else
	{
		color.r = ft_atoi_hexa(str + 3);
		color.g = ft_atoi_hexa(str + 5);
		color.b = ft_atoi_hexa(str + 7);
	}
	return (color);
}

t_shade	get_opp_color(t_shade color)
{
	t_shade	new_color;

	new_color.r = 255 - color.r;
	new_color.g = 255 - color.g;
	new_color.b = 255 - color.b;
	return (new_color);
} */

int	get_color(t_vec3 color)
{
	int	new_color;

	new_color = (((int)color.x & 0x0ff) << 16)
		| (((int)color.y & 0x0ff) << 8) | ((int)color.z & 0x0ff);
	return (new_color);
}

/* t_shade	calculate_shading(t_shade a, t_shade b, int gap)
{
	t_shade	color_gap;

	if (gap)
	{
		color_gap.r = (b.r - a.r) / gap;
		color_gap.g = (b.g - a.g) / gap;
		color_gap.b = (b.b - a.b) / gap;
	}
	else
		color_gap = (t_shade){0, 0, 0};
	return (color_gap);
}

t_shade	get_next_color(t_shade color, t_shade gap)
{
	color.r += gap.r;
	color.g += gap.g;
	color.b += gap.b;
	if (color.r > 255)
		color.r = 255;
	if (color.r < 0)
		color.r = 0;
	if (color.g > 255)
		color.g = 255;
	if (color.g < 0)
		color.g = 0;
	if (color.b > 255)
		color.b = 255;
	if (color.b < 0)
		color.b = 0;
	return (color);
}
 */