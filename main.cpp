#include <QApplication>
#include <QWidget>
#include <QFile>
#include <QDir>
#include <QFileInfo>

#include <iostream>

#include "test/testp1.h"
#include "window/main_window.h"
#include "Fbyte.h"
#include "Fcalc.h"
#include "Tvlog.h"

using namespace std;


// 读取指定目录下的所有样式表
QString read_file_qss(QString path)
{
    QString style;
    QDir dir(path);
    auto ls = dir.entryList();
    for(auto &a:ls)
    {
        QFileInfo info(path + a);
        if(info.isFile() && info.suffix() == "qss")
        {
            QFile fs(info.absoluteFilePath());
            if(fs.open(QIODevice::ReadOnly))
            {
                style += fs.readAll();
                fs.close();
            }
        }
    }
    return style;
}

int run_main_app(int argc, char *argv[])
{
    QApplication a(argc,argv);

    auto sstyle = read_file_qss("../config/style/default/");
    qApp->setStyleSheet(sstyle);
    // vlogd($Q(sstyle));

    main_window w;
    w.show();

    return a.exec();
}

int exit_main_app(int run_value)
{
    cout<<"exit run value : "<<run_value<<endl;
    return run_value;
}

int perse_arg(int argc, char *argv[])
{
    cout<<"perse_arg : "<<argc<<endl;
    for(int i=0;i<argc;i++)
    {
        cout<<"arg: "<<string(argv[i])<<endl;
    }
    return argc;
}

int main(int argc, char *argv[])
{
    Tvlogs::get()->set_level(vlevel4::e_info);

    vlogd("== begin ==");


#if 0
    test_12();
    return 0;
#endif

    perse_arg(argc,argv);

    int run_value = run_main_app(argc,argv);

    return exit_main_app(run_value);
}