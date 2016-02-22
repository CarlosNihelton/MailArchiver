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

// std
#include <string>
#include <unordered_map>

// Qt
#include <QStringListModel>

// locals
#include "MailArchive.h"

class ArchiveManager
{
public:
    /**
    * Meyers Singleton design.
    *
    * This method is the only way the user can create and/or access theArchiveManager.
    * \return A static reference to the ArchiveManager object created.
    */
    static ArchiveManager& instance();

    /**
     * Adds an archive to the pool. If it doesn't exist, it will be created.
     * \param fileName The full path and name for the archive file to be opened or created.
     * \param name The name to be stored as a key to access the archive inside the pool.
     */
    void openArchive(const QString& fileName, const QString& name);

    /**
     * Closes an open archive.
     * By closing I mean only removing its name from the list and model members. The archive will be alive into the
     * pool, in order to respond quickly to a reopen request.
     * \param name The name of the archive to be closed as it is stored in the internal pool.
     */
    void softCloseArchive(const QString& name);

    /**
     * Really closes an open archive.
     * \param name The name of the archive to be closed as it is stored in the internal pool.
     */
    void hardCloseArchive(const QString& name);

    /**
     * Really closes everything.
     * Needed because we cannot late destroy QSqlDatabase objects contained inside MailArchive objects, because it
     * might happen of the driver being already unloaded and resulting on SIGSEGV when ARchiveManager dtor is called.
     */
    void hardCloseAll();

    /**
     * Returns a reference to the active archive.
     */
    MailArchive& current();

    /**
     * Returns a reference to the active archive name member.
     */
    const QString& currentName();

    /**
     * Sets the active archive.
     * \param name of the archive as stored into the pool.
     */
    void setCurrent(const QString& name);

    /**
     * Returns an irresponsible pointer to list model exposing the structure of the open archives.
     *
     */
    QStringListModel* model();

    /**
     * Access the internal pool of archives held by theArchiveManager.
     *
     */
    std::unordered_map<std::string, MailArchive>& archivePool() { return m_archivePool; };

    /**
     * Virtual destructor.
     */
    ~ArchiveManager() = default;

private:
    /**
     * Default constructor is private.
     */
    ArchiveManager() = default;

    QStringListModel m_model;
    QStringList m_list;
    QString m_current;
    std::unordered_map<std::string, MailArchive> m_archivePool;
};

#endif // ARCHIVEMANAGER_H
