/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:00:40 by avast             #+#    #+#             */
/*   Updated: 2023/04/25 17:34:46 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H

t_vec3		calculate_lower_left_corner(t_data data);
int			close_window(t_data *data);
int			display(t_data *data);
void		display_background(t_img *img);
void		display_ray(t_data *data);
int			handle_keypress(int keysym, t_data *data);
bool		hit_sphere(t_vec3 center, double radius, t_ray r);
void		img_pix_put(t_img *img, int x, int y, int color);


#endif