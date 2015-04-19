/*
 * client_events.c
 *
 * Copyright (C) 2012 - 2015 James Booth <boothj5@gmail.com>
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

#include <glib.h>

#include "config.h"
#include "log.h"
#include "ui/ui.h"
#include "xmpp/xmpp.h"
#ifdef HAVE_LIBOTR
#include "otr/otr.h"
#endif

void
client_msg_send(const char * const barejid, const char * const msg)
{
    char *id = NULL;

#ifdef HAVE_LIBOTR
    prof_otrpolicy_t policy = otr_get_policy(barejid);

    if (otr_is_secure(barejid)) {
        char *encrypted = otr_encrypt_message(barejid, msg);
        if (encrypted != NULL) {
            id = message_send_chat_encrypted(barejid, encrypted);
            chat_log_otr_msg_out(barejid, msg);
            ui_outgoing_chat_msg(barejid, msg, id);
            otr_free_message(encrypted);
        } else {
            cons_show_error("Failed to encrypt and send message.");
        }

    } else if (policy == PROF_OTRPOLICY_ALWAYS) {
        cons_show_error("Failed to send message. Please check OTR policy");

    } else if (policy == PROF_OTRPOLICY_OPPORTUNISTIC) {
        char *otr_tagged_msg = otr_tag_message(msg);
        id = message_send_chat_encrypted(barejid, otr_tagged_msg);
        ui_outgoing_chat_msg(barejid, msg, id);
        chat_log_msg_out(barejid, msg);
        free(otr_tagged_msg);

    } else {
        id = message_send_chat(barejid, msg);
        ui_outgoing_chat_msg(barejid, msg, id);
        chat_log_msg_out(barejid, msg);
    }
#else
    id = message_send_chat(barejid, msg);
    chat_log_msg_out(barejid, msg);
    ui_outgoing_chat_msg(barejid, msg, id);
#endif

    free(id);
}