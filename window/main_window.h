
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QIcon>
#include <QDateTime>
#include <QEvent>

#include <memory>

#include "wid_input/wid_input.h"
#include "input_but_lay.h"
#include "Tvlog.h"
#include "Fbyte.h"
#include "Fcalc.h"
#include "input_edit.h"
#include "wid_list.h"


class main_window : public QWidget
{
    Q_OBJECT
public:
    main_window(QWidget *parent = nullptr);
    ~main_window();

    void init_wid(QWidget *parent);

signals:

protected:

private:

};
#endif // MAIN_WINDOW_H
