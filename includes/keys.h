/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:01:42 by sko               #+#    #+#             */
/*   Updated: 2019/10/16 12:05:41 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

/*
** Reference : http://stackoverflow.com/a/16125341 | <events.h>
*/

# define KEY_AS_A			 		(0X00)
# define KEY_AS_S			 		(0X01)
# define KEY_AS_D			 		(0X02)
# define KEY_AS_X			 		(0X07)
# define KEY_AS_V			 		(0X09)
# define KEY_AS_Q			 		(0X0C)
# define KEY_AS_W			 		(0X0D)
# define KEY_AS_E			 		(0X0E)
# define KEY_AS_R			 		(0X0F)
# define KEY_AS_T			 		(0X11)
# define KEY_AS_O					(0X1F)
# define KEY_AS_M					(0X2E)
# define KEY_AS_I					(0X22)

# define KEY_NAS_SPACE				(0X31)
# define KEY_NAS_ESCAPE				(0X35)
# define KEY_NAS_LEFTARROW			(0X7B)
# define KEY_NAS_RIGHTARROW			(0X7C)
# define KEY_NAS_DOWNARROW			(0X7D)
# define KEY_NAS_UPARROW			(0X7E)

/*
** mouse button
*/

# define MOUSE_LEFT_CLICK			(0x01)
# define MOUSE_RIGHT_CLICK			(0x02)
# define MOUSE_MIDDLE_CLICK			(0x03)
# define MOUSE_UP_SCROLL			(0x04)
# define MOUSE_DOWN_SCROLL 			(0x05)

#endif
