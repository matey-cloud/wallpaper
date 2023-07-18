/*
 * author       :  YangLi
 * date         :  2023-07-18
 * description  :  MainWindow是对壁纸应用程序整体框架的设计
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QFile>
#include <QScrollBar>
#include <QList>
#include <QMap>
#include <QFileInfo>
#include <QIcon>

#include "imageinfoitem.h"
#include "imagedatainfo.h"
#include "datamanager.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initListWigdet();
    void updateListWidget(int page);

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

private slots:


private:
    Ui::MainWindow *ui;

    bool m_moveing;
    QPoint m_movePosition;

};

#endif // MAINWINDOW_H
