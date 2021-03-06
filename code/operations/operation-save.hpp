/* Gobby - GTK-based collaborative text editor
 * Copyright (C) 2008-2014 Armin Burgmeier <armin@arbur.net>
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
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#ifndef _GOBBY_OPERATIONS_OPERATION_SAVE_HPP_
#define _GOBBY_OPERATIONS_OPERATION_SAVE_HPP_

#include "operations/operations.hpp"
#include "core/documentinfostorage.hpp"

#include <giomm/file.h>
#include <giomm/outputstream.h>
#include <glibmm/convert.h>

#include <ctime>

namespace Gobby
{

class OperationSave: public Operations::Operation, public sigc::trackable
{
public:
	// TODO: This should maybe just take a text buffer to save, not a
	// textsessionview.
	OperationSave(Operations& operations, TextSessionView& view,
	              const std::string& uri, const std::string& encoding,
	              DocumentInfoStorage::EolStyle eol_style);

	virtual ~OperationSave();

	virtual void start();

	// Note these can return NULL in case the view has been closed
	// in the meanwhile.
	TextSessionView* get_view() { return m_view; }
	const TextSessionView* get_view() const { return m_view; }

	std::time_t get_start_time() const { return m_start_time; }

protected:
	void on_document_removed(SessionView& view);
	void on_file_replace(const Glib::RefPtr<Gio::AsyncResult>& result);
	void on_stream_write(const Glib::RefPtr<Gio::AsyncResult>& result);

	void attempt_next();
	void write_next();
	void error(const Glib::ustring& message);
protected:
	const std::string m_uri;
	TextSessionView* m_view;
	std::time_t m_start_time;

	typedef std::pair<gchar*, std::size_t> Line;
	std::list<Line> m_lines;
	std::list<Line>::iterator m_current_line;
	std::size_t m_current_line_index;

	std::string m_encoding;
	DocumentInfoStorage::EolStyle m_eol_style;
	std::string m_storage_key;
	Glib::IConv m_iconv;

	static const std::size_t BUFFER_SIZE = 1024;
	char m_buffer[BUFFER_SIZE];
	std::size_t m_buffer_size;
	std::size_t m_buffer_index;

	Glib::RefPtr<Gio::File> m_file;
	Glib::RefPtr<Gio::OutputStream> m_stream;

	StatusBar::MessageHandle m_message_handle;
};

}

#endif // _GOBBY_OPERATIONS_OPERATION_SAVE_HPP_
