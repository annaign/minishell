/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 22:41:47 by pshagwel          #+#    #+#             */
/*   Updated: 2020/05/09 22:41:49 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_split_count_words(char const *s, char c)
{
	int	words;
	int i;
	int	delimiter;

	while (*s == c && *s != '\0')
		s++;
	words = (*s == '\0') ? 0 : 1;
	delimiter = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i++] == c)
			delimiter = 1;
		else if (delimiter == 1)
		{
			delimiter = 0;
			words++;
		}
	}
	return (words);
}

static char	*ft_split_word(char const *s, char c, int *i)
{
	char	*word;
	int		len;
	int		l;

	len = 0;
	while (s[*i] == c)
		(*i)++;
	while (s[*i + len] != c && s[*i + len] != '\0')
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (word)
	{
		l = 0;
		while (l < len)
			word[l++] = s[(*i)++];
		word[l] = '\0';
	}
	return (word);
}

static void	ft_split_free(char **arr, int len)
{
	int	i;

	i = 0;
	while (i < len)
		if (arr[i++] == NULL)
		{
			i = 0;
			while (i < len)
				free(arr[i++]);
			free(arr);
			arr = NULL;
		}
}

char		**ft_split(char const *s, char c)
{
	char	**arr;
	int		words;
	int		w;
	int		i;

	if (s == NULL)
		return (NULL);
	words = ft_split_count_words(s, c);
	arr = malloc(sizeof(char *) * (words + 1));
	if (arr)
	{
		w = 0;
		i = 0;
		while (w < words)
		{
			arr[w++] = ft_split_word(s, c, &i);
			if (arr[w - 1] == NULL)
			{
				ft_split_free(arr, words);
				return (NULL);
			}
		}
		arr[w] = NULL;
	}
	return (arr);
}
