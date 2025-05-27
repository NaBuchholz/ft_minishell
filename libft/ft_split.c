/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:26:44 by nbuchhol          #+#    #+#             */
/*   Updated: 2024/10/24 18:14:04 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*word_dup(const char *start, size_t len)
{
	char	*word;

	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, start, len + 1);
	word[len] = '\0';
	return (word);
}

static void	fill_words_array(char **arr, char const *s, char c)
{
	char			*temp_s;
	size_t			count;
	unsigned int	start;

	temp_s = (char *)s;
	count = 0;
	while (*temp_s != '\0')
	{
		while (*temp_s == c)
			temp_s++;
		start = temp_s - s;
		while (*temp_s && *temp_s != c)
			temp_s++;
		if (temp_s - s > start)
		{
			arr[count] = word_dup(s + start, (size_t)(temp_s - s - start));
			count++;
		}
	}
}

char	**ft_split(char const *s, char c)
{
	char	**words_array;
	size_t	count;

	if (!s)
		return (NULL);
	count = count_words(s, c);
	words_array = (char **)malloc((count + 1) * sizeof(char *));
	if (!words_array)
		return (NULL);
	fill_words_array(words_array, s, c);
	words_array[count] = NULL;
	return (words_array);
}
