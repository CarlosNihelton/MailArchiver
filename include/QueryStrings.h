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

#include <QString>

class QueryStrings
{
  public:
    static const QString SelectAllFolders;
    static const QString SelectAllTags;
    static const QString SelectAllEmails;
    static const QString CreateMailArchiveTable;
    static const QString CreateFoldersTable;
    static const QString CreateTagsTable;
    static const QString CreateFolderRelsTable;
    static const QString CreateTagRelsTable;
    static const QString SelectCountOfMails;
    static const QString InsertNewMail;
    static const QString TryClearSQLiteState;
    static const QString SelectCompressedContents;
    static const QString DeleteMail;

    static const QString SearchFullPattern;
    static const QString SearchBodyPattern;
    static const QString SearchSubjectPattern;
    static const QString SearchFromPattern;
    static const QString SearchToPattern;
};

const QString QueryStrings::SelectAllFolders = QStringLiteral("SELECT * FROM MailFolders");
const QString QueryStrings::SelectAllTags    = QStringLiteral("SELECT * FROM MailTags");
const QString QueryStrings::SelectAllEmails = QStringLiteral("SELECT * FROM MailArchive");
const QString QueryStrings::CreateMailArchiveTable =
    QStringLiteral("CREATE TABLE IF NOT EXISTS MailArchive ("
                   "MESSAGEID VARCHAR(32) PRIMARY KEY NOT NULL, "
                   "FROM_NAME TEXT, FROM_ADDR TEXT, "
                   "TO_NAME TEXT, TO_ADDR TEXT, "
                   "CC TEXT, BCC TEXT, SUBJECT TEXT, "
                   "CWHEN DATE, CONTENT TEXT, "
                   "COMPRESSED BLOB, HASATTACH BOOL)");

const QString QueryStrings::CreateFoldersTable = QStringLiteral("CREATE TABLE IF NOT EXISTS "
                                                                "MailFolders (FID INTEGER PRIMARY "
                                                                "KEY NOT NULL, "
                                                                "FNAME TEXT NOT NULL)");
const QString QueryStrings::CreateTagsTable = QStringLiteral("CREATE TABLE IF NOT EXISTS "
                                                             "MailTags (TID INTEGER PRIMARY KEY "
                                                             "NO NULL, TNAME TEXT NOT NULL)");
const QString QueryStrings::CreateFolderRelsTable =
    QStringLiteral("CREATE TABLE IF NOT EXISTS FolderRels (FRELID "
                   "INTEGER PRIMARY KEY NOT NULL, FID INTEGER NOT "
                   "NULL, MID VARCHAR(32) NOT NULL)");
const QString QueryStrings::CreateTagRelsTable = QStringLiteral("CREATE TABLE IF NOT EXISTS "
                                                                "TagRels (TRELID INTEGER PRIMARY "
                                                                "KEY NOT NULL, TID "
                                                                "INTEGER NOT NULL, "
                                                                "MID VARCHAR(32) NOT NULL)");
const QString QueryStrings::SelectCountOfMails = QStringLiteral("SELECT COUNT(MESSAGEID) FROM "
                                                                "MailArchive WHERE MESSAGEID=?");
const QString QueryStrings::InsertNewMail = QStringLiteral("INSERT INTO MailArchive (MESSAGEID, FROM_NAME, "
                                                           "FROM_ADDR, TO_NAME, TO_ADDR, CC, BCC, SUBJECT, "
                                                           "CWHEN, CONTENT, COMPRESSED, HASATTACH) VALUES "
                                                           "(?,?,?,?,?,?,?,?,?,?,?,?)");
const QString QueryStrings::TryClearSQLiteState      = QStringLiteral("SELECT MESSAGEID FROM MailArchive LIMIT 1");
const QString QueryStrings::SelectCompressedContents = QStringLiteral("SELECT COMPRESSED FROM "
                                                                      "MailArchive WHERE MESSAGEID=?");
const QString QueryStrings::DeleteMail        = QStringLiteral("DELETE FROM MailArchive WHERE MESSAGEID=?");
const QString QueryStrings::SearchFullPattern = QStringLiteral(
    "SELECT * FROM MailArchive WHERE FROM_NAME like '%1' or FROM_ADDR like '%1' or TO_NAME like '%1' or "
    "TO_ADDR like '%1' or CC like '%1' or BCC like '%1' or SUBJECT like '%1' or CONTENT like '%1'");
const QString QueryStrings::SearchBodyPattern =
    QStringLiteral("SELECT * FROM MailArchive WHERE CONTENT like '%1'");
const QString QueryStrings::SearchSubjectPattern =
    QStringLiteral("SELECT * FROM MailArchive WHERE SUBJECT like '%1'");
const QString QueryStrings::SearchFromPattern =
    QStringLiteral("SELECT * FROM MailArchive WHERE FROM_NAME like '%1' or FROM_ADDR like '%1'");
const QString QueryStrings::SearchToPattern =
    QStringLiteral("SELECT * FROM MailArchive WHERE TO_NAME like '%1' or TO_ADDR like '%1' or CC like '%1' "
                   "or BCC like '%1'");
