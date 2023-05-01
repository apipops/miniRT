/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 12:40:22 by avast             #+#    #+#             */
/*   Updated: 2023/05/01 18:29:03 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/params.h"
#include "../includes/proto.h"
#include "../libft/libft.h"

t_vec3	calculate_lower_left_corner(t_data data)
{
	t_vec3	corner;

	corner.xyz = data.origin.xyz + data.direction.xyz - data.horizontal.xyz / 2 - data.vertical.xyz / 2;
	return (corner);
}

int	main(void)
{
	t_data		data;
	double		fov;

	// Initialization mlx items
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "miniRT");
	if (data.win_ptr == NULL)
		return (free(data.win_ptr), MLX_ERROR);
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);

	// Initialization data
	fov = deg_to_rad(75);
	data.aspect_ratio = (double)WIDTH / (double)HEIGHT;
	data.focal_length = 1;
	data.viewport_height = 2 * data.focal_length * tan(fov / 2);
	data.viewport_width = data.viewport_height * data.aspect_ratio;
	data.origin = (t_vec3){0, 0, 1};
	data.direction = vec3_normalize((t_vec3){0, 0, -1});
	data.horizontal = data.viewport_width * vec3_normalize(vec3_cross(data.direction, (t_vec3){0, 1, 0}));
	data.vertical = data.viewport_height * vec3_normalize(vec3_cross(data.direction, data.horizontal));
	data.corner = calculate_lower_left_corner(data);

	// Render & loop
	mlx_loop_hook(data.mlx_ptr, &display, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, 17, ButtonPressMask, &close_window, &data);
	mlx_loop(data.mlx_ptr);
}
