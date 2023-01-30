/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_and_file_error.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 10:55:03 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/30 16:38:46 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_global	g_global;

void	error_to_fd(int fd, char *path, DIR *folder)
{
	if (ft_strchr(path, '/') == NULL)
	{
		ft_putendl_fd(": command not found", 2);
		g_global.exit_status = 127;
	}
	else if (fd == -1 && folder == NULL)
	{
		ft_putendl_fd(": No such file or directory", 2);
		g_global.exit_status = 127;
	}
	else if (fd == -1 && folder != NULL)
	{
		ft_putendl_fd(": is a directory", 2);
		g_global.exit_status = 127;
	}
	else if (fd != -1 && folder == NULL)
	{
		ft_putendl_fd(": Permission denied", 2);
		g_global.exit_status = 126;
	}
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
