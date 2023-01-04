/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 10:32:01 by jrainpre          #+#    #+#             */
/*   Updated: 2022/12/30 16:05:25 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void include_env(t_input *input, t_env_list *env_list)
{
	char *dollar_pos;
	char *name;
	char *temp;
	int i = 0;

	while (input->output[i])
	{
		while (find_unquoted_dollar(input->output[i]))	
		{
			dollar_pos = find_unquoted_dollar(input->output[i]);
			name = get_env_name(dollar_pos, env_list);
			temp = input->output[i];
			input->output[i] = get_new_str(input->output[i], name, dollar_pos);
			free(temp);
		}
		i++;
	}
}

char *get_new_str(char *str, char *envvar, char *ptr)
{
	char *new;
	int i;
	int j;

	i = 0;
	new = ft_calloc((get_new_strlen(str, envvar, ptr) + 1), 1);
	while(str[i] != '\0' && &str[i] != ptr)
		i++;
	ft_strncpy(new, str, i);
	ft_strcpy(&new[i], envvar);
	j = i;
	while(str[i] != '\0' && str[i] != ' ')
		i++;
	while(new[j] != '\0' && new[j] != ' ')
		j++;
	ft_strcpy(&new[j], &str[i]);
	return(new);
}
	
int get_new_strlen(char *str, char *value, char *ptr)
{
	int i;

	i = 0;
	while(*str != '\0' && str != ptr)
	{
		str++;
		i++;
	}
	while(*str != '\0' && *str != ' ')
		str++;
	while(*str != '\0')
	{
		str++;
		i++;
	}
	i += ft_strlen(value);
	return (i);
}

char *get_env_name(char *arg, t_env_list *env_lst)
{
	int i;
	char *env_name;
	char *env_val;

	i = 0;
	while (arg[i] && arg[i] != ' ')
		i++;
	env_name = calloc(i + 1, 1);
	arg++;
	i = 0;
	while (arg[i] && arg[i] != ' ')
	{
		env_name[i] = arg[i];
		i++;
	}
	env_val = get_env_value(env_lst, env_name);
	if (!env_val)
		env_val = ft_calloc(1, 1);
	free(env_name);
	return(env_val);
}

char *find_unquoted_dollar(char *str)
{
  int in_single_quotes;
  char *q;

	in_single_quotes = 0;
 	while (*str != '\0')
	{
    if (*str == '\'')
    	in_single_quotes = !in_single_quotes;
	else if (*str == '$')
	{
      if (in_single_quotes)
	  {
        q = str + 1;
        while (*q != '\0' && *q != '\'')
			q++;
        if (*q != '\'')
			return (str);
        str = --q;
      }
	  else
    	return (str);
    }
    str++;
  }
  return (NULL);
}