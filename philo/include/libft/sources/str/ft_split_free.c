/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:37:49 by sklaokli          #+#    #+#             */
/*   Updated: 2025/01/13 07:28:10 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_split_free(char **split)
{
	int	idx;

	if (!split)
		return ;
	idx = 0;
	while (split[idx])
		free(split[idx++]);
	free(split);
}
