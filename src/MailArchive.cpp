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

// std
#include <fstream>
#include <sstream>
// Qt
#include <QString>
#include <QUrl>
#include <QDirIterator>
#include <QSqlQuery>
#include <QFile>
#include <QBuffer>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlError>
// local
#include "utils.h"
#include "MailListModel.h"
#include "MailArchive.h"
#include "QueryStrings.h"

MailArchive::MailArchive(const QString& filename)
    : transactionCounter{ 0 }
{
    openFile(filename);
    m_Folders = std::make_unique<QSqlQueryModel>();
    m_Folders->setQuery(QueryStrings::SelectAllFolders, db);
    m_Tags = std::make_unique<QSqlQueryModel>();
    m_Tags->setQuery(QueryStrings::SelectAllTags, db);
    m_Emails = std::make_unique<MailListModel>();
    m_Emails->setQuery(QueryStrings::SelectAllEmails, db);
}

void MailArchive::openFile(const QString& filename)
{
    QUrl name(filename);
    baseFileName = name.fileName();
    m_Path       = name.path();

    db = QSqlDatabase::addDatabase("QSQLITE", baseFileName);
    db.setDatabaseName(filename);

    if (db.open()) {
        QSqlQuery q(db);

        q.exec(QueryStrings::CreateMailArchiveTable);

        q.exec(QueryStrings::CreateFoldersTable);
        q.exec(QueryStrings::CreateTagsTable);
        q.exec(QueryStrings::CreateFolderRelsTable);
        q.exec(QueryStrings::CreateTagRelsTable);
    }
}

void MailArchive::refreshQueries()
{
    QString query = m_Emails->query().lastQuery();
    m_Emails->setQuery("", db);
    m_Emails->setQuery(query, db);
    query = m_Folders->query().lastQuery();
    m_Folders->setQuery("", db);
    m_Folders->setQuery(query, db);
}

void MailArchive::setActiveFolder(const QString& af)
{
    m_ActiveFolder = af;
}

void MailArchive::setActiveTag(const QString& at)
{
    m_ActiveTag = at;
}

void MailArchive::archiveFolder(const QString& folder)
{
    QDirIterator it(folder, QStringList() << "*.msg", QDir::Files);
    while (it.hasNext()) {
        QString mes = it.next();
        qDebug() << mes;
        Core::Msg msg(mes.toStdString());
        archiveMsg(msg);
        db.commit();
    }
    refreshQueries();
}

void MailArchive::archiveMsg(Core::Msg& msgFile)
{
    QSqlQuery q(db);
    q.prepare(QueryStrings::SelectCountOfMails);
    q.addBindValue(msgFile.hash().c_str());
    q.exec();
    q.next();
    if (q.value(0).toInt() == 0) {
        if (transactionCounter == 0)
            db.transaction();

        q.prepare(QueryStrings::InsertNewMail);
        q.addBindValue(msgFile.hash().c_str());
        q.addBindValue(msgFile.senderName().c_str());
        q.addBindValue(msgFile.senderAddress().c_str());
        q.addBindValue(msgFile.receiversNames().c_str());
        q.addBindValue(msgFile.receiversAddresses().c_str());
        q.addBindValue(msgFile.CCs().c_str());
        q.addBindValue(msgFile.Bccs().c_str());
        q.addBindValue(msgFile.subject().c_str());
        q.addBindValue(msgFile.date().c_str());
        q.addBindValue(msgFile.body().c_str());
        std::string compressed = Utils::string_compress_encode_file(msgFile.fileName());
        qDebug() << compressed.size();
        q.addBindValue(compressed.data(), QSql::In | QSql::Binary);
        q.addBindValue(msgFile.hasAttachments());

        if (q.exec())
            ++transactionCounter;
        else {
            qDebug() << q.lastError();
            db.close();
            db.open();
        }

        qDebug() << q.lastQuery();

        if (transactionCounter == 299u) {
            db.commit();
            transactionCounter = 0;
            // try to clear sqlite state...
            q.exec(QueryStrings::TryClearSQLiteState);
            q.next();
            qDebug() << q.value(0).toString();
        }
    } else {
        qDebug() << "This email already exists into the "
                    "archive: "
                 << msgFile.hash().c_str();
    }
}

Core::Msg MailArchive::retrieveMsg(const QString& messageId)
{
    saveMsgAsFile(messageId, messageId);
    Core::Msg msg(messageId.toStdString());
    return msg;
}

void MailArchive::saveMsgAsFile(const QString& messageId, const QString& fileName)
{
    QSqlQuery q(db);
    q.prepare(QueryStrings::SelectCompressedContents);
    q.addBindValue(messageId);
    q.exec();
    if (q.next()) {
        QByteArray array(q.value(0).toByteArray());
        std::string input(array.data(), array.size());
        Utils::string_decompress_decode_to_file(input, fileName.toStdString());
    }
}

void MailArchive::deleteMsg(const QString& id)
{
    QSqlQuery q(db);
    q.prepare(QueryStrings::DeleteMail);
    q.addBindValue(id);
    q.exec();
    // TODO: Delete from folders too.
    refreshQueries();
}
