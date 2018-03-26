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

#include <QDir>

#include "watcher.h"

#define DEV_PATH "/dev/"

Watcher::Watcher(QObject *parent) :
    QObject(parent),
    m_devWatcher(new QFileSystemWatcher(this))
{
    connect(m_devWatcher, &QFileSystemWatcher::directoryChanged,
            this, &Watcher::dirChanged);
}

void Watcher::start()
{
    m_devWatcher->addPath(DEV_PATH);
    m_devList = getDevList(DEV_PATH);
    foreach(QString dev, m_devList)
        emit deviceAttached(DEV_PATH + dev);
}

QStringList Watcher::getDevList(const QString &path)
{
    QDir dir(path);
    dir.setNameFilters(QStringList() << "ttyUSB*" << "ttyACM*");
    dir.setFilter(QDir::System);

    return dir.entryList();
}

void Watcher::dirChanged(const QString &path)
{
    QStringList newDevList = getDevList(path);

    foreach (QString dev, m_devList) {
        if(!newDevList.contains(dev))
        {
            m_devList.removeAll(dev);
            emit deviceDetached(path + dev);
        }
    }
    foreach(QString dev, newDevList)
    {
        if(!m_devList.contains(dev))
        {
            m_devList.append(dev);
            emit deviceAttached(path + dev);
        }
    }
}
