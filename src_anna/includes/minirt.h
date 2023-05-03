/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:49:42 by ankhabar          #+#    #+#             */
/*   Updated: 2023/05/03 16:26:39 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define ERRCOMMAS	"Too many or not enough commas.\033[0m"
# define ERRCHAR	"Invalid characters detected.\033[0m"
# define ERRRANGE	"Invalid range of a parameter.\033[0m"
# define ERRPARAM	"Invalid number of parameters.\033[0m"
# define ERRDEF		"You cannot redefine A or C.\033[0m"
# define ERRITI		1
# define ERRIPN		2
# define SPHERE		1
# define PLANE		2
# define CYLINDER	3


# include <errno.h>
# include <stdlib.h>
# include <float.h>
# include "libft.h"
# include "colors.h"

typedef float	t_vec3	__attribute__((ext_vector_type(3)));

/* typedef struct s_vec3 {
	float	x;
	float	y;
	float	z;
}			t_vec3; */

typedef struct s_ambient {
	float	ratio;
	t_vec3	colors;
}			t_ambient;

typedef struct s_camera {
	t_vec3	origin;
	t_vec3	dir;
	float	fov;
}			t_camera;

typedef struct s_light {
	t_vec3			origin;
	float			ratio;
	t_vec3			colors;
	struct s_light	*next;
}			t_light;

typedef struct s_objects {
	int					id;
	int					type;
	t_vec3				origin;
	t_vec3				dir;
	float				radius;
	float				height;
	t_vec3				colors;
	struct s_objects	*next;
}		t_objects;

typedef struct s_elements {
	t_ambient	ambient;
	t_camera	camera;
	t_light		*lights_head;
	t_objects	*objects_head;
	int			flag_camera;
	int			flag_ambient;
}				t_elem;

//error ------------------------------------------- //
void	error(char **to_free, t_elem *elems, int code);

//free -------------------------------------------- //
void	free_tab(char **tab);
void	free_structures(t_elem *elems);

//acl_check --------------------------------------- //
bool	ambient(t_elem *elems, char **params);
bool	camera(t_elem *elems, char **params);
bool	light(t_elem *elems, char **params);

//acl_init ---------------------------------------- //
bool	reinit_ambient(t_elem *elems, char **params);
bool	reinit_camera(t_elem *elems, char **params);
bool	reinit_light(t_elem *elems, char **params);

//parse objects ----------------------------------- //
void	init_object_head(t_elem *elems, char **params, int type);
void	new_node_object(t_elem *elems, char **params, int type);

//parse cylinders --------------------------------- //
void	init_cylinder(t_objects *object, char **params);
bool	cylinder(t_elem *elems, char **params);

//parse planes ------------------------------------ //
void	init_plane(t_objects *object, char **params);
bool	plane(t_elem *elems, char **params);

//parse spheres ----------------------------------- //
void	init_sphere(t_objects *object, char **params);
bool	sphere(t_elem *elems, char **params);

//parse utils ------------------------------------- //
t_vec3	colors_to_percent(char **tab);

//parse checks ------------------------------------ //
bool	invalid_param_number(int code, char **params);
bool	invalid_chars(char *str);
bool	not_valid_parameter(char *to_check, float min, float max);
bool	not_valid_number_of_commas(char *to_check);
bool	not_valid_range(char *to_check, float min, float max);

float	ft_atof(const char *nptr);

#endif
