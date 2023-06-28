#include "../minishell.h"

// int valid_arg(char *arg)
// {
// 	(void)arg;
// 	return (0);
// }
static char	*keep_token(char **s)
{
	char *token;
	int	len;

	len = word_len(s);
	token = malloc(sizeof(char) * len + 1);
	if (!token)
		return (NULL);
	ft_strlcpy(token, *s, len + 1);
	*s += len;
	return (token);
}

int ft_tokenize(char *s, t_token *token)
{
	int		i;

	if (!s)
		return (0);
	token->value = (char **)malloc((token->n_token + 1) * sizeof(char *));
	if (!token->value)
		return (0);
	i = -1;
	while (++i < token->n_token)
		token->value[i] = keep_token(&s);
	token->value[i] = NULL;
	return (1);
}
