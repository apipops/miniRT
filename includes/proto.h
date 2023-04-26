/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:00:40 by avast             #+#    #+#             */
/*   Updated: 2023/04/26 14:40:39 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H

t_vec3	calculate_lower_left_corner(t_data data);
int		close_window(t_data *data);
int		display(t_data *data);
void	display_background(t_img *img);
void	display_ray(t_data *data);
int		handle_keypress(int keysym, t_data *data);
double	hit_sphere(t_vec3 center, double radius, t_ray r);
void	img_pix_put(t_img *img, int x, int y, int color);

/* VEC3 UTILS*/
double	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_unit_vector(t_vec3 a);
t_vec3	vec3_mult(t_vec3 vec, double a);
t_vec3	vec3_div(t_vec3 vec, double a);
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
t_vec3	vec3_at(t_ray ray, double t);

/* SHADING */
int	get_color(t_vec3 color);
int	define_color(t_ray r, double t);

#endif