/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:45:15 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/19 14:04:24 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

# define SPACE 0x31
# define ESC 0x35
# define RETURN 0x24
# define KEY_UP 0x7e
# define KEY_DOWN 0x7c
# define KEY_LEFT 0x7b
# define KEY_RIGHT 0x7d
# define KEY_W 0x0d
# define KEY_S 0x01
# define KEY_A 0x00
# define KEY_D 0x02
# define KEY_G 0x05
# define KEY_Z 0x06
# define KEY_X 0x07
# define KEY_C 0x08
# define KEY_O 0x1f
# define KEY_P 0x23
# define KEY_L 0x25
# define KEY_Q 0x0c
# define KEY_I 0x22
# define KEY_M 0x2d
# define KEY_1 0x12
# define KEY_2 0x13
# define KEY_3 0x14
# define KEY_4 0x15
# define KEY_5 0x17
# define KEY_6 0x16
# define KEY_7 0x1a
# define KEY_8 0x1c
# define KEY_9 0x19
# define KEY_0 0x1d
# define COMMA 0x2b
# define DOT 0x2f
# define SQ_BR_L 0x21
# define SQ_BR_R 0x1e
# define MINUS 0x1b
# define PLUS 0x18

# define KEY_UP_TO_TWO(x) (x == KEY_1 || x == KEY_2) ? 1 : 0
# define KEY_UP_TO_THREE(x) (KEY_UP_TO_TWO(x) || x == KEY_3) ? 1 : 0
# define KEY_UP_TO_FOUR(x) (KEY_UP_TO_THREE(x) || x == KEY_4) ? 1 : 0
# define KEY_UP_TO_FIVE(x) (KEY_UP_TO_FOUR(x) || x == KEY_5) ? 1 : 0
# define KEY_UP_TO_SIX(x) (KEY_UP_TO_FIVE(x) || x == KEY_6) ? 1 : 0
# define KEY_UP_TO_SEVEN(x) (KEY_UP_TO_SIX(x) || x == KEY_7) ? 1 : 0
# define KEY_UP_TO_EIGHT(x) (KEY_UP_TO_SEVEN(x) || x == KEY_8) ? 1 : 0
# define KEY_UP_TO_NINE(x) (KEY_UP_TO_EIGHT(x) || x == KEY_9) ? 1 : 0
# define KEY_UP_TO_ZERO(x) (KEY_UP_TO_NINE(x) || x == KEY_0) ? 1 : 0

# define KEY_NUM_VALUE_0(x) (x == KEY_0) ? 0 : x
# define KEY_NUM_VALUE_9(x) (x == KEY_9) ? 9 : KEY_NUM_VALUE_0(x)
# define KEY_NUM_VALUE_8(x) (x == KEY_8) ? 8 : KEY_NUM_VALUE_9(x)
# define KEY_NUM_VALUE_7(x) (x == KEY_7) ? 7 : KEY_NUM_VALUE_8(x)
# define KEY_NUM_VALUE_6(x) (x == KEY_6) ? 6 : KEY_NUM_VALUE_7(x)
# define KEY_NUM_VALUE_5(x) (x == KEY_5) ? 5 : KEY_NUM_VALUE_6(x)
# define KEY_NUM_VALUE_4(x) (x == KEY_4) ? 4 : KEY_NUM_VALUE_5(x)
# define KEY_NUM_VALUE_3(x) (x == KEY_3) ? 3 : KEY_NUM_VALUE_4(x)
# define KEY_NUM_VALUE_2(x) (x == KEY_2) ? 2 : KEY_NUM_VALUE_3(x)
# define KEY_NUM_VALUE(x) (x == KEY_1) ? 1 : KEY_NUM_VALUE_2(x)

#endif
