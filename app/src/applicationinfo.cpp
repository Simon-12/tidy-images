#include "applicationinfo.h"


ApplicationInfo::ApplicationInfo(QObject *parent) : QObject(parent)
{
    m_website = "https://github.com/Simon-12/tidy-images";
    m_report = "https://github.com/Simon-12/tidy-images/issues";
    m_version = "0.82.1";
    m_paypal = "https://paypal.me/SimonSchwarzkopf";
    m_btc = "bc1qll43hkqvv9jjwqw54xhejw324q4t4t55p8ss9e";

    m_about =
            "<font size='+2'><center><b>"
            "Tidy Images"
            "</b></font></center>"
            "<font size='+1'><center>"
            "Version: " + m_version +
            "</font></center><br>"
            "Tidy Images is an application to sort and organize your image collection. "
            "<br><br>"
            "If you like the application and want to support, you can donate via PayPal or BTC: ";

    m_story =
            "This application was published in the hope that someone would find it useful and inspiring. "
            "In the first place this application was developed for my wife, "
            "to sort her beautiful camera pictures and to find her favorite memories in a well organized database. "
            "<br><br>"
            "Thanks a lot to Bryan for the instructive Udemy courses and YouTube tutorials. "
            "With this i could improve my skills and got some good inspirations to do this project. "
            "For interested check out the links below and join the community: "
            "<ul>"
            "<li><a href='https://www.facebook.com/groups/1400884323467285/'>facebook/voidrealms</a> </li>"
            "<li><a href='https://www.youtube.com/user/VoidRealms'>youtube/voidrealms</a> </li>"
            "<li><a href='https://www.udemy.com/user/bryan-cairns/'>udemy/bryan-cairns</a> </li>"
            "</ul>"
            "Feedback, suggestions for improvements or ideas for new features are always welcome. "
            "<br>"
            "If you find bugs, please report to: "
            "<a href='" + m_report + "'>github/issues</a>"
            "<br><br><br>";

    m_license =
            "Copyright © 2015-2021 Simon Schwarzkopf"
            "<br><br>"
            "Licensed under the "
            "<a href='https://www.gnu.org/licenses/gpl-3.0.html'>GNU General Public License v3.0</a>"
            "<br><br>"
            "The source code used to build this program can be downloaded from: "
            "<a href='" + m_website + "'>github/tidy-images</a>"
            "<br><br>"
            "This program is free software: you can redistribute it and/or modify "
            "it under the terms of the GNU General Public License as published by "
            "the Free Software Foundation, either version 3 of the License, or "
            "(at your option) any later version."
            "<br><br>"
            "This program is distributed in the hope that it will be useful, "
            "but WITHOUT ANY WARRANTY; without even the implied warranty of "
            "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. "
            "See the GNU General Public License for more details. "
            "<br><br>"
            "You should have received a copy of the GNU General Public License "
            "along with this program. If not, see "
            "<a href='https://www.gnu.org/licenses/'>https://www.gnu.org/licenses/</a>. "
            "<br><br><br>";

    m_QtInfo =
            "This program uses Qt version " + QString(QT_VERSION_STR) + "<br><br>"
            "Qt is a C++ toolkit for cross-platform application development. "
            "Qt provides single-source portability across all major desktop operating systems. "
            "It is also available for embedded Linux and other embedded and mobile operating systems. "
            "<br><br>"
            "Qt is available under multiple licensing options designed to accommodate the needs of our various users. "
            "Qt licensed under GNU (L)GPL is appropriate for the development of Qt applications provided you can "
            "comply with the terms and conditions of the respective licenses. Please see "
            "<a href='https://www.qt.io/licensing/'>qt.io/licensing</a>"
            " for an overview of Qt licensing. "
            "<br><br>"
            "Copyright (C) 2020 The Qt Company Ltd and other contributors. "
            "Qt and the Qt logo are trademarks of The Qt Company Ltd. "
            "Qt is The Qt Company Ltd product developed as an open source project. See "
            "<a href='https://www.qt.io/'>qt.io</a>"
            " for more information. "
            "<br><br><br>";

    m_model = new IconModel(this);
    initFlatIcons();
    initMaterialIcons();
}


void ApplicationInfo::loadFonts()
{
    QDirIterator it(":/fonts");
    while(it.hasNext())
    {
        QString name = it.next();
        QFontDatabase::addApplicationFont(name);
    }
}


void ApplicationInfo::initFlatIcons()
{
    QFile file(":/icons/flaticon/reference.txt");
    if(!file.open(QIODevice::ReadOnly))
    {
        qCritical() << "Could not read file! \n" + file.errorString();
        return;
    }

    QString data = file.readAll();
    QStringList list = data.split("\r\n\r\n");

    foreach(QString line, list)
    {
        QStringList icon = line.split("\r\n");
        if(icon.last() == "") icon.removeLast(); // Remove empty
        if(icon.size() > 3) icon.removeAt(1); // Remove duplicates

        QString author = icon[2];
        int pos1 = author.indexOf('\"') + 1;
        int pos2 = author.indexOf('\"', pos1) - pos1;
        author = author.mid(pos1, pos2);

        // Add to model
        IconItem item(icon[0], "qrc:/icons/flaticon/", icon[1], author);
        m_model->append(item);
    }
}


void ApplicationInfo::initMaterialIcons()
{
    QFile file(":/icons/material/reference.txt");
    if(!file.open(QIODevice::ReadOnly))
    {
        qCritical() << "Could not read file! \n" + file.errorString();
        return;
    }

    QString data = file.readAll();
    QStringList list = data.split("\r\n");

    int pos = list.indexOf("");
    QString link = list[pos + 1];
    QString author = list[pos + 2];

    for(int i = 0; i < pos; i++)
    {
        // Add to model
        IconItem item(list[i], "qrc:/icons/material/", link, author);
        m_model->append(item);
    }
}
