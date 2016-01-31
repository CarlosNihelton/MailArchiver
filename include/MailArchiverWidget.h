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

#ifndef MAILARCHIVERWIDGET_H
#define MAILARCHIVERWIDGET_H

#include <QMainWindow>
#include "MailArchive.h"

namespace Ui
{
class MailArchiverWidget;
}

class MailArchive;
class MailListDelegate;

class MailArchiverWidget : public QMainWindow
{
public:
    MailArchiverWidget();
    virtual ~MailArchiverWidget();
    static const int ExitCodeRestartApp=-54321;

// protected:
//     void contextMenuEvent(QContextMenuEvent *event);

protected slots:
    //Actions
    //void onClose(); //Not required. Directly connected to the widget close handler.
    void onEditTags();
    void onEditFolders();
    void onEditPreferences();
    void onAbout();
    void onNewArchive();
    void onNewFolder();
    void onNewTag();
    void onOpenArchive();
    void onArchiveEmails();
    void onArchiveEntireFolder();

    //TODO: Implement a context menu for the mail list view.
    void onCustomCtxMenuRequested(QPoint pos);

    //Context menu actions:
    void onActionViewSelected();
    void onActionExportSelected();
    void onActionMoveToFolder();
    void onActionRemoveFromArchive();

    //Widget reactors
//     void onListViewDoubleClicked(const QModelIndex& index);

    //slot for restarting the application.
    void onRestartApplication();

private:
    Ui::MailArchiverWidget* ui;
    MailListModel* model;
    MailListDelegate* delegate;
    MailArchive* archive;
};

#endif // MAILARCHIVERWIDGET_H
