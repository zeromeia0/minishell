#include "../libft.h"

char	**ft_matrix_in_matrix(char **mat, int ind, char **holder)
{
	int		count;
	int		ind2;
	char	**ret;

	count = ft_matlen(mat) + ft_matlen(holder);
	ret = malloc(sizeof(char *) * (count + 1));
	if (ret == NULL)
		return (ft_free_matrix(holder), mat);
	ret[count] = NULL;
	count = -1;
	while (++count < ind)
	{
		ret[count] = ft_strdup(mat[count]);
		// printf("before thing is %s\n", ret[count]);
		// fflush(stdout);
	}
	ind2 = -1;
	while (holder[++ind2])
	{
		ret[count] = holder[ind2];
		// printf("before thing2 is %s\n", ret[count]);
		// fflush(stdout);
		count++;
	}
	while (mat[ind])
	{
		ret[count] = ft_strdup(mat[ind]);
		// printf("after thing is %s\n", ret[count]);
		// fflush(stdout);
		count++;
		ind++;
	}
	// printf("end is %s\n", ret[count]);
	// fflush(stdout);
	return (free(holder), free_matrix_nodes(mat), ret);
}
