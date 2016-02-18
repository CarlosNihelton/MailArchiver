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

#include "ArchiveManager.h"

ArchiveManager& ArchiveManager::instance() {
    static ArchiveManager theArchiveManager;
    return theArchiveManager;
}

void ArchiveManager::openArchive(const QString& fileName, const QString& name)
{
    if(!m_list.contains(name)) {
        std::string  sName(name.toStdString());
        if(!m_archivePool.count(sName)) {
            m_archivePool.emplace(sName, MailArchive(fileName));
        }
        m_list << name;
        m_model.setStringList(m_list);
        m_current = name;
    }
}

void ArchiveManager::softCloseArchive(const QString& name)
{
    std::string  sName(name.toStdString());
    if(m_archivePool.count(sName)) {
        m_list.removeAll(name);
        m_model.setStringList(m_list);
    }
}

void ArchiveManager::hardCloseArchive(const QString& name) {
    std::string  sName(name.toStdString());
    if(m_archivePool.count(sName)) {
        m_archivePool.erase(sName);
        softCloseArchive(name);
    }
}

void ArchiveManager::hardCloseAll() {
    m_archivePool.clear();
    m_list.clear();
    m_model.setStringList(m_list);
}

MailArchive& ArchiveManager::current() {
    return m_archivePool.at(m_current.toStdString());
}

void ArchiveManager::setCurrent(const QString& name) {
    if(m_archivePool.count(name.toStdString())) {
        m_current=name;
    }
}

QStringListModel* ArchiveManager::model()
{
    QStringListModel* ret {&m_model};
    return ret;
}
