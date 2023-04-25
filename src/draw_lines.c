/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:27:01 by avast             #+#    #+#             */
/*   Updated: 2023/01/04 15:24:17 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/params.h"
#include "../includes/proto.h"
#include "../libft/libft.h"

void	erline(int v_incr, int er_incr, int *v, int *er)
{
	*v += v_incr;
	*er += er_incr;
}

int	draw_line4(t_img *img, t_coor2d a, t_coor2d b)
{
	int		x;
	int		y;
	int		error;
	t_shade	gap;

	x = a.x;
	y = a.y;
	error = -ft_abs(b.y - a.y);
	while (y != b.y + ft_sign(b.y - a.y))
	{
		gap = calculate_shading(a.col, b.col, ft_abs(b.x - a.x));
		if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
			img_pix_put(img, x, y, get_color(a.col));
		error += 2 * ft_abs(b.x - a.x);
		if (error >= 0)
			erline(ft_sign(b.x - a.x), -2 * ft_abs(b.y - a.y), &x, &error);
		y += ft_sign(b.y - a.y);
		a.col = get_next_color(a.col, gap);
	}
	return (0);
}

int	draw_line3(t_img *img, t_coor2d a, t_coor2d b)
{
	int		x;
	int		y;
	int		error;
	t_shade	gap;

	x = a.x;
	y = a.y;
	if (ft_abs(b.x - a.x) >= ft_abs(b.y - a.y))
	{
		error = -ft_abs(b.x - a.x);
		gap = calculate_shading(a.col, b.col, ft_abs(b.x - a.x));
		while (x != b.x + ft_sign(b.x - a.x))
		{
			if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
				img_pix_put(img, x, y, get_color(a.col));
			error += 2 * ft_abs(b.y - a.y);
			if (error >= 0)
				erline(ft_sign(b.y - a.y), -2 * ft_abs(b.x - a.x), &y, &error);
			x += ft_sign(b.x - a.x);
			a.col = get_next_color(a.col, gap);
		}
	}
	else
		draw_line4(img, a, b);
	return (0);
}

int	draw_line2(t_img *img, t_coor2d a, t_coor2d b)
{
	int		y;
	t_shade	gap;

	y = a.y;
	if (ft_abs(b.x - a.x) == 0)
	{
		gap = calculate_shading(a.col, b.col, ft_abs(b.y - a.y));
		while (y != b.y + ft_sign(b.y - a.y))
		{
			if (a.x > 0 && a.x < WIDTH && y > 0 && y < HEIGHT)
				img_pix_put(img, a.x, y, get_color(a.col));
			y += ft_sign(b.y - a.y);
			a.col = get_next_color(a.col, gap);
		}
	}
	else
		draw_line3(img, a, b);
	return (0);
}

int	draw_line(t_img *img, t_coor2d a, t_coor2d b)
{
	int		x;
	t_shade	gap;

	x = a.x;
	if (ft_abs(b.y - a.y) == 0)
	{
		gap = calculate_shading(a.col, b.col, ft_abs(b.x - a.x));
		while (x != b.x + ft_sign(b.x - a.x))
		{
			if (x > 0 && x < WIDTH && a.y > 0 && a.y < HEIGHT)
				img_pix_put(img, x, a.y, get_color(a.col));
			x += ft_sign(b.x - a.x);
			a.col = get_next_color(a.col, gap);
		}
	}
	else
		draw_line2(img, a, b);
	return (0);
}
