/*****************************************************************************
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

#ifndef ARCHIVEMANAGER_H
#define ARCHIVEMANAGER_H

#include <QMap>
#include <QObject>
#include <QStandardItemModel>

class MailArchive;

class ArchiveManager : public QObject
{
    Q_OBJECT

public:
     /**
     * Meyers-Singleton design.
     * 
     * This method is the only way the user can create and/or access theArchiveManager.
     * \return A static reference to the ArchiveManager object created.
     */
    static ArchiveManager& instance(){
        static ArchiveManager theArchiveManager;
        return theArchiveManager;
    }
    
    /**
     * Returns the tree model exposing the structure of the open archives.
     * 
     */
    QStandardItemModel* mgrModel() const;
    
    /**
     * Access the internal pool of archives held by theArchiveManager.
     * 
     */
    QMap<QString,MailArchive>& archivePool() const;

    /**
     * Virtual destructor.
     */
    virtual ~ArchiveManager();
    
public Q_SLOTS:


private:
    /**
     * Default constructor is private.
     */
    ArchiveManager();
    
    QStandardItemModel m_mgrModel;
    QMap<QString,MailArchive> m_archivePool;
};

#endif // ARCHIVEMANAGER_H
