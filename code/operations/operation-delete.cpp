/* gobby - A GTKmm driven libobby client
 * Copyright (C) 2005 - 2008 0x539 dev group
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "operations/operation-delete.hpp"
#include "util/i18n.hpp"

Gobby::OperationDelete::OperationDelete(Operations& operations,
                                        InfcBrowser* browser,
                                        InfcBrowserIter* iter):
	Operation(operations),
	m_name(infc_browser_iter_get_name(browser, iter))
{
	m_request = infc_browser_remove_node(browser, iter);

	// Note infc_browser_remove_node does not return a
	// new reference.
	g_object_ref(m_request);

	m_failed_id = g_signal_connect(
		G_OBJECT(m_request), "failed",
		G_CALLBACK(on_request_failed_static), this);
	m_finished_id = g_signal_connect(
		G_OBJECT(m_request), "finished",
		G_CALLBACK(on_request_finished_static), this);

	m_message_handle = get_status_bar().add_message(
		StatusBar::INFO,
		Glib::ustring::compose(_("Removing node %1..."), m_name), 0);
}

Gobby::OperationDelete::~OperationDelete()
{
	g_signal_handler_disconnect(G_OBJECT(m_request), m_finished_id);
	g_signal_handler_disconnect(G_OBJECT(m_request), m_failed_id);
	g_object_unref(m_request);

	get_status_bar().remove_message(m_message_handle);
}

void Gobby::OperationDelete::on_request_failed(const GError* error)
{
	get_status_bar().add_message(
		StatusBar::ERROR,
		Glib::ustring::compose(_("Failed to delete node %1: %2"),
			m_name, error->message), 5);

	remove();
}

void Gobby::OperationDelete::on_request_finished(InfcBrowserIter* iter)
{
	remove();
}