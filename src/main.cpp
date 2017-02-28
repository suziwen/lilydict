/****************************************************************************
**
** Copyright (C) 2016 lieefu Way.
** All rights reserved.
** Contact: lieefu@gmail.com
**
** This file is part of the ShanbayDict.
**
** $BEGIN_LICENSE:LGPL$
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 3 as published by the Free Software Foundation and
** appearing in the file LICENSE included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 3 requirements will be met:
** http://www.gnu.org/licenses/lgpl.html.
**
** $END_LICENSE$
**                                                    2016/5/5
****************************************************************************/
#include <QApplication>
#include <dict/dict.h>

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
#ifdef Q_OS_LINUX
    QFont font;
    font.setFamily("WenQuanYi Micro Hei");
    qApp->setFont(font);
#endif
    DICT::app->run();
    return app.exec();
 }
