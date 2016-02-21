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

// Qt
#include <QPainter>
#include <QWidget>
#include <QApplication>

// local
#include "MailListDelegate.h"
#include "MailListModel.h"

MailListDelegate::MailListDelegate()
    : hasatt(":/hasatt")
    , noatt(":/noatt")
{
}

void MailListDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QIcon attachIcon;

    QStyledItemDelegate::paint(painter, option, index);

    painter->save();

    QFont font    = QApplication::font();
    QFont SubFont = QApplication::font();
    font.setBold(true);
    SubFont.setWeight(SubFont.weight() - 4);
    SubFont.setItalic(true);
    QFontMetrics fm(font);

    QString subjectText = qvariant_cast<QString>(index.data(MailListModel::subjectTextRole));
    QString senderText  = qvariant_cast<QString>(index.data(MailListModel::senderTextRole));
    QString whenText    = qvariant_cast<QString>(index.data(MailListModel::whenTextRole));

    bool hasAttachment = qvariant_cast<bool>(index.data(MailListModel::hasAttachRole));

    if (hasAttachment) {
        attachIcon = hasatt;
    } else {
        attachIcon = noatt;
    }

    QSize iconsize = attachIcon.actualSize(option.decorationSize);

    QRect iconRect    = option.rect;
    QRect subjectRect = option.rect;
    QRect senderRect  = subjectRect;
    QRect whenRect    = subjectRect;

    iconRect.setRight(iconRect.right() - 10);
    iconRect.setLeft(iconRect.right() - iconsize.width() - 10);
    iconRect.setTop(iconRect.top() - 10);

    subjectRect.setLeft(subjectRect.left() + 16);
    subjectRect.setRight(iconRect.left());
    subjectRect.setTop(subjectRect.top() + 5);
    subjectRect.setBottom(subjectRect.top() + fm.height());

    senderRect.setLeft(subjectRect.left() + 16);
    senderRect.setRight(iconRect.left() - 2);
    senderRect.setTop(subjectRect.bottom() + 2);
    whenRect.setTop(subjectRect.bottom() + 2);
    whenRect.setRight(iconRect.right() - 8);
    whenRect.setLeft(subjectRect.right() - fm.width(whenText) - 16);

    painter->drawPixmap(QPoint(iconRect.left() + iconsize.width() / 2 + 2, iconRect.top() + iconsize.height() / 2 + 3),
                        attachIcon.pixmap(iconsize.width(), iconsize.height()));

    painter->setFont(font);
    painter->drawText(subjectRect, Qt::AlignLeft, subjectText);

    painter->setFont(SubFont);
    painter->drawText(senderRect, Qt::AlignLeft, senderText);
    painter->drawText(whenRect, Qt::AlignRight, whenText);

    painter->restore();
}

QSize MailListDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QFont font = QApplication::font();
    QFontMetrics metric(font);
    QString subject = qvariant_cast<QString>(index.data(MailListModel::subjectTextRole));
    QSize size;
    size.setWidth(metric.width(subject) + 4 + hasatt.actualSize(option.decorationSize).width());
    size.setHeight(qMax(2 * metric.height(), hasatt.actualSize(option.decorationSize).height()) + 8);
    return size;
}

MailListDelegate::~MailListDelegate()
{
}
