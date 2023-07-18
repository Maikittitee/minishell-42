/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:22:15 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/18 14:54:33 by ktunchar         ###   ########.fr       */
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
	cmd->next = NULL;
	return (cmd);
	
}

void	link_cmd(t_scmd **head, t_scmd *cmd)
{
	t_scmd *curr;

	(void)cmd;
	curr = *head;
	while (curr->next != NULL)
	{
		curr = curr->next;
	}
	printf("before link : lastest cmd is %s\n", curr->cmd[0]);
	curr->next = cmd;
	curr = curr -> next;
	printf("after link : lastest cmd is %s\n", curr->cmd[0]);
}

int	main(int ac, char **av, char **env)
{
	t_line *line;
	t_scmd **cmd;
	t_file	*file;
	
	(void)ac;
	(void)av;
	env = dup_env(env);
	line = init_line();
	global_data.env_dict = get_env_dict(env);
	// file = create_file();
	file = NULL;
	if (apply_fd(line, file) == -1)
		return (EXIT_FAILURE);
	print_file(file);
	printf("the file infile_fd is %d\n", line->fd_in);
	printf("the file outfile_fd is %d\n", line->fd_out);

	cmd = init_cmd(new_node("ls -l"));
	link_cmd(cmd, new_node("wc -l"));
	// printf("cmd is %s\n", (*cmd)->cmd[0]);
	printf("--------\n");
	print_cmd(cmd);
		
	
	// ft_double_free(env);
	// ft_free_dict(global_data.env_dict);
	// ft_free_file(file);
	// clear_free_cmd(cmd);
	return (0);	
}