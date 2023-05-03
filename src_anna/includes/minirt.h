/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankhabar <ankhabar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:49:42 by ankhabar          #+#    #+#             */
/*   Updated: 2023/05/03 13:18:29 by ankhabar         ###   ########.fr       */
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

# include <sys/wait.h>
# include <errno.h>
# include <stdlib.h>
# include <float.h>
# include "libft.h"
# include "colors.h"

// typedef double	t_vec3	__attribute__((ext_vector_type(3)));

typedef struct s_vec3 {
	double	x;
	double	y;
	double	z;
}			t_vec3;

typedef struct s_ambient {
	double	ratio;
	t_vec3	colors;
}			t_ambient;

typedef struct s_camera {
	t_vec3	origin;
	t_vec3	orientation;
	double	fov;
}			t_camera;

typedef struct s_light {
	t_vec3			origin;
	double			ratio;
	t_vec3			colors;
	struct s_light	*next;
}			t_light;

typedef struct s_objects {
	int					id;
	int					type;
	t_vec3				origin;
	t_vec3				orientation;
	double				radius;
	double				height;
	t_vec3				colors;
	struct s_objects	*next;
}		t_objects;

typedef struct s_elements {
	t_ambient	*ambient;
	t_camera	*camera;
	t_light		*lights_head;
	t_objects	*objects_head;
}				t_elements;

//error ------------------------------------------- //
void	error(char **to_free, t_elements *elems, int code);

//free -------------------------------------------- //
void	free_tab(char **tab);
void	free_structures(t_elements *elems);

//acl_check --------------------------------------- //
bool	ambient(t_elements *elems, char **params);
bool	camera(t_elements *elems, char **params);
bool	light(t_elements *elems, char **params);

//acl_init ---------------------------------------- //
bool	reinit_ambient(t_elements *elems, char **params);
bool	reinit_camera(t_elements *elems, char **params);
bool	reinit_light(t_elements *elems, char **params);

//parse objects ----------------------------------- //
void	init_object_head(t_elements *elems, char **params, int type);
void	new_node_object(t_elements *elems, char **params, int type);

//parse cylinders --------------------------------- //
void	init_cylinder(t_objects *object, char **params);
bool	cylinder(t_elements *elems, char **params);

//parse planes ------------------------------------ //
void	init_plane(t_objects *object, char **params);
bool	plane(t_elements *elems, char **params);

//parse spheres ----------------------------------- //
void	init_sphere(t_objects *object, char **params);
bool	sphere(t_elements *elems, char **params);

//parse utils ------------------------------------- //
t_vec3	colors_to_percent(char **tab);

//parse checks ------------------------------------ //
bool	invalid_param_number(int code, char **params);
bool	invalid_chars(char *str);
bool	not_valid_parameter(char *to_check, double min, double max);
bool	not_valid_number_of_commas(char *to_check);
bool	not_valid_range(char *to_check, double min, double max);

double	ft_atof(const char *nptr);

#endif
