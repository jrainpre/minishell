/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 21:18:57 by jonathanrai       #+#    #+#             */
/*   Updated: 2022/10/19 10:43:18 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*entry;

	entry = (t_list *)malloc(sizeof(t_list));
	if (!entry)
		return (NULL);
	entry->next = NULL;
	entry->content = content;
	return (entry);
}
