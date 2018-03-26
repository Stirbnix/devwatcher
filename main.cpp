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

#include <QCommandLineParser>
#include <QCoreApplication>

#include "defines.h"
#include "application.h"

static void messageOutput(QtMsgType type,
                          const QMessageLogContext &context,
                          const QString &msg)
{
    Q_UNUSED(context);
    QByteArray localMsg = msg.toLocal8Bit();

    switch(type)
    {
    case QtDebugMsg:
        fprintf(stderr, APP_NAME ": DBG: %s\n",
                localMsg.constData());
        break;
    case QtInfoMsg:
        fprintf(stdout, APP_NAME ": INF: %s\n",
                localMsg.constData());
        break;
    case QtWarningMsg:
        fprintf(stderr, APP_NAME ": WRN: %s\n",
                localMsg.constData());
        break;
    case QtCriticalMsg:
        fprintf(stderr, APP_NAME ": CRT: %s\n",
                localMsg.constData());
        break;
    case QtFatalMsg:
    default:
        fprintf(stderr, APP_NAME ": FTL: %s\n",
                localMsg.constData());
        abort();
        break;
    }
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(messageOutput);
    QCoreApplication a(argc, argv);
    QCommandLineParser clParser;

    QCoreApplication::setApplicationName(APP_NAME);
    QCoreApplication::setApplicationVersion(APP_VERSION " (" _BUILD_NO_ ")");
    QCoreApplication::setOrganizationName(ORG_NAME);
    QCoreApplication::setOrganizationDomain(ORG_DOMAIN);

    clParser.setApplicationDescription(DESCRIPTION);
    clParser.addHelpOption();
    clParser.addVersionOption();
    clParser.process(a);

    Application app(&a);
    a.connect(&app, &Application::destroyed, &a, &QCoreApplication::quit);

    return a.exec();
}
