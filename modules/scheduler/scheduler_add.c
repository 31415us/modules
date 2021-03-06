/*  
 *  Copyright Droids Corporation, Microb Technology, Eirbot (2005)
 * 
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  Revision : $Id: scheduler_add.c,v 1.1.2.4 2009-11-08 17:33:14 zer0 Exp $
 *
 */

#include <aversive.h>

#include <scheduler_config.h>
#include <scheduler_private.h>
#include <scheduler_stats.h>

#include <stdio.h>

/** @brief Get a free event,
 *
 * This funtion searches for a free event, marks it as allocated and returns its
 * index.
 *
 * @return Index of the allocated event or -1 if no free event was found.
 */
static inline int8_t scheduler_alloc_event(void) {
	uint8_t i;
	
	for (i=0 ; i<SCHEDULER_NB_MAX_EVENT ; i++) {
		if( g_tab_event[i].state == SCHEDULER_EVENT_FREE ) {
			g_tab_event[i].state = SCHEDULER_EVENT_ALLOCATED;
			return i;
		}
	}
	SCHED_INC_STAT(alloc_fails);
	printf("%s failed, maybe we should increase SCHEDULER_NB_MAX_EVENT...\r\n", __FUNCTION__);
	return -1;
}

int8_t scheduler_add_event(uint8_t unicity, void (*f)(void *), 
			   void *data, uint16_t period, 
			   uint8_t priority) {
	int8_t i;
	
	if(period == 0)
		return -1;

	i = scheduler_alloc_event();
	if(i == -1)
		return -1;

	SCHED_INC_STAT(add_event);

	if (!unicity)
		g_tab_event[i].period = period ;
	else
		g_tab_event[i].period = 0 ;
	g_tab_event[i].current_time = period ;
	g_tab_event[i].priority = priority ;
	g_tab_event[i].f = f;
	g_tab_event[i].data = data;
	
	g_tab_event[i].state = SCHEDULER_EVENT_ACTIVE;

	return i;
}
