/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:00:40 by avast             #+#    #+#             */
/*   Updated: 2023/04/28 14:20:31 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H

t_vec3	calculate_corner(t_data data);
int		close_window(t_data *data);
int		display(t_data *data);
void	display_background(t_img *img);
void	display_ray(t_data *data);
int		handle_keypress(int keysym, t_data *data);
void	img_pix_put(t_img *img, int x, int y, int color);
bool	hit_anything(t_ray r, t_vec2 limit, t_hit_rec *rec);


/* MATH */
double	cal_cos(int a);
double	cal_sin(int a);
double	ft_abs(double a);
int		ft_sign(int a);
double	ft_positive(double x);
double	deg_to_rad(double a);

/* VEC3 UTILS*/
double	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_unit_vector(t_vec3 a);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);

/* RAY UTILS*/
void	set_face_normal(t_ray r, t_vec3 out_normal, t_hit_rec *rec);
t_vec3	ray_at(t_ray ray, double t);
t_ray	get_ray(double u, double v, t_data data);

/* SHADING */
int		get_color(t_vec3 color);
int		define_color(t_ray r, t_vec2 limit);

/* SPHERE */
bool	hit_sphere(t_vec3 center, double rad, t_ray r, t_vec2 limit, t_hit_rec *rec);

/* LIGTHS */
t_vec3	get_direct_light(t_hit_rec rec, t_dir_ligth light, t_vec3 obj_col);


#endif