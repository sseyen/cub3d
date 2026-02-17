#ifndef INPUT_H
# define INPUT_H

/* Event codes shared by MLX across platforms */
# define EVENT_KEYDOWN 2
# define EVENT_KEYUP 3
# define EVENT_CLOSE 17

/* Event masks for mlx_hook */
# define MASK_KEYDOWN (1L << 0)
# define MASK_KEYUP (1L << 1)
# define MASK_CLOSE 0L

# ifdef CUB3D_LINUX
#  define KEY_ESC 65307
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_UP 65362
#  define KEY_DOWN 65364
# elif defined(CUB3D_MACOS)
#  define KEY_ESC 53
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_UP 126
#  define KEY_DOWN 125
# else
#  error "Define CUB3D_LINUX or CUB3D_MACOS to select keycodes"
# endif

#endif /* INPUT_H */
