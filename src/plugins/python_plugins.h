/*
 * python_plugins.h
 *
 * Copyright (C) 2012 - 2014 James Booth <boothj5@gmail.com>
 *
 * This file is part of Profanity.
 *
 * Profanity is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Profanity is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Profanity.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef PYTHON_PLUGINS_H
#define PYTHON_PLUGINS_H

#include "plugins/plugins.h"

ProfPlugin* python_plugin_create(const char * const filename);

void python_init_hook(ProfPlugin *plugin, const char * const version, const char * const status);
void python_on_start_hook(ProfPlugin *plugin);
void python_on_connect_hook(ProfPlugin *plugin, const char * const account_name, const char * const fulljid);
void python_on_disconnect_hook(ProfPlugin *plugin, const char * const account_name, const char * const fulljid);
char * python_before_message_displayed_hook(ProfPlugin *plugin, const char *message);
char * python_on_message_received_hook(ProfPlugin *plugin, const char * const jid, const char *message);
char * python_on_private_message_received_hook(ProfPlugin *plugin, const char * const room,
    const char * const nick, const char *message);
char * python_on_room_message_received_hook(ProfPlugin *plugin, const char * const room,
    const char * const nick, const char *message);
char * python_on_message_send_hook(ProfPlugin *plugin, const char * const jid, const char *message);
char * python_on_private_message_send_hook(ProfPlugin *plugin, const char * const room,
    const char * const nick, const char *message);
char * python_on_room_message_send_hook(ProfPlugin *plugin, const char * const room,
    const char *message);
void python_on_shutdown_hook(ProfPlugin *plugin);

void python_plugin_destroy(ProfPlugin *plugin);
void python_check_error(void);

void allow_python_threads();
void disable_python_threads();

#endif