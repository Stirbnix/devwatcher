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

#include <QIODevice>
#include <QThread>

#include "checker.h"

#define TIMEOUT_SEC (5)

Checker::Checker(QString dev, QObject *parent) : QObject(parent),
    m_port(nullptr),
    m_dev(dev)
{
}

Checker::~Checker()
{
    if(m_port != nullptr)
        m_port->close();
}

void Checker::process()
{
    m_timer = new QTimer();
    m_port = new QSerialPort();

    connect(m_timer, &QTimer::timeout, this, &Checker::onTimeout);
    connect(m_port, &QSerialPort::readyRead, this, &Checker::onReadyRead);

    m_timer->setSingleShot(true);
    m_timer->start(TIMEOUT_SEC * 1000);
    m_port->setBaudRate(QSerialPort::Baud115200);
    m_port->setPortName(m_dev);
    QThread::msleep(100);
    if(!m_port->open(QIODevice::ReadOnly))
        deleteLater();
}

void Checker::onTimeout()
{
    deleteLater();
}

void Checker::onReadyRead()
{
    static int lines = 5;

    m_timer->start(TIMEOUT_SEC * 1000);
    if(!m_port->canReadLine())
        return;
    QByteArray data = m_port->readLine();
    if(data.contains("MountPoint:"))
    {
        validDevice(m_dev, data.mid(data.indexOf("/")).simplified().toLower());
        deleteLater();
    }
    if(--lines < 0)
        deleteLater();
}
