/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 13:40:46 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/30 13:42:12 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	op_union(double d1, double d2)
{
	return (fmin(d1, d2));
}

double	op_sub(double d1, double d2)
{
	return (fmax(-d1, d2));
}

double	op_intersect(double d1, double d2)
{
	return (fmax(d1, d2));
}