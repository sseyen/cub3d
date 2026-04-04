/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 12:07:02 by alisseye          #+#    #+#             */
/*   Updated: 2026/04/04 12:07:03 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void	key_press(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == KEY_ESC && keydata.action == MLX_PRESS)
		close_game(param);
}
