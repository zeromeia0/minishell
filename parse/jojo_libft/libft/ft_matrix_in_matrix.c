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
		ret[count] = mat[count];
	ind2 = -1;
	while (holder[++ind2])
	{
		ret[count] = holder[ind2];
		count++;
	}
	while (mat[ind])
	{
		ret[count] = mat[ind];
		count++;
		ind++;
	}
	return (free(holder), free(mat), ret);
}
