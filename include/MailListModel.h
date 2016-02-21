/****************************************************************************
* Mail Archiver - A solution to store and manage offline e-mail files.      *
* Copyright (C) 2015-2016 Carlos Nihelton <carlosnsoliveira@gmail.com>      *
*                                                                           *
*   This is a free software; you can redistribute it and/or                 *
*   modify it under the terms of the GNU Library General Public             *
*   License as published by the Free Software Foundation; either            *
*   version 2 of the License, or (at your option) any later version.        *
*                                                                           *
*   This software  is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
*   GNU Library General Public License for more details.                    *
*                                                                           *
*   You should have received a copy of the GNU Library General Public       *
*   License along with this library; see the file COPYING.LIB. If not,      *
*   write to the Free Software Foundation, Inc., 59 Temple Place,           *
*   Suite 330, Boston, MA  02111-1307, USA                                  *
*                                                                           *
****************************************************************************/

#ifndef MAILLISTMODEL_H
#define MAILLISTMODEL_H

#include <QSqlQueryModel>

class MailListModel : public QSqlQueryModel
{
public:
    enum datarole {
        subjectTextRole = Qt::UserRole + 100,
        senderTextRole  = Qt::UserRole + 101,
        whenTextRole    = Qt::UserRole + 102,
        hasAttachRole   = Qt::UserRole + 103,
        messageIdRole   = Qt::UserRole + 104
    };
    MailListModel() = default;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    ~MailListModel() = default;
};

#endif // MAILLISTMODEL_H
