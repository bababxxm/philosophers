/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:42:46 by sklaokli          #+#    #+#             */
/*   Updated: 2025/01/13 07:27:34 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*node;
	t_list	*tmp;

	if ((!lst) || (!del))
		return ;
	node = *lst;
	while (node)
	{
		tmp = node;
		node = node -> next;
		ft_lstdelone(tmp, del);
	}
	*lst = NULL;
}
