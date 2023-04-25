/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 12:40:22 by avast             #+#    #+#             */
/*   Updated: 2023/04/25 16:58:07 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/params.h"
#include "../includes/proto.h"
#include "../libft/libft.h"

void	free_tab_altcol(t_altcol **tab, int i)
{
	if (i < 0)
		return ;
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
}

void	free_tab_coor2d(t_coor2d **tab, int index)
{
	while (index >= 0)
	{
		free(tab[index]);
		index--;
	}
	free(tab);
}

t_vec3	calculate_lower_left_corner(t_data data)
{
	t_vec3	corner;

	corner.x = data.origin.x - data.horizontal.x / 2 - data.vertical.x / 2;
	corner.y = data.origin.y - data.horizontal.y / 2 - data.vertical.y / 2;
	corner.z = data.origin.z - data.horizontal.z / 2 - data.vertical.z / 2 - data.focal_length;
	return (corner);
}

int	main(int ac, char **av)
{
	t_data		data;

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
	data.aspect_ratio = WIDTH / HEIGHT;
	data.viewport_height = 2;
	data.viewport_width = data.viewport_height * data.aspect_;
	data.focal_length = 1;
	data.origin = {0, 0, 0};
	data.horizontal = {data.viewport_width, 0, 0};
	data.vertical = {0, data.viewport_height, 0};
	data.lower_left_corner = calculate_lower_left_corner(data);

	// Render & loop
	mlx_loop_hook(data.mlx_ptr, &display, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, ButtonPress, ButtonPressMask, &handle_mouse, &data);
	mlx_hook(data.win_ptr, 17, ButtonPressMask, &close_window, &data);
	mlx_loop(data.mlx_ptr);
}