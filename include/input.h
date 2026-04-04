/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 12:08:06 by alisseye          #+#    #+#             */
/*   Updated: 2026/04/04 12:08:55 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef INPUT_H
# define INPUT_H

/* map chars */
# define WALL '1'
# define FLOOR '0'
# define SPACE ' '
# define PLAYER_NORTH 'N'
# define PLAYER_SOUTH 'S'
# define PLAYER_EAST 'E'
# define PLAYER_WEST 'W'

/* raycasting */
# define TILE_SIZE 64

/* MLX42 key aliases */
# define KEY_ESC   MLX_KEY_ESCAPE
# define KEY_W     MLX_KEY_W
# define KEY_A     MLX_KEY_A
# define KEY_S     MLX_KEY_S
# define KEY_D     MLX_KEY_D
# define KEY_LEFT  MLX_KEY_LEFT
# define KEY_RIGHT MLX_KEY_RIGHT
# define KEY_UP    MLX_KEY_UP
# define KEY_DOWN  MLX_KEY_DOWN

#endif
