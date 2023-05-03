/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankhabar <ankhabar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:06:28 by ankhabar          #+#    #+#             */
/*   Updated: 2023/05/03 13:15:57 by ankhabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// todo: more specific errors, either in each function or here
void	error(char **to_free, t_elements *elems, int code)
{
	if (code == ERRITI)
		ft_dprintf(2, FRED"Error\nInvalid type identifier."RESET"\n");
	// else if (code == ERRIPN)
	// 	ft_dprintf(2, FRED"Error\nInvalid paramerters."RESET"\n");
	free_tab(to_free);
	free_structures(elems);
	exit(1);
}
