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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the Free
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#include "util/closebutton.hpp"

#include <gtkmm/image.h>
#include <gtkmm/stock.h>
#include <gtk/gtk.h>

Gobby::CloseButton::CloseButton()
{
        set_relief(Gtk::RELIEF_NONE);
        set_focus_on_click(false);
	//set_flags(get_flags() & ~Gtk::CAN_FOCUS);

        GtkRcStyle* rc_style = gtk_rc_style_new();
        rc_style->xthickness = 0;
        rc_style->ythickness = 0;
        gtk_widget_modify_style(GTK_WIDGET(gobj()), rc_style);
        g_object_unref(rc_style);

        Gtk::Image* button_image = Gtk::manage(
                new Gtk::Image(Gtk::Stock::CLOSE, Gtk::ICON_SIZE_MENU));
        add(*button_image);
        button_image->show();
}

#ifdef USE_GTKMM3
void Gobby::CloseButton::on_style_updated()
#else
void Gobby::CloseButton::on_style_changed(
	const Glib::RefPtr<Gtk::Style>& previous_style)
#endif
{
	int width;
	int height;

	gtk_icon_size_lookup_for_settings(
		gtk_widget_get_settings(GTK_WIDGET(gobj())),
		GTK_ICON_SIZE_MENU, &width, &height);
	set_size_request(width + 2, height + 2);
}
