/**
 * @file ft_count_if.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-02-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

// ************************************************************************** //
// *                                                                        * //
// * Header function.                                                       * //
// *                                                                        * //
// ************************************************************************** //

int	ft_count_if(
		const char *s, int (*func)(char)
		)
{
	int	k;

	k = 0;
	while (s[k] != '\0' && func(s[k]))
		++k;
	return (k);
}
