#include <stdio.h>
#include "minishell.h"

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
int main (void) {

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
            first = second = NULL;
			
        }
		if (first)
			len++;
		p++;
    }
    return 0;
}