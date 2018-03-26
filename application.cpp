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

#include <QThread>

#include "checker.h"
#include "application.h"

Application::Application(QObject *parent) : QObject(parent),
    m_watcher(new Watcher(this)),
    m_mounter(new Mounter(this))
{
    connect(m_watcher, &Watcher::deviceAttached,
            this, &Application::onDeviceAttached);
    connect(m_watcher, &Watcher::deviceDetached,
            m_mounter, &Mounter::umountDevice);

    m_watcher->start();

    qInfo("Up and running");
}

void Application::onDeviceAttached(const QString &dev)
{
    QThread *t = new QThread();
    Checker *c = new Checker(dev);

    connect(t, &QThread::started, c, &Checker::process);
    connect(c, &Checker::destroyed, t, &QThread::quit);
    connect(c, &Checker::validDevice, m_mounter, &Mounter::mountDevice);
    c->moveToThread(t);
    t->start();
}
