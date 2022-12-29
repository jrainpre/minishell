#include "minishell.h"
char *get_env_name(char *arg);
int get_new_strlen(char *str, char *value, char *ptr);
char *get_new_str(char *str, char *envvar, char *ptr);
char *find_unquoted_dollar(char *str);
//function that replaces $ with the value of the env variable
void include_env(t_parse_com *args, char **env)
{
	char *ptr;
	char *name;
	char *second;
	int i = 0;

	while (find_unquoted_dollar(args->command))
	{
	ptr = find_unquoted_dollar(args->command);
		name = get_env_name(ptr);
		args->command = get_new_str(args->command, name, ptr);
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

char *get_env_name(char *arg)
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
	env_val = getenv(env_name);
	if (!env_val)
		env_val = ft_calloc(1, 1);
	free(env_name);
	return(env_val);
}



// int check_in_single_quotes(char *str)
// {
// 	int i;
// 	int open;
// 	int in_qutoes;
// 	int dollar_found;

// 	i = 0;
// 	open = 0;
// 	in_qutoes = 0;
// 	dollar_found = 0;
// 	while (str[i])
// 	{
// 		if (!open && str[i] == '\'')
// 			open = 1;
// 		if (open && str[i] == '$')
// 			dollar_found = 1;
// 		if (open && str[i++] == '\'')
// 		{
// 			open = 0;
// 			if (dollar_found)
// 				in_qutoes = 1;
// 		}
// 	}
// 	return (dollar_found);
// }


char *find_unquoted_dollar(char *str)
{
  bool in_single_quotes;
  char *q;

	in_single_quotes = false;
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

int main(int argc, char **argv, char **envp)
{
	t_parse_com args;
	int i;

	i = 0;

	args.command = "Hall'o $USER Test $GDMSESSION Hallo";
	include_env(&args, envp);

}