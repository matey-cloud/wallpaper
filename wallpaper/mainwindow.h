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
#include <QListWidget>

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

    static const int smVisibleButtonCount = 7; // 设置分页栏显示的按钮个数

    void initListWigdet(QListWidget *listWidget);
    void addImageToListWidget(int num, QListWidget *listWidget, QList<QPushButton *> &buttonList);
    void updateListWidget(int num, int page, QListWidget *listWidget);

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
private:
    /*
     * 去除layout中的按钮列表
     * 执行流程：
     *   先判断mLayout中是否有buttonList的元素，有就去除，然后对该元素设置不可见
     *   接着判断省略号按钮
     */
    void clearPaingLayout();

    /*
     * 显示当前分页控件的布局，由clickedId控制， buttonList是所需要的按钮列表
     * 执行流程：
     *    先调用clearPaingLayout，清除layout中的按钮列表
     *    再调用curPaging，获取当前clickedId按钮布局需要显示的按钮，保存在mUseButtonList中
     *    最后添加到mLayout中
     */
    void changePagingButton(const int clickedId, QList<QPushButton *> &buttonList);

    /*
     * 执行流程：
     *    先对保存分页控件的容器清空，再设置要显示按钮的个数
     *    然后统计参数buttonList的个数，表示有多少个按钮
     *    根据当前按钮个数和需要显示的按钮个数的大小， 判断是否需要省略号按钮
     */
    void curPaging(const int clickedId, QList<QPushButton *> &buttonList);

    /*
     * 执行流程：
     *   获取对应按钮的文本，即编号，转为int类型
     *   然后更新当前页，再用updateListWidget更新内容显示区
     *   最后更改分页工具栏的样式
     */
    void clickPagingButton(int num, QListWidget *listWidget, QList<QPushButton *> &buttonList); //当点击一个按钮后，需要进行的操作

private slots:
    void clickPaging(); // 点击分页按钮后，根据mFlag的值来判断传入值
    void on_homeButton_clicked();
    void on_collectButton_clicked();

private:
    Ui::MainWindow *ui;

    QList<DataManager*> mDataManagers; // 获取壁纸信息
    bool mMoveing;
    QPoint mMovePosition;
    QList<QPushButton*> mHButtonList; //按钮列表，保存首页分页按钮
    QList<QPushButton*> mCButtonList; //按钮列表，保存收藏页分页按钮
    QList<QPushButton*> mUseButtonList; //保存分页控件中需要用到的按钮    

    // 省略号按钮
    QPushButton *mEllipsisButtonLeft;
    QPushButton *mEllipsisButtonRight;

    QHBoxLayout* mLayout; //水平显示 分页按钮
    int mFlag; // 标记作用， 1表示显示首页， 2表示显示收藏页，默认为1

};

#endif // MAINWINDOW_H
