/*******************************************************************************
 * devwatcher observes serial device connections and provides a fixed link
 * (mount point) to that device, regardless of the actual device name (e.g.:
 * /dev/ttyUSB0..99 or /dev/ttyACM0..99).
 *
 * Copyright (C) 2018  Andreas Gollsch
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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 ******************************************************************************/

#ifndef DEFINES_H
#define DEFINES_H

// General Application Information
#define APP_NAME    "devwatcher"
#define APP_VERSION "1.0"
#define DESCRIPTION ("\n" APP_NAME " observes serial device connections and " \
					 "provides\na fixed link (mount point) to that device, " \
					 "regardless of the\nactual device name " \
					 "(e.g. /dev/ttyUSB0..99 or /dev/ttyACM0..99).\n\n" \
					 "Copyright (C) 2018 Andreas Gollsch\n\n" \
					 "This program comes with ABSOLUTELY NO WARRANTY.\n" \
					 "This is free software, and you are welcome to " \
					 "redistribute\nit under certain conditions.")

#define CSTR(s) ((s).toStdString().c_str())

#endif // DEFINES_H

