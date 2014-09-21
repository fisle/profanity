/*
 * plugins.h
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
 * In addition, as a special exception, the copyright holders give permission to
 * link the code of portions of this program with the OpenSSL library under
 * certain conditions as described in each individual source file, and
 * distribute linked combinations including the two.
 *
 * You must obey the GNU General Public License in all respects for all of the
 * code used other than OpenSSL. If you modify file(s) with this exception, you
 * may extend this exception to your version of the file(s), but you are not
 * obligated to do so. If you do not wish to do so, delete this exception
 * statement from your version. If you delete this exception statement from all
 * source files in the program, then also delete it here.
 *
 */

#ifndef PLUGINS_H
#define PLUGINS_H

typedef enum {
    LANG_PYTHON,
    LANG_RUBY,
    LANG_LUA,
    LANG_C
} lang_t;

typedef struct prof_plugin_t {
    char *name;
    lang_t lang;
    void *module;
    void (*init_func)(struct prof_plugin_t* plugin, const char * const version,
        const char * const status);
    void (*on_start_func)(struct prof_plugin_t* plugin);
    void (*on_connect_func)(struct prof_plugin_t* plugin,
        const char * const account_name, const char * const fulljid);
    void (*on_disconnect_func)(struct prof_plugin_t* plugin,
        const char * const account_name, const char * const fulljid);
    char* (*before_message_displayed_func)(struct prof_plugin_t* plugin,
        const char * const message);
    char* (*on_message_received_func)(struct prof_plugin_t* plugin,
        const char * const jid, const char * const message);
    char* (*on_private_message_received_func)(struct prof_plugin_t* plugin,
        const char * const room, const char * const nick,
        const char * const message);
    char* (*on_room_message_received_func)(struct prof_plugin_t* plugin,
        const char * const room, const char * const nick,
        const char * const message);
    char* (*on_message_send_func)(struct prof_plugin_t* plugin,
        const char * const jid, const char * const message);
    char* (*on_private_message_send_func)(struct prof_plugin_t* plugin,
        const char * const room, const char * const nick,
        const char * const message);
    char* (*on_room_message_send_func)(struct prof_plugin_t* plugin,
        const char * const room, const char * const message);
    void (*on_shutdown_func)(struct prof_plugin_t* plugin);
} ProfPlugin;

void plugins_init(void);
GSList * plugins_get_list(void);
char * plugins_get_lang_string(ProfPlugin *plugin);
void plugins_on_start(void);
void plugins_on_connect(const char * const account_name, const char * const fulljid);
void plugins_on_disconnect(const char * const account_name, const char * const fulljid);
char * plugins_before_message_displayed(const char * const message);
char * plugins_on_message_received(const char * const jid, const char *message);
char * plugins_on_room_message_received(const char * const room, const char * const nick, const char *message);
char * plugins_on_private_message_received(const char * const room, const char * const nick, const char *message);
char * plugins_on_message_send(const char * const jid, const char *message);
char * plugins_on_private_message_send(const char * const room, const char * const nick,
    const char * const message);
char * plugins_on_room_message_send(const char * const room, const char *message);
void plugins_on_shutdown(void);
void plugins_shutdown(void);
gboolean plugins_run_command(const char * const cmd);
void plugins_run_timed(void);
gchar * plugins_get_dir(void);

char* plugins_autocomplete(char *input, int *size);
void plugins_reset_autocomplete(void);

void plugins_win_process_line(char *win, const char * const line);
#endif