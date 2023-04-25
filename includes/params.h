/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:54:19 by avast             #+#    #+#             */
/*   Updated: 2023/04/25 16:51:21 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARAMS_H
# define PARAMS_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <math.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <mlx.h>
# include <errno.h>
/* # include <X11/X.h>
# include <X11/keysym.h> */

# define XK_space 49
# define XK_2 19
# define XK_1 18
# define XK_c 8
# define XK_Escape 53
# define XK_Up 126
# define XK_Down 125
# define XK_Left 123
# define XK_Right 124
# define XK_w 13
# define XK_s 1
# define XK_d 2 
# define XK_a 0
# define KeyPress 02
# define KeyPressMask (1L<<0)
# define ButtonPress 04
# define ButtonPressMask (1L<<2)

# define WIDTH 600
# define HEIGHT 300

# define MLX_ERROR 1

# define RED_PIXEL 0xFF0000
# define GREEN_PIXEL 0xFF00
# define W 0xFFFFFF
# define BLACK 0x000000

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_shade
{
	float	r;
	float	g;
	float	b;
}	t_shade;

typedef struct s_altcol
{
	int		z;
	t_shade	color;
}	t_altcol;

typedef struct s_coor3d
{
	float		x;
	float		y;
	t_altcol	alt;
}	t_coor3d;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

typedef struct s_coor2d
{
	int		x;
	int		y;
	t_shade	col;
}	t_coor2d;

typedef struct s_size2d
{
	int	x;
	int	y;
}	t_size2d;

typedef struct s_params
{
	int			a1;
	int			a2;
	t_size2d	cent;
	float		tsize;
	float		alti;
	int			type;
	int			color;
}	t_params;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	double		aspect_ratio;
	double		viewport_height;
	double		viewport_width;
	double		focal_length;
	t_vec3		origin;
	t_vec3		horizontal;
	t_vec3		vertical;
	t_vec3		lower_left_corner;
}	t_data;

#endif