#include <stdio.h>
#include "libft/libft.h"
#include "minishell.h"
int	push(t_tokens **thestack, char *thevalue)
{
	t_tokens	*newnode;
	t_tokens	*temp;

	temp = NULL;
	newnode = malloc(sizeof(t_tokens));
	if (newnode == NULL)
	{
		write(2, "Error\n", 6);
		free(newnode);
		return (0);
	}
	newnode->token = thevalue;
	newnode->next = NULL;
	if (*thestack == NULL)
		*thestack = newnode;
	else
	{
		temp = *thestack;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newnode;
	}
	return (1);
}
char	*ft_strdup(const char *s1)
{
	char	*mem_dup;
	size_t	i;

	i = 0;
	mem_dup = malloc(strlen(s1) + 1);
	if (!mem_dup)
		return (NULL);
	while (s1[i] != '\0')
	{
		mem_dup[i] = s1[i];
		i++;
	}
	mem_dup[i] = '\0';
	return (mem_dup);
}
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub_str;
	unsigned int	l1;
	unsigned int	l2;

	if (!s)
		return (NULL);
	l1 = strlen(s);
	l2 = strlen(s + start);
	if (l1 < start)
		return (strdup(""));
	if (l2 < len)
		len = strlen(s + start);
	sub_str = malloc(len + 1);
	if (!sub_str)
		return (NULL);
	strlcpy(sub_str, s + start, len + 1);
	return (sub_str);
}
void	find_token(t_tokens *tokens) {

    const char *line = "'foobar'|cat'mousebar'sum";
    char delim = '\'';
    char *p = (char *)line;
	char *first = NULL;
	char *second = NULL;
	char *str;
    size_t i = 0;
	size_t len = -1;

    while (p && *p) {                /* for each char in line */
        if (!first && *p == delim)             /* find 1st delim */
            first = p, first++;                   /* set start ptr  */
        else if (!second && *p == delim)        /* find 2nd delim */
        {
			str = ft_substr(first, 0, len);   
			len = -1;                    /* set end ptr    */
			second = p;
		}
		if (first && second) {                     /* if both set    */
            printf ("single-quoted string : %s\n", str);
			push(&tokens, str);
            first = second = NULL;
			
        }
		if (first)
			len++;
		p++;
    }
}
int main (void) {
	t_tokens	*tokens;
	t_tokens	*tmp;
	// char *token1;
	// char *token2;
	// char *token3;

tokens = malloc(sizeof(t_tokens));
	find_token(tokens);
	// token1 = ft_strdup("hello");
	// token2 = ft_strdup("hello again");
	// token3 = ft_strdup("hello");
;
	
	tmp = tokens;
	tokens = tokens->next;
	free(tmp);

	// push(&tokens, token1);
	// push(&tokens, token2);
	// push(&tokens, token3);
 

	tmp = tokens;
	while(tmp)
	{
		printf(">%s\n", tmp->token);
		tmp = tmp->next;
	}
	system("leaks test");
    return 0;
}