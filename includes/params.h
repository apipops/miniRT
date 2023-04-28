/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:54:19 by avast             #+#    #+#             */
/*   Updated: 2023/04/28 14:35:10 by avast            ###   ########.fr       */
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
# include <stdbool.h>

/* A commenter pour macos */
# include <X11/X.h>
# include <X11/keysym.h>

/* A decommenter pour macos */
/* # define XK_space 49
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
# define ButtonPressMask (1L<<2) */

# define WIDTH 1000
# define HEIGHT 600

# define MLX_ERROR 1

# define RED 0xFF0000
# define GREEN 0xFF00
# define WHITE 0xFFFFFF
# define BLACK 0x000000

typedef double	t_vec3	__attribute__((ext_vector_type(3)));
typedef double	t_vec2	__attribute__((ext_vector_type(2)));

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;


typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

typedef struct s_dir_ligth
{
	t_vec3	position;
	double	intensity;
	t_vec3	color;
}	t_dir_ligth;

typedef struct s_amb_light
{
	double	intensity;
	t_vec3	color;
}	t_amb_ligth;

typedef struct s_hit_record
{
	t_vec3	p;
	t_vec3	normal;
	double	t;
	bool	front_face;
}	t_hit_rec;

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
	t_vec3		corner;
}	t_data;

#endif