
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mEllipsisButtonLeft(nullptr)
    , mEllipsisButtonRight(nullptr)
    , mLayout(nullptr)
    , mMainMenu(MainMenu::HomePage) // 默认首页
    , mImageSource(ImageSource::All) // 默认使用全部图片
{
    ui->setupUi(this);
    //去掉软件标题栏，自己来实现  Qt::FramelessWindowHint
    //设置窗体透明，但里面的控件不透明,这个可以用来做不规则的窗体效果
    //如果是规则的矩形窗体这个可以不用
    // setAttribute(Qt::WA_TranslucentBackground,true);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    setWindowIcon(QIcon(":/icons/application.ico"));//可执行程序图标
    setWindowTitle("小亦壁纸");

    mLayout = new QHBoxLayout(ui->tool);
    ui->tool->setLayout(mLayout);
    mLayout->setAlignment(Qt::AlignLeft); // 分页按钮向左对齐

    // 初始化省略号按钮
    initEllipsisButton();

    //初始化QlistWidget
    initListWigdet(ui->listWidget);
    initListWigdet(ui->listWidget_2);

    // 默认显示首页界面，所以传入1获取对应文件夹的壁纸，并计算多少页
    addImageToListWidget(MainMenu::HomePage, ui->listWidget, mHButtonList);
    // 收藏页
    addImageToListWidget(MainMenu::CollectPage, ui->listWidget_2, mCButtonList);


    // 默认显示首页的内容
    on_homeButton_clicked();

//    // 给item绑定真实数据,默认更新第一页的数据
//    updateListWidget(MainMenu::HomePage, 1, ui->listWidget, mDataManagers[0]->getImagesOfPage(1));
//    // 设置按钮在首页中默认的显示规则,从按钮1开始
//    changePagingButton(1, mHButtonList, mDataManagers[0]->totalPage());

//    updateListWidget(MainMenu::CollectPage, 1, ui->listWidget_2, mDataManagers[1]->getImagesOfPage(1));

//    // 显示首页
//    ui->stackedWidget->setCurrentIndex(0);

}

MainWindow::~MainWindow()
{
    delete mEllipsisButtonRight;
    delete mEllipsisButtonLeft;
    for(auto &button: mCButtonList){
        delete button;
    }
    for(auto &button: mHButtonList){
        delete button;
    }

    for(auto manager: mDataManagers){
        delete manager;
    }
    delete mLayout;
    delete ui;
}

//重写鼠标按下事件
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    mMoveing = true;
    //记录下鼠标相对于窗口的位置
    //event->globalPos()鼠标按下时，鼠标相对于整个屏幕位置
    //pos() this->pos()鼠标按下时，窗口相对于整个屏幕位置
    mMovePosition = event->globalPos() - pos();
    QWidget::mousePressEvent(event);
}

//重写鼠标移动事件
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    //(event->buttons() & Qt::LeftButton)按下是左键
    //鼠标移动事件需要移动窗口，窗口移动到哪里呢？就是要获取鼠标移动中，窗口在整个屏幕的坐标，然后move到这个坐标，怎么获取坐标？
    //通过事件event->globalPos()知道鼠标坐标，鼠标坐标减去鼠标相对于窗口位置，就是窗口在整个屏幕的坐标
    if (mMoveing && (event->buttons() & Qt::LeftButton)
        && (event->globalPos()-mMovePosition).manhattanLength() > QApplication::startDragDistance())
    {
        move(event->globalPos()-mMovePosition);
        mMovePosition = event->globalPos() - pos();
    }
    QWidget::mouseMoveEvent(event);
}

//鼠标释放
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    mMoveing = false;
    QWidget::mouseReleaseEvent(event);
}

/*
 * 初始化省略号按钮，分页控件中需要用到两个
 */
void MainWindow::initEllipsisButton()
{
    mEllipsisButtonLeft = new QPushButton("...");
    mEllipsisButtonRight = new QPushButton("...");
    // 不可点击
    mEllipsisButtonLeft->setEnabled(false);
    mEllipsisButtonRight->setEnabled(false);
    mEllipsisButtonLeft->setFixedSize(35, 35); // 设置按钮大小
    mEllipsisButtonRight->setFixedSize(35, 35); // 设置按钮大小
}

/*
 * 初始化传入的listWidget
 */
void MainWindow::initListWigdet(QListWidget *listWidget){
    // 获取容器QlistWidget的长度和宽度
    int itemWidth = (listWidget->width()-20) / smRowItemNum;
    int itemHeight = (listWidget->height()) / smRowItemNum;

    //初始化QListWidget
    listWidget->setIconSize(QSize(itemWidth,itemHeight)); // 每个Item的大小
    listWidget->setResizeMode(QListView::Adjust);
    listWidget->setViewMode(QListView::IconMode);
    //设置不能移动
    listWidget->setMovement(QListView::Static);
    listWidget->setSpacing(0);
    listWidget->horizontalScrollBar()->setDisabled(true);
    listWidget->verticalScrollBar()->setDisabled(true);
    listWidget->setStyleSheet("QListWidget::Item:hover{background-color:rgba(47,46,46,0);border-radius:5px; }"
                              "QListWidget::item:selected{background-color:rgba(47,46,46,0);color:rgb(61,61,61);border:2px solid #FFC53D;border-radius:5px; }"
                              "QScrollBar:vertical{width:0px}");
    listWidget->setFocusPolicy(Qt::NoFocus);//文字没虚线
    listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    //    connect(ui->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(listWidgetClicked(QListWidgetItem*)));
}

/*
 * 根据传入的参数来判断需要调入哪一个页面的数据，返回一个int类型作为DataManagers的索引
 */
int MainWindow::getCurMenuNum(MainMenu mainMenu){
    int num = -1;
    switch (mainMenu) {
    case MainMenu::HomePage:
        num = 1;
        break;
    case MainMenu::CollectPage:
        num = 2;
        break;
    default:
        num = -1;
        break;
    }
    return num;
}

/*
 * new一个DataManager，并将该对象保存到成员变量mDatamanagers中，这个对象和当前界面绑定，图片资源从这个对象获取
 * 根据当前菜单获取num值，num-1是mDatamanagers的索引
 * 并根据num值来获取对应菜单内容的页数
 * 每个页面对应一个按钮，添加到buttonList中，
 * 一个页面对应6个ImageInfoItem，即6张图片，对每一页初始化
 */
void MainWindow::addImageToListWidget(MainMenu mainMenu, QListWidget* listWidget, QList<QPushButton *> &buttonList)
{
    DataManager* manager = new DataManager();
    manager->setPageImageNum(smItemNum);
    mDataManagers.push_back(manager);

    // 获取容器QlistWidget的长度和宽度
    QSize itemSize = listWidget->iconSize();
    int num = getCurMenuNum(mainMenu);

    // 读取对应num的图片文件夹, 并计算有多少页
    mDataManagers[num-1]->getImages(num);
    // 获取有多少页
    int pages = mDataManagers[num-1]->totalPage();

    for(int n = 1; n <= pages; ++n){
        // 每页创建一个按钮
        QPushButton* button = new QPushButton(QString::number(n));// 按钮以页数命名
        button->setFixedSize(35, 35); // 设置按钮大小

        // 设置样式表
        QFile file(":/qss/button.qss");
        file.open(QFile::ReadOnly);
        QString styleSheet = tr(file.readAll());
        button->setStyleSheet(styleSheet);
        file.close();

        //绑定分页按钮点击事件
        QObject::connect(button, &QPushButton::clicked, this, &MainWindow::clickPaging);
        button->setVisible(false);
        buttonList.append(button); // buttonList.push_back(button)，将按钮添加到按钮列表末尾

        // 创建单元项
        // 这里创建的Item使用的背景图是样式表中的默认背景图
        for (int i = 0; i < smItemNum; ++i)
        {
            QListWidgetItem *item = new QListWidgetItem(listWidget);
            ImageInfoItem *widget = new ImageInfoItem;
            item->setSizeHint(itemSize);
            listWidget->addItem(item);
            //最重要的是这句将Item设置为一个Widget，而这个Widget就是自定义的ui
            //将ImageInfoItem部件与相应的QListWidgetItem关联起来
            listWidget->setItemWidget(item, widget);
        }
    }
}

/*
 * imageInfoList是该页需要的图片
 * listWidget是图片显示的视图
 * 再将图片添加到每一个item中
 */
void MainWindow::updateListWidget(MainMenu mainMenu, int page, QListWidget* listWidget, QList<ImageDataInfo> imageInfoList){
    int num = getCurMenuNum(mainMenu); // 创建每个Item时，右击生成的菜单需要

    //    //获取第page页面的数据当在imageInfoList中
    //    QList<ImageDataInfo> imageInfoList = mDataManagers[num-1]->getImagesOfPage(page);
    //先初始化listWidget列表的每一项为空数据
    for (int i = 0; i < smItemNum; ++i)
    {
        QListWidgetItem *item = listWidget->item(i);
        QWidget *widget = listWidget->itemWidget(item);
        ImageInfoItem* imageInfoItem = dynamic_cast<ImageInfoItem*>(widget);
        if(imageInfoItem != nullptr){
            ImageDataInfo info;//空数据
            imageInfoItem->addImage(info);
            listWidget->setItemWidget(item, imageInfoItem);
        }
    }
    //根据实际上得到的imageInfoList初始化listWidget
    for (int i = 0; i < imageInfoList.size(); ++i)
    {
        QListWidgetItem *item = listWidget->item(i);
        item->setHidden(false);
        QWidget * widget = listWidget->itemWidget(item);
        ImageInfoItem* imageInfoItem = dynamic_cast<ImageInfoItem*>(widget);
        if (imageInfoItem != nullptr) {
            imageInfoItem->RightClickMenu(num);
            imageInfoItem->addImage(imageInfoList[i]);
            // 设置 ImageInfoItem 作为 QListWidgetItem 的自定义小部件
            listWidget->setItemWidget(item, imageInfoItem);

            if(num == 1)
                QObject::connect(imageInfoItem, SIGNAL(clickCollectMenu(ImageInfoItem*)), this, SLOT(addCollection(ImageInfoItem*)));
            else if(num == 2)
                QObject::connect(imageInfoItem, SIGNAL(clickCollectMenu(ImageInfoItem*)), this, SLOT(removeCollection(ImageInfoItem*)));
        }
    }

    // 对最后一页的处理
    //    if(imageInfoList.size() != smItemNum){
    //        for(int i = imageInfoList.size(); i < smItemNum; ++i){
    //            QListWidgetItem *item = listWidget->item(i);
    //            item->setHidden(true);
    //        }
    //    }
}

/*
 * 执行流程：
 *   去除layout中的按钮列表
 *   先判断mLayout中是否又buttonList的元素，有就去除，然后对该元素设置不可见
 *   接着判断省略号按钮
 */
void MainWindow::clearPaingLayout()
{
    // 首页按钮
    for (int i = 0; i < mHButtonList.count(); ++i) {
        if (mLayout->indexOf(mHButtonList[i]) != -1) {
            mLayout->removeWidget(mHButtonList[i]);
            mHButtonList[i]->setVisible(false);
        }
    }
    // 收藏页按钮
    for (int i = 0; i < mCButtonList.count(); ++i) {
        if (mLayout->indexOf(mCButtonList[i]) != -1) {
            mLayout->removeWidget(mCButtonList[i]);
            mCButtonList[i]->setVisible(false);
        }
    }

    if (mLayout->indexOf(mEllipsisButtonLeft) != -1){
        mLayout->removeWidget(mEllipsisButtonLeft);
        mEllipsisButtonLeft->setVisible(false);
    }
    if (mLayout->indexOf(mEllipsisButtonRight) != -1){
        mLayout->removeWidget(mEllipsisButtonRight);
        mEllipsisButtonRight->setVisible(false);
    }
}

/*
 * 显示当前分页控件的布局，由clickedId控制， buttonList是所需要的按钮列表
 * 执行流程：
 *   先调用clearPaingLayout，清除layout中的按钮列表
 *   再调用curPaging，获取当前clickedId按钮布局需要显示的按钮，保存在mUseButtonList中
 *   最后添加到mLayout中
 */
void MainWindow::changePagingButton(const int clickedId, QList<QPushButton *> &buttonList, const int buttonCount)
{
    clearPaingLayout(); // 清空当前布局mLayout中的Button

    curPaging(clickedId, buttonList, buttonCount);// 获取当前布局需要的按钮
    int count = mUseButtonList.count();
    for(int i = 0; i < count ; ++i){
        mUseButtonList[i]->setVisible(true);
        mLayout->addWidget(mUseButtonList[i]);
    }
    ui->tool->setLayout(mLayout);
}

/*
 * 执行流程：
 *    先对保存分页控件的容器清空，再设置要显示按钮的个数
 *    然后统计参数buttonList的个数，表示有多少个按钮
 *    根据当前按钮个数和需要显示的按钮个数的大小， 判断是否需要省略号按钮
 */
void MainWindow::curPaging(const int clickedId, QList<QPushButton *> &buttonList, const int buttonCount){

    mUseButtonList.clear();
    // 按钮列表中设置显示smVisibleButtonCount个
    int visibleButtonCount = smVisibleButtonCount;

    // 如果可见按钮的数量比总页数还大，显示所有的按钮，不需要省略号按钮
    // 执行后退出
    if(buttonCount <= visibleButtonCount){
        for(int i = 0; i < buttonCount; ++i){
            buttonList[i]->setVisible(true);
            mUseButtonList.append(buttonList[i]);
        }
        return;
    }

    if(clickedId <= visibleButtonCount / 2 + 1){ // 需要右省略号按钮（出现在点击按钮的右边）
        // 省略号左边的按钮
        for(int i = 0; i < visibleButtonCount - 1; ++i){
            buttonList[i]->setVisible(true);
            mUseButtonList.append(buttonList[i]);
            qDebug() << buttonList[i]->text();
        }
        mEllipsisButtonRight->setVisible(true);
        mUseButtonList.append(mEllipsisButtonRight);// 添加右省略按钮
        buttonList.last()->setVisible(true);
        mUseButtonList.append(buttonList.last());

    } else if(clickedId >= buttonCount - (visibleButtonCount / 2)){ // 需要左省略号按钮（出现在点击按钮的左边）
        buttonList.first()->setVisible(true);
        mUseButtonList.append(buttonList.first());
        mEllipsisButtonLeft->setVisible(true);
        mUseButtonList.append(mEllipsisButtonLeft);
        for(int i = buttonCount - visibleButtonCount + 1; i < buttonCount; ++i){
            buttonList[i]->setVisible(true);
            mUseButtonList.append(buttonList[i]);
            qDebug() << buttonList[i]->text();
        }
    } else { //两个按钮都需要
        buttonList.first()->setVisible(true);
        mUseButtonList.push_back(buttonList.first()); // 添加1号按钮
        mEllipsisButtonLeft->setVisible(true);
        mUseButtonList.push_back(mEllipsisButtonLeft);// 添加左省略号按钮
        for(int i = clickedId - visibleButtonCount / 2; i <= clickedId +1; ++i){
            buttonList[i]->setVisible(true);
            mUseButtonList.push_back(buttonList[i]);
            qDebug() << buttonList[i]->text();
        }
        mEllipsisButtonRight->setVisible(true);
        mUseButtonList.push_back(mEllipsisButtonRight);// 添加右省略号按钮
        buttonList.last()->setVisible(true);
        mUseButtonList.push_back(buttonList.last());
    }
}

/*
 * 函数功能：
 *   点击分页按钮后，视图显示对应按钮的图片，并更新分页控件的格式
 * 参数：
 *   num -
 * 执行流程：
 *   获取对应按钮的文本，即编号，转为int类型
 *   然后更改分页工具栏的样式
 *   最后更新当前页，再用updateListWidget更新内容显示区
 */
void MainWindow::clickPagingButton(int num, QListWidget *listWidget, QList<QPushButton *> &buttonList)
{
    QPushButton* button = qobject_cast<QPushButton*>(sender()); // 获取发出信号的按钮

    if(button){
        // 更新对应页数的壁纸
        QString buttonText = button->text();
        int clickedId = buttonText.toInt(); // 获取点击的第几页
        mDataManagers[num-1]->setCurPage(clickedId);
        int curPage = mDataManagers[num-1]->curPage();

        QList<ImageDataInfo> imageList;
        int buttonCount = 0;
        // 判断使用的图片是分类的图片还是全部图片
        // 以及按钮的个数
        if(mImageSource == ImageSource::All){
            imageList = mDataManagers[num-1]->getImagesOfPage(curPage);
            buttonCount = mDataManagers[num-1]->totalPage();
        }
        else{
            imageList = mDataManagers[num-1]->getClassflyImagesOfPage(curPage);
            buttonCount = mDataManagers[num-1]->classflyTotalPage();
        }

        for(auto& b : buttonList){
            if(b != button){
                b->setEnabled(true);
                QFile file(":/qss/button.qss");
                file.open(QFile::ReadOnly);
                QString styleSheet = tr(file.readAll());
                b->setStyleSheet(styleSheet);
                file.close();

            } else { // 将被点击的按钮设置为另一个样式
                b->setEnabled(false);
                QFile file(":/qss/clickedButton.qss");
                file.open(QFile::ReadOnly);
                QString styleSheet = tr(file.readAll());
                b->setStyleSheet(styleSheet);
                file.close();
            }
        }


        updateListWidget(mMainMenu, curPage, listWidget, imageList);
        // 更改分页工具栏的样式
        changePagingButton(clickedId, buttonList, buttonCount);

    }
}
/*
 * 这是分页按钮点击信号对应的槽函数
 * 根据getCurMenuNum的返回值来判断点击的是哪个页面的按钮，
 */
void MainWindow::clickPaging(){
    int num = getCurMenuNum(mMainMenu);
    if(num == 1)
        clickPagingButton(num, ui->listWidget, mHButtonList);
    else if(num == 2){
        clickPagingButton(num, ui->listWidget_2, mCButtonList);
    }
}

/*
 * 点击首页按钮后，先更改mMainMenu的值，标识首页
 * 然后更新首页页面的图片，显示第一页
 * 再更改分页控件的布局
 * 最后显示首页
 */
void MainWindow::on_homeButton_clicked()
{
    mMainMenu = MainMenu::HomePage;
    mImageSource = ImageSource::All;

    // 初始化被点击的按钮
    QFile file(":/qss/clickedButton.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = tr(file.readAll());

    // 初始化第一个分页按钮的样式
    mHButtonList[0]->setStyleSheet(styleSheet);
//    mCButtonList[0]->setStyleSheet(styleSheet);
    ui->homeButton->setStyleSheet(styleSheet);
    ui->all->setStyleSheet(styleSheet);
    file.close();

    // 改变样式
    QFile file1(":/qss/button.qss");
    file1.open(QFile::ReadOnly);
    styleSheet = tr(file1.readAll());
    ui->collectButton->setStyleSheet(styleSheet);
    for(int i = 1; i < mHButtonList.size(); ++i){
        mHButtonList[i]->setStyleSheet(styleSheet);
    }
    file1.close();


    // 初始化第一个分页按钮，首页中分类按钮的“全部”按钮，首页按钮和收藏按钮， 设置对应的点击状态
    mHButtonList[0]->setEnabled(false);
//    mCButtonList[0]->setEnabled(false);
    ui->all->setEnabled(false);
    ui->homeButton->setEnabled(false);
    ui->collectButton->setEnabled(true);

    // 更改为第一页的分页按钮样式
    changePagingButton(1, mHButtonList, mDataManagers[0]->totalPage());
    // 显示第一页的内容
    updateListWidget(MainMenu::HomePage, 1, ui->listWidget, mDataManagers[0]->getImagesOfPage(1));

    ui->stackedWidget->setCurrentIndex(0);

}

/*
 * 点击收藏按钮后，先更改mMainMenu的值，标识收藏页
 * 然后更新收藏页页面的图片，显示第一页
 * 再更改分页控件的布局
 * 最后显示收藏页
 */
void MainWindow::on_collectButton_clicked()
{
    mMainMenu = MainMenu::CollectPage;
    mImageSource = ImageSource::All;

    // 初始化被点击的按钮
    QFile file(":/qss/clickedButton.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = tr(file.readAll());

    // 初始化第一个分页按钮的样式
    mCButtonList[0]->setStyleSheet(styleSheet);
    ui->collectButton->setStyleSheet(styleSheet);
    file.close();

    // 改变样式
    QFile file1(":/qss/button.qss");
    file1.open(QFile::ReadOnly);
    styleSheet = tr(file1.readAll());
    ui->homeButton->setStyleSheet(styleSheet);
    for(int i = 1; i < mCButtonList.size(); ++i){
        mCButtonList[i]->setStyleSheet(styleSheet);
    }
    file1.close();


    // 初始化第一个分页按钮，设置对应的点击状态
    mCButtonList[0]->setEnabled(false);
    ui->homeButton->setEnabled(true);
    ui->collectButton->setEnabled(false);

    changePagingButton(1, mCButtonList, mDataManagers[1]->totalPage());
    updateListWidget(MainMenu::CollectPage, 1, ui->listWidget_2, mDataManagers[1]->getImagesOfPage(1));

    ui->stackedWidget->setCurrentIndex(1);
}

/*
 * 判断分类按钮是否点击，如果点击了设置该按钮不可点击，其他按钮可被点击
 * 并设置样式
 */
void MainWindow::isClickClassflyButton(QPushButton* button){
    QList<QPushButton*> buttonList;
    buttonList.push_back(ui->all);
    buttonList.push_back(ui->dongman);
    buttonList.push_back(ui->dongwu);
    buttonList.push_back(ui->fengjing);
    buttonList.push_back(ui->jianyue);
    buttonList.push_back(ui->youxi);
    for(auto& b : buttonList){
        if(b != button){
            b->setEnabled(true);
            QFile file(":/qss/button.qss");
            file.open(QFile::ReadOnly);
            QString styleSheet = tr(file.readAll());
            b->setStyleSheet(styleSheet);
            file.close();

        } else { // 将被点击的按钮设置为另一个样式
            b->setEnabled(false);
            QFile file(":/qss/clickedButton.qss");
            file.open(QFile::ReadOnly);
            QString styleSheet = tr(file.readAll());
            b->setStyleSheet(styleSheet);
            file.close();
        }
    }
    // 默认显示的第一页， 所以需要重新设置分页按钮
    initHomeButtonList();
}

/*
 * 初始化首页中的分页按钮，由addImageToListWidget创建
 * 在点击分类按钮后会使用
 * 将第一个按钮设置为不可点击，其他按钮设置为可点击
 */
void MainWindow::initHomeButtonList()
{
    for(int i = 0; i < mHButtonList.size(); ++i){
        if(i != 0){
            mHButtonList[i]->setEnabled(true);
            QFile file(":/qss/button.qss");
            file.open(QFile::ReadOnly);
            QString styleSheet = tr(file.readAll());
            mHButtonList[i]->setStyleSheet(styleSheet);
            file.close();

        } else { // 将被点击的按钮设置为另一个样式
            mHButtonList[i]->setEnabled(false);
            QFile file(":/qss/clickedButton.qss");
            file.open(QFile::ReadOnly);
            QString styleSheet = tr(file.readAll());
            mHButtonList[i]->setStyleSheet(styleSheet);
            file.close();
        }
    }

}

void MainWindow::on_all_clicked()
{
    mImageSource = ImageSource::All;
    isClickClassflyButton(ui->all);
    updateListWidget(MainMenu::HomePage, 1, ui->listWidget, mDataManagers[0]->getImagesOfPage(1));
    changePagingButton(1, mHButtonList, mDataManagers[0]->totalPage());
}


void MainWindow::on_dongman_clicked()
{
    mImageSource = ImageSource::Classfly;
    mDataManagers[0]->getClassflyImages("动漫");
    isClickClassflyButton(ui->dongman);
    changePagingButton(1, mHButtonList, mDataManagers[0]->classflyTotalPage());
    updateListWidget(MainMenu::HomePage, 1, ui->listWidget, mDataManagers[0]->getClassflyImagesOfPage(1));

}


void MainWindow::on_dongwu_clicked()
{
    mImageSource = ImageSource::Classfly;
    mDataManagers[0]->getClassflyImages("动物");
    isClickClassflyButton(ui->dongwu);
    changePagingButton(1, mHButtonList, mDataManagers[0]->classflyTotalPage());
    updateListWidget(MainMenu::HomePage, 1, ui->listWidget, mDataManagers[0]->getClassflyImagesOfPage(1));

}


void MainWindow::on_fengjing_clicked()
{
    mImageSource = ImageSource::Classfly;
    mDataManagers[0]->getClassflyImages("风景");
    isClickClassflyButton(ui->fengjing);
    changePagingButton(1, mHButtonList, mDataManagers[0]->classflyTotalPage());
    updateListWidget(MainMenu::HomePage, 1, ui->listWidget, mDataManagers[0]->getClassflyImagesOfPage(1));

}


void MainWindow::on_jianyue_clicked()
{
    mImageSource = ImageSource::Classfly;
    mDataManagers[0]->getClassflyImages("简约");
    isClickClassflyButton(ui->jianyue);
    changePagingButton(1, mHButtonList, mDataManagers[0]->classflyTotalPage());
    updateListWidget(MainMenu::HomePage, 1, ui->listWidget, mDataManagers[0]->getClassflyImagesOfPage(1));

}


void MainWindow::on_youxi_clicked()
{
    mImageSource = ImageSource::Classfly;
    mDataManagers[0]->getClassflyImages("游戏");
    isClickClassflyButton(ui->youxi);
    changePagingButton(1, mHButtonList, mDataManagers[0]->classflyTotalPage());
    updateListWidget(MainMenu::HomePage, 1, ui->listWidget, mDataManagers[0]->getClassflyImagesOfPage(1));

}


void MainWindow::on_searchButton_clicked()
{
    int num = getCurMenuNum(mMainMenu);
    mImageSource = ImageSource::Classfly;
    mDataManagers[num-1]->getClassflyImages(ui->searchText->text());
    changePagingButton(1, mHButtonList, mDataManagers[num-1]->classflyTotalPage());
    QListWidget* listWidget;
    if(num == 1){
        listWidget = ui->listWidget;
    } else if(num == 2){
        listWidget = ui->listWidget_2;
    }
    updateListWidget(MainMenu::HomePage, 1, listWidget, mDataManagers[num-1]->getClassflyImagesOfPage(1));

}

void MainWindow::addCollection(ImageInfoItem* imageItem){
    QFileInfo imageInfo(imageItem->path());
    QImage image(imageInfo.filePath());

    // 构造文件名
    QString fileName = "D:\\CandC++\\C++\\wallpaper\\collect\\默认\\" + imageInfo.fileName();

    // 创建文件对象
    QFile file(fileName);

    // 打开文件（只写模式）
    if (file.open(QIODevice::WriteOnly))
    {
        // 保存图片到文件
        if (image.save(&file)){
            // 关闭文件
            file.close();
        }else{
            // 保存失败
            file.close();
            QMessageBox::information(this, tr("小亦壁纸"),
                                 tr("收藏失败.\n"));
        }
    }else{
        // 打开文件失败
    }
    updateCollection();
}

void MainWindow::removeCollection(ImageInfoItem* imageItem){

    QString filePath = imageItem->path();
    // 创建QFileInfo对象
    QFileInfo fileInfo(filePath);

    int ret = QMessageBox::warning(this, tr("小亦壁纸"),
                                   tr("删除后该图片将不会出现在文件夹中.\n"
                                      "是否确定要删除？"),
                                   QMessageBox::Ok | QMessageBox::Cancel,
                                   QMessageBox::Ok);

    switch (ret) {
    case QMessageBox::Ok:
        // Save was clicked
        // 检查文件是否存在
        if (fileInfo.exists()){
            // 创建QFile对象
            QFile file(filePath);

            // 删除文件
            if (file.remove()){
                QMessageBox::information(this, tr("小亦壁纸"),
                                         tr("删除成功.\n"));
                // 更新收藏页视图
                updateCollection();
                // 还需要更新分页按钮
                changePagingButton(1, mCButtonList, mDataManagers[1]->totalPage());
                break;
            }else{
                // 删除失败
                QMessageBox::information(this, tr("小亦壁纸"),
                                         tr("删除失败.\n"));
                break;
            }
        }else{
            // 文件不存在
            QMessageBox::information(this, tr("小亦壁纸"),
                                     tr("文件不存在.\n"));
            break;
        }
    case QMessageBox::Cancel:
        // Cancel was clicked
        break;
    default:
        // should never be reached
        break;
    }
}


void MainWindow::updateCollection(){

    for(int i = 0 ;i < ui->listWidget_2->count(); ++i)
        //这里是0，不是i，因为每移除一个item都会导致每个item的row发生变化
        delete ui->listWidget_2->takeItem(0);

    ui->listWidget_2->clear();
    qDebug() << ui->listWidget_2->count();
    for(auto& button : mCButtonList)
        delete button;
    mCButtonList.clear();
    delete mDataManagers[1];
    mDataManagers.pop_back();
    // 更新收藏页
    addImageToListWidget(MainMenu::CollectPage, ui->listWidget_2, mCButtonList);

    // 设置样式表
    QFile file(":/qss/clickedButton.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = tr(file.readAll());
    mCButtonList[0]->setStyleSheet(styleSheet);
    file.close();

    mCButtonList[0]->setEnabled(false);
    // 给item绑定真实数据,默认更新第一页的数据
    updateListWidget(MainMenu::CollectPage, 1, ui->listWidget_2, mDataManagers[1]->getImagesOfPage(1));
}

