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

// 描述主菜单的状态
enum class MainMenu{
    HomePage,
    CollectPage
};

// 描述图片源是全部还是分类后
enum class ImageSource{
    All,
    Classfly
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    const static int smRowItemNum = 3;
    const static int smColumnItemNum = 3;
    const static int smItemNum = smRowItemNum * smColumnItemNum;
    const static int smVisibleButtonCount = 7; // 设置分页栏显示的按钮个数

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /*
     * 初始化省略号按钮
     */
    void initEllipsisButton();

    /*
     * 初始化传入的listWidget
     */
    void initListWigdet(QListWidget *listWidget);

    /*
     * 根据传入的参数来判断需要调入哪一个页面的数据，返回一个int类型作为DataManagers的索引
     */
    int getCurMenuNum(MainMenu mainMenu);

    /*
     * 对菜单初始化按钮列表，视图item
     */
    void addImageToListWidget(MainMenu mainMenu, QListWidget *listWidget, QList<QPushButton *> &buttonList);

    /*
     * 更新对应菜单下的page页的图片
     */
    void updateListWidget(MainMenu mainMenu, int page, QListWidget *listWidget, QList<ImageDataInfo> imageInfoList);

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
private:
    /*
     * 去除layout中的按钮列表
     */
    void clearPaingLayout();

    /*
     * 显示当前分页控件的布局，由clickedId控制， buttonList是所需要的按钮列表
     */
    void changePagingButton(const int clickedId, QList<QPushButton *> &buttonList, const int buttonCount);

    /*
     * 执行流程：
     *    先对保存分页控件的容器清空，再设置要显示按钮的个数
     *    然后统计参数buttonList的个数，表示有多少个按钮
     *    根据当前按钮个数和需要显示的按钮个数的大小， 判断是否需要省略号按钮
     */
    void curPaging(const int clickedId, QList<QPushButton *> &buttonList, const int buttonCount);

    /*
     * 函数功能：
     *   点击分页按钮后，视图显示对应按钮的图片，并更新分页控件的格式
     */
    void clickPagingButton(int num, QListWidget *listWidget, QList<QPushButton *> &buttonList); //当点击一个按钮后，需要进行的操作

private slots:
    /*
     * 分页按钮点击后执行的槽函数
     */
    void clickPaging();

    /*
     * 首页按钮点击后执行的槽函数
     */
    void on_homeButton_clicked();

    /*
     * 收藏页按钮点击后执行的槽函数
     */
    void on_collectButton_clicked();

    void on_all_clicked();

    void on_dongman_clicked();

    void on_dongwu_clicked();

    void on_fengjing_clicked();

    void on_jianyue_clicked();

    void on_youxi_clicked();

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
    MainMenu mMainMenu; // 枚举值，起标记作用
    ImageSource mImageSource;
};

#endif // MAINWINDOW_H
