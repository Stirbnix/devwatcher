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

#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>

#include "defines.h"
#include "watcher.h"
#include "mounter.h"

class Application : public QObject
{
    Q_OBJECT

public:
    explicit Application(QObject *parent = nullptr);

private:
    Watcher *m_watcher;
    Mounter *m_mounter;

private slots:
    void onDeviceAttached(const QString &dev);
};

#endif // APPLICATION_H
