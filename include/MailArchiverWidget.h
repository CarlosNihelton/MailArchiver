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

namespace Ui
{
class MailArchiverWidget;
}

class ArchiveManager;
class MailArchive;
class MailListDelegate;
class MailListModel;
class QModelIndex;

class MailArchiverWidget : public QMainWindow
{
public:
    MailArchiverWidget();
    virtual ~MailArchiverWidget();
    static const int ExitCodeRestartApp=-54321;

protected:
    void createConnections();
    void createCtxMenu();
    void updateViews();
    //Due to a bug in Qt5, we cannot destroy an QSqlDatabase too later, because the driver might be already unloaded, which will result in a SIGSEGV. For this reason I reimplemented the closeEvent to destroy the Archiver Manager and all members.
    void closeEvent(QCloseEvent *event);

protected slots:
    //Actions
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

    void onSelectedOpenedArchive(const QModelIndex& index);
    void onSelectedFolderOnCurrentArchive(const QModelIndex& index);
    void onCustomCtxMenuRequested(QPoint pos);

    //Context menu actions:
    void onActionViewSelected();
    void onActionExportSelected();
    void onActionMoveToFolder();
    void onActionRemoveFromArchive();

    //slot for restarting the application.
    void onRestartApplication();

private:
    QMenu* ctxMenu;
    Ui::MailArchiverWidget* ui;
    MailListDelegate* delegate;
    ArchiveManager* archiveMgr;
};

#endif // MAILARCHIVERWIDGET_H
