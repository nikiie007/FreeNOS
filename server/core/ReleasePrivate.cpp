/*
 * Copyright (C) 2009 Niek Linnenbank
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "CoreServer.h"
#include "CoreMessage.h"

void CoreServer::releasePrivate(CoreMessage *msg)
{
    msg->access |= Memory::Present | Memory::User;
    
    /* Only allow unmapping of user pages. */
    if (!VMCtl(msg->from, Access, msg))
    {
        msg->result = EFAULT;
        return;
    }
    msg->access = Memory::None;
	
    /* Unmap now. */
    VMCtl(msg->from, Map, msg);

    /* Done. */
    msg->result = ESUCCESS;
}
