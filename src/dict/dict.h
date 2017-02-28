#ifndef DICT_H
#define DICT_H
#include <memory>
#include <gui/Gui.h>
#include "dictlogo.h"
#include <app/application.h>
#include "shanbaydict.h"
#include <app/config.h>
enum class ShowType{balloon,main};
namespace DICT{
    extern std::unique_ptr<Gui> gui;
    extern std::unique_ptr<Application> app;
    extern std::unique_ptr<ShanbayDict> shanbayDict;
    extern std::unique_ptr<Config> cfg;
    extern Dictlogo* logo;
    extern ShowType showType;
    void init();
    void queryWord(const QString& word);
}


#endif // DICT_H
