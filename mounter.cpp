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

#include <QFile>

#include "defines.h"
#include "mounter.h"

Mounter::Mounter(QObject *parent) : QObject(parent)
{
}

void Mounter::mountDevice(const QString &dev, const QString &mnt)
{
    QFile link(mnt);
    if(link.exists() && !link.remove())
    {
        qCritical("Symbolic link may exists and can't be removed: %s -> %s",
                  CSTR(mnt), CSTR(dev));
        return;
    }
    if(!QFile::link(dev, mnt))
    {
        qCritical("Can't create symbolic link: %s -> %s", CSTR(mnt), CSTR(dev));
        return;
    }
    qInfo("Symbolic link created: %s -> %s", CSTR(mnt), CSTR(dev));
    m_devMap[dev] = mnt;
}

void Mounter::umountDevice(const QString &dev)
{
    if(!m_devMap.contains(dev))
        return;
    QFile link(m_devMap[dev]);
    if(link.exists() && !link.remove())
        qCritical("Can't remove symbolic link: %s", CSTR(m_devMap[dev]));
    qInfo("Symbolic link removed: %s -> %s", CSTR(m_devMap[dev]), CSTR(dev));
    m_devMap.remove(dev);
}
