/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:48:17 by avast             #+#    #+#             */
/*   Updated: 2023/01/04 16:20:20 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/params.h"
#include "../includes/proto.h" 
#include "../libft/libft.h"

int	ft_strstr_hexa(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c > 'a' && c <= 'f')
		return (c - 'a' + 10);
	if (c > 'A' && c <= 'F')
		return (c - 'A' + 10);
	else
		return (-1);
}

int	ft_atoi_hexa(char *str)
{
	int	nombre;
	int	i;

	i = 0;
	nombre = 0;
	while (str[i] && i < 2 && ft_strstr_hexa(str[i]) > -1)
	{
		nombre = nombre * 16 + ft_strstr_hexa(str[i]);
		i++;
	}
	return (nombre);
}

t_altcol	ft_atoi_fdf(char *nptr)
{
	t_altcol	n;

	n.z = ft_atoi(nptr);
	while (*nptr != ',' && *nptr != 10 && *nptr != 32)
		nptr++;
	if (*nptr == ',')
		n.color = read_shade(nptr);
	else
		n.color = (t_shade){255, 255, 255};
	return (n);
}

t_altcol	*ft_memcpy_fdf(t_altcol *dest, t_altcol *src, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}
