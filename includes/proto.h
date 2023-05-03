/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:00:40 by avast             #+#    #+#             */
/*   Updated: 2023/05/03 12:47:19 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H

t_vec3	calculate_corner(t_data data);

/* DISPLAY */
int		display(t_data *data);
void	display_ray(t_data *data);
void	img_pix_put(t_img *img, int x, int y, int color);

/* HOOKS */
int		close_window(t_data *data);
int		handle_keypress(int keysym, t_data *data);

/* RAYTRACING */
int		define_color(t_data *data, t_ray r);
bool	hit_anything(t_ray r, t_elements elem, t_hit_rec *rec, int exclu);
t_vec3	update_color_shadow(t_hit_rec rec, t_elements elem);

/* LIGTHS */
t_vec3	get_ambient_light(t_ambient ambient, t_vec3	obj_color);
t_vec3	get_direct_light(t_hit_rec rec, t_light light, t_vec3 obj_color);
t_vec3	get_spec_light(t_camera c, t_hit_rec rec, t_light light, t_vec3	col);

/* SPHERE */
bool	hit_sphere(t_objects sphere, t_ray r, t_vec2 limit, t_hit_rec *rec);
void	set_sphere_hit_rec(t_ray r, double t, t_objects sphere, t_hit_rec *rec);
bool	hit_sphere_shadow(t_ray r, t_hit_rec rec);

/* PLAN */
bool	hit_plane(t_objects plane, t_ray r, t_vec2 limit, t_hit_rec *rec);

/* MATH */
double	cal_cos(int a);
double	cal_sin(int a);
double	deg_to_rad(double a);
double	ft_abs(double a);
int		ft_sign(int a);

/* VEC3 UTILS*/
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
double	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_normalize(t_vec3 a);

/* RAY UTILS*/
t_ray	get_ray(double u, double v, t_data data);
t_ray	get_shadow_ray(t_hit_rec rec, t_light light);
t_vec3	ray_at(t_ray ray, double t);
void	set_face_normal(t_ray r, t_vec3 out_normal, t_hit_rec *rec);




#endif