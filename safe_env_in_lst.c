#include "minishell.h"

void fill_env_lst(t_env_list **env_lst, char **envp)
{
	int i;
	t_env_list *temp;
	t_env_list *new;

	i = 0;
	temp = *env_lst;
	while (envp[i])
	{
		new = malloc(sizeof(t_env_list));
		new->name = ft_substr(envp[i], 0, ft_strchr(envp[i], '=') - envp[i]);
		new->value = ft_substr(envp[i], ft_strchr(envp[i], '=') - envp[i] + 1, ft_strlen(envp[i]));
		new->next = NULL;
		if (i == 0)
			*env_lst = new;
		else
			temp->next = new;
		temp = new;
		i++;
	}
}

char *get_env_value(t_env_list *env_lst, char *name)
{
	t_env_list *temp;

	temp = env_lst;
	while (temp)
	{
		if (ft_strcmp(temp->name, name) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}