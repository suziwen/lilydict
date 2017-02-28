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
