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


#ifndef MAILARCHIVE_H
#define MAILARCHIVE_H

//std

//Qt
#include <QString>
#include <QSqlDatabase>

//Local
#include "msg.h"

class QSqlQueryModel;
class QSqlDatabase;
class MailListModel;

class MailArchive
{
private:
    QString baseFileName;
    QString m_Path;
    QString m_ActiveFolder;
    QString m_ActiveTag;
    
    MailListModel* m_Emails;
    QSqlQueryModel* m_Folders;
    QSqlQueryModel* m_Tags;
    
    QSqlDatabase db;
    unsigned int transactionCounter;
    
public:
    MailArchive(const QString& filename);
    void openFile(const QString& filename);
    virtual ~MailArchive();
    
    const QString& activeFolder(){return m_ActiveFolder;}
    const QString& activeTag(){return m_ActiveTag;}
    const QString& path(){return m_Path;}
    const QString& fileName(){return baseFileName;}
    
    MailListModel* emails(){return m_Emails;}
    QSqlQueryModel* folders(){return m_Folders;}
    QSqlQueryModel* tags(){return m_Tags;}
    
    void setActiveFolder(const QString& af);
    void setActiveTag(const QString& at);
    
    void archiveMsg(Core::Msg& msgFile);
    void archiveFolder(const QString& folder);
    Core::Msg retrieveMsg(const QString& messageId);
    void saveMsgAsFile(const QString& messageId, const QString& fileName);
    void refresh();
    
};

#endif // MAILARCHIVE_H
