/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 12:40:22 by avast             #+#    #+#             */
/*   Updated: 2023/05/03 13:24:47 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/params.h"
#include "../includes/proto.h"
#include "../libft/libft.h"


// lstlast adapled for t_plane struct
static t_objects	*sp_lstlast(t_objects *lst, int *id)
{
	int	i;

	i = 1;
	while (lst->next != NULL)
	{
		i++;
		lst = lst->next;
	}
	*id = i;
	return (lst);
}

void	new_node_object(t_elements *elems, int type, int id, t_vec3 origin, t_vec3 orientation, double radius, t_vec3 colors)
{
	t_objects	*plst;
	t_objects	*new_node;

	new_node = malloc(sizeof(t_objects));
	if (new_node == NULL)
		perror("malloc");
	new_node->id = id;
	new_node->type = type;
	new_node->origin = origin;
	new_node->orientation = orientation;
	new_node->radius = radius;
	new_node->colors = colors;
	new_node->next = NULL;
	plst = elems->objects_head;
	plst = sp_lstlast(elems->objects_head, &new_node->id);
	plst->next = new_node;
}

// normalize les vecteurs
void	initialize_data(t_data *data, t_elements elem)
{
	t_camera	camera;

	elem.camera->orientation = vec3_normalize(elem.camera->orientation);
	camera = elem.camera;
	data->elements = elem;
	data->aspect_ratio = (double)WIDTH / (double)HEIGHT;
	data->focal_length = 1;
	data->height = 2 * data->focal_length * tan(deg_to_rad(camera.fov) / 2);
	data->width = data->height * data->aspect_ratio;
	data->horizontal = data->width
		* vec3_normalize(vec3_cross(camera.orientation, (t_vec3){0, 1, 0}));
	data->vertical = data->height
		* vec3_normalize(vec3_cross(camera.orientation, data->horizontal));
	data.corner = camera.origin.xyz + camera.orientation.xyz
		- data->horizontal.xyz / 2 - data->vertical.xyz / 2;
}


int	main(void)
{
	t_data		data;
	t_elements	elem;

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
	initialize_data(&data, elem);

	// Render & loop
	mlx_loop_hook(data.mlx_ptr, &display, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, 17, ButtonPressMask, &close_window, &data);
	mlx_loop(data.mlx_ptr);
}
