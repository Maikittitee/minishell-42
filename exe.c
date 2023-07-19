/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:22:15 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/19 18:18:20 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	is_pipe(char *input)
{
	while(*input)
	{
		if (*input == '|')
			return (1);
		input++;
	}
	return (0);
}

t_line	*init_line(void)
{
	t_line *line;
	
	line = malloc(sizeof(line));
	if (!line)
		perror("malloc failed.");
	
	line->fd_in = 0;
	line->fd_out = 1;
	return (line);
	
	
}

t_file *create_file(void)
{
	t_file *ret;

	ret = malloc(sizeof(t_file) * 3);
	ret[0].filename = ft_strdup("infile");
	ret[0].index = 1;
	ret[0].type = infile;
	ret[1].filename = ft_strdup("outfile");
	ret[1].index = 2;
	ret[1].type = outfile;
	ret[3].type = none;
	return (ret);
}

void	print_file(t_file *file)
{
	int	i;

	i = 0;
	if (!file)
		return ;
	while (file[i].type != none)
	{
		printf("%d.%s[%d]\n", i + 1, file[i].filename, file[i].type);
		i++;
	}
}

t_scmd **init_cmd(t_scmd *cmd)
{
	t_scmd **head;
	head = malloc(sizeof(t_scmd *));
	*head = cmd;
	return (head);
}

t_scmd *new_node(char *str)
{
	t_scmd *cmd;

	cmd = malloc(sizeof(t_scmd));
	cmd->cmd = ft_split(str, ' ');
	cmd->file = NULL;
	cmd->next = NULL;
	return (cmd);
	
}

void	link_cmd(t_scmd **head, t_scmd *cmd)
{
	t_scmd *curr;

	(void)cmd;
	curr = *head;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = cmd;
}

int	executor(t_scmd *cmd, char **env)
{

	global_data.return_code = do_pipe(cmd, env);
	return (1);
	
	
}

int	main(int ac, char **av, char **env)
{
	t_scmd **cmd;
	
	(void)ac;
	(void)av;
	env = dup_env(env);
	global_data.env_dict = get_env_dict(env);
	
	cmd = init_cmd(new_node("ls -l"));
	// link_cmd(cmd, new_node("wc -l"));
	print_cmd(cmd);
	executor(*cmd, env);
		
		
	ft_double_free(env);
	ft_free_dict(global_data.env_dict);
	clear_free_cmd(*cmd);
	free(cmd);
	return (0);	
}