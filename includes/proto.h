/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:00:40 by avast             #+#    #+#             */
/*   Updated: 2023/01/04 16:55:51 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H

float		cal_cos(int a);
float		cal_sin(int a);
t_shade		calculate_shading(t_shade a, t_shade b, int gap);
int			close_window(t_data *data);
int			count_columns(char *line);
int			display(t_data *data);
void		display_background(t_img *img);
void		display_grid(t_data *data);
int			draw_line(t_img *img, t_coor2d a, t_coor2d b);
int			draw_line2(t_img *img, t_coor2d a, t_coor2d b);
int			draw_line3(t_img *img, t_coor2d a, t_coor2d b);
int			draw_line4(t_img *img, t_coor2d a, t_coor2d b);
int			get_color(t_shade color);
t_altcol	*get_coor_3d(char	*line, int size_x, t_data *data);
t_coor2d	**get_map_2d(t_data *data, t_altcol	**map, t_size2d size);
t_shade		get_next_color(t_shade color, t_shade gap);
t_shade		get_opp_color(t_shade color);
t_coor2d	get_2di(t_coor3d point, t_params params, t_size2d size);
void		erline(int v_incr, int er_incr, int *v, int *er);
void		free_tab_altcol(t_altcol **tab, int i);
void		free_tab_coor2d(t_coor2d **tab, int index);
int			ft_abs(int a);
t_altcol	ft_atoi_fdf(char *nptr);
int			ft_atoi_hexa(char *str);
t_altcol	*ft_memcpy_fdf(t_altcol *dest, t_altcol *src, int n);
int			ft_sign(int a);
int			ft_strstr_hexa(char c);
int			handle_keypress(int keysym, t_data *data);
void		handle_keypress2(int keysym, t_data *data);
int			handle_mouse(int button, int x, int y, t_data *data);
void		img_pix_put(t_img *img, int x, int y, int color);
t_altcol	**read_map(t_data *data);
t_shade		read_shade(char *str);
t_altcol	**realloc_tab(t_altcol **tab, char *line, t_data *data);
void		reset_user_type(t_data *data, int a);
float		setup_alti(int tsize, float a);
t_params	setup_param(t_size2d size, t_params user, float a);

#endif