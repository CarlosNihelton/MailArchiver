/**************************************************************************
* Mail Archiver - A solution to store and manage offline e-mail files.    *
* Copyright (C) 2015-2016 Carlos Nihelton <carlosnsoliveira@gmail.com>    *
*                                                                         *
* This is a free software; you can redistribute it and/or                 *
* modify it under the terms of the GNU Library General Public             *
* License as published by the Free Software Foundation; either            *
* version 2 of the License, or (at your option) any later version.        *
*                                                                         *
* This software  is distributed in the hope that it will be useful,       *
* but WITHOUT ANY WARRANTY; without even the implied warranty of          *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
* GNU Library General Public License for more details.                    *
*                                                                         *
* You should have received a copy of the GNU Library General Public       *
* License along with this library; see the file COPYING.LIB. If not,      *
* write to the Free Software Foundation, Inc., 59 Temple Place,           *
* Suite 330, Boston, MA  02111-1307, USA                                  *
*                                                                         *
**************************************************************************/

#include "MailListModel.h"
#include <QSqlQuery>
#include <QSqlRecord>

QVariant MailListModel::data(const QModelIndex& index, int role) const
{
    QVariant returnVar;
    QString sublimited;

    if (index.isValid()) {
        switch (role) {
        case subjectTextRole:
            sublimited = record(index.row()).value("SUBJECT").toString();
            if (sublimited.length() > 123) {
                sublimited.resize(123);
                sublimited.replace(119, 122, "...");
                returnVar = QVariant::fromValue<QString>(sublimited);
            } else
                returnVar = record(index.row()).value("SUBJECT");
            break;

        case senderTextRole:
            returnVar = record(index.row()).value("FROM_NAME");
            break;
        case receiversRole:
            returnVar = record(index.row()).value("TO_NAME");
            break;
        case whenTextRole:
            returnVar = record(index.row()).value("CWHEN");
            break;
        case hasAttachRole:
            returnVar = record(index.row()).value("HASATTACH");
            break;
        case messageIdRole:
            returnVar = record(index.row()).value("MESSAGEID");
            break;
        case bodyTextRole:
            returnVar = record(index.row()).value("CONTENT");
            break;
        case Qt::DisplayRole:
            returnVar = QVariant();
            break;
        default:
            returnVar = QSqlQueryModel::data(index, role);
            break;
        }
    }

    return returnVar;
}

#include "MailListModel.moc"
