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

#ifndef _GOBBY_AUTOSAVE_COMMANDS_HPP_
#define _GOBBY_AUTOSAVE_COMMANDS_HPP_

#include <sigc++/trackable.h>

#include "operations/operations.hpp"

#include "core/folder.hpp"
#include "core/documentinfostorage.hpp"
#include "core/preferences.hpp"

namespace Gobby
{

class AutosaveCommands: public sigc::trackable
{
public:
	AutosaveCommands(const Folder& folder, Operations& operations,
	                 const DocumentInfoStorage& storage,
	                 const Preferences& preferences);
	~AutosaveCommands();

protected:
	void on_document_added(SessionView& view);
	void on_document_removed(SessionView& view);

	void on_begin_save_operation(OperationSave* operation);
	void on_autosave_enabled_changed();
	void on_autosave_interval_changed();

	const Folder& m_folder;
	Operations& m_operations;
	const DocumentInfoStorage& m_info_storage;
	const Preferences& m_preferences;

	class Info;
	typedef std::map<TextSessionView*, Info*> InfoMap;
	InfoMap m_info_map;
};

}
	
#endif // _GOBBY_AUTOSAVE_COMMANDS_HPP_
