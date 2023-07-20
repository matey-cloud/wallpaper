/*
 * author       :  YangLi
 * date         :  2023-07-18
 * description  :  MainWindow是对壁纸应用程序整体框架的设计
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>//鼠标事件
#include <QFile>
#include <QScrollBar>
#include <QList>
#include <QFileInfo> //
#include <QIcon>
#include <QHBoxLayout>
#include <QPushButton>
#include <QtGlobal>//需要用到qMax和qMin

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

    static const int smVisibleButtonCount = 7;

    void initListWigdet();
    void addImageToListWidget();
    void updateListWidget(int page);

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
private:
    void clearPaingLayout();
    void changePagingButton(const int clickedId);
    void curPaging(const int clickedId);


private slots:
    void clickPagingButton();

private:
    Ui::MainWindow *ui;

    DataManager *mDataManager; // 获取壁纸信息的类
    bool m_moveing;
    QPoint m_movePosition;
    QList<QPushButton*> mButtonList; //按钮列表，保存分页按钮
    QList<QPushButton*> mUseButtonList; //保存分页控件中需要用到的按钮
    // 创建省略号按钮，
    QPushButton *mEllipsisButtonLeft;
    QPushButton *mEllipsisButtonRight;

    QHBoxLayout* mLayout; //水平显示 分页按钮

};

#endif // MAINWINDOW_H
