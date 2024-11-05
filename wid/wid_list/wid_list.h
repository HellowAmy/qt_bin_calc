
#ifndef WID_LIST_H
#define WID_LIST_H

#include <QWidget>
#include <QListWidget>
#include <QScrollBar>

class wid_list : public QListWidget
{
    Q_OBJECT
public:
    wid_list(QWidget *parent = nullptr);
    ~wid_list();

    void push_data(const QString &s);
    void bar_move_bottom();

signals:

protected:

private:

};
#endif // WID_LIST_H
