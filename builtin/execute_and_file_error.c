/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_and_file_error.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 10:55:03 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/30 14:04:42 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_to_fd(int fd, char *path, DIR *folder)
{
	if (ft_strchr(path, '/') == NULL)
		ft_putendl_fd(": command not found", 2);
	else if (fd == -1 && folder == NULL)
		ft_putendl_fd(": No such file or directory", 2);
	else if (fd == -1 && folder != NULL)
		ft_putendl_fd(": is a directory", 2);
	else if (fd != -1 && folder == NULL)
		ft_putendl_fd(": Permission denied", 2);
}

int	error_message(char *path)
{
	DIR	*folder;
	int	fd;
	int	ret;

	ret = 0;
	if (access(path, F_OK) != 0)
	{
		fd = open(path, O_WRONLY);
		folder = opendir(path);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		error_to_fd(fd, path, folder);
		if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
			ret = 1;
		else
			ret = 2;
		if (folder)
			closedir(folder);
		close(fd);
	}
	return (ret);
}
