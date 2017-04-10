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
#ifndef DICT_H
#define DICT_H
#include <memory>
#include <gui/Gui.h>
#include <gui/dictlogo.h>
#include <app/application.h>
#include <app/config.h>
#include <dict/shanbaydict.h>
#include <dict/youdaodict.h>
enum class ShowType{balloon,main};
enum class DictType{ShanbayDict,YoudaoDict};
namespace DICT{
    extern std::unique_ptr<Gui> gui;
    extern std::unique_ptr<Application> app;
    extern std::unique_ptr<ShanbayDict> shanbayDict;
    extern std::unique_ptr<YoudaoDict> youdaoDict;
    extern std::unique_ptr<Config> cfg;
    extern Dictlogo* logo;
    extern ShowType showType;
    void init();
    void queryWord(const QString& word);
    void showWord(DictType dictType,const QString& wordinfo);
}


#endif // DICT_H
