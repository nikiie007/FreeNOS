/*
 * Copyright (C) 2014 Niek Linnenbank
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

#include <FreeNOS/API.h>
#include <FileSystemMessage.h>
#include <FileType.h>
#include <FileMode.h>
#include "Runtime.h"
#include <errno.h>
#include "sys/stat.h"

int creat(const char *path, mode_t mode)
{
    FileSystemMessage msg;
    ProcessID mnt = findMount(path);

    /* Fill in the message. */
    msg.action   = CreateFile;
    msg.path     = (char *) path;
    msg.filetype = RegularFile;
    msg.mode     = (FileModes) (mode & FILEMODE_MASK);

    /* Ask FileSystem to create the file for us. */
    if (mnt)
    {
	IPCMessage(mnt, API::SendReceive, &msg, sizeof(msg));

	/* Set errno. */
	errno = msg.result;
    }
    else
	errno = ENOENT;

    /* Report result. */
    return msg.result == ESUCCESS ? 0 : -1;
}
