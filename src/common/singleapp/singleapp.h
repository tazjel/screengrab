/***************************************************************************
 *   Copyright (C) 2010 - 2013 by Artem 'DOOMer' Galichkin                        *
 *   doomer3d@gmail.com                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef SINGLEAPP_H
#define SINGLEAPP_H

#include <QtGui/QApplication>
#include <QtCore/QSharedMemory>
#include <QtNetwork/QLocalServer>

class SingleApp : public QApplication
{
        Q_OBJECT
public:
        SingleApp(int &argc, char *argv[], const QString keyString);

        bool isRunning();
        bool sendMessage(const QString &message);

public Q_SLOTS:
        void receiveMessage();

Q_SIGNALS:
        void messageReceived(const QString& message);

private:
        bool runned;
        QString uniqueKey;
        QSharedMemory sharedMemory;
        QLocalServer *localServer;

        static const int timeout = 1000;
};

#endif // SINGLEAPP_H