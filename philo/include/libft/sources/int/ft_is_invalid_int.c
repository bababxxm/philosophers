/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_invalid_int.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:23:14 by sklaokli          #+#    #+#             */
/*   Updated: 2024/12/17 12:23:44 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

bool	ft_is_invalid_int(long nbr)
{
	if (nbr < INT_MIN || nbr > INT_MAX)
		return (true);
	return (false);
}
