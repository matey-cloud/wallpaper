
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mDataManager(new DataManager)
    , mLayout(nullptr)
{
    ui->setupUi(this);
    //去掉软件标题栏，自己来实现  Qt::FramelessWindowHint
    //设置窗体透明，但里面的控件不透明,这个可以用来做不规则的窗体效果
    //如果是规则的矩形窗体这个可以不用
    //    setAttribute(Qt::WA_TranslucentBackground,true);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    setWindowIcon(QIcon(":/images/title.png"));//可执行程序图标
\
    mLayout = new QHBoxLayout(ui->tool);
    ui->tool->setLayout(mLayout);
    mLayout->setAlignment(Qt::AlignLeft); // 分页按钮向左对齐


    initListWigdet();//初始化QlistWidget
    addImageToListWidget();// 添加壁纸到QListWidget中，需要用到DataManager::mTotalPage

}

MainWindow::~MainWindow()
{
    delete mDataManager;
    delete ui;
}

//重写鼠标按下事件
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    m_moveing = true;
    //记录下鼠标相对于窗口的位置
    //event->globalPos()鼠标按下时，鼠标相对于整个屏幕位置
    //pos() this->pos()鼠标按下时，窗口相对于整个屏幕位置
    m_movePosition = event->globalPos() - pos();
    QWidget::mousePressEvent(event);
}

//重写鼠标移动事件
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    //(event->buttons() & Qt::LeftButton)按下是左键
    //鼠标移动事件需要移动窗口，窗口移动到哪里呢？就是要获取鼠标移动中，窗口在整个屏幕的坐标，然后move到这个坐标，怎么获取坐标？
    //通过事件event->globalPos()知道鼠标坐标，鼠标坐标减去鼠标相对于窗口位置，就是窗口在整个屏幕的坐标
    if (m_moveing && (event->buttons() & Qt::LeftButton)
        && (event->globalPos()-m_movePosition).manhattanLength() > QApplication::startDragDistance())
    {
        move(event->globalPos()-m_movePosition);
        m_movePosition = event->globalPos() - pos();
    }
    QWidget::mouseMoveEvent(event);
}

//鼠标释放
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    m_moveing = false;
    QWidget::mouseReleaseEvent(event);
}


void MainWindow::initListWigdet(){
    //    QFile file2(":/qss/scrollbar.qss");
    //    file2.open(QFile::ReadOnly);
    //    ui->listWidget->verticalScrollBar()->setStyleSheet(file2.readAll());
    //    file2.close();
    // 获取容器QlistWidget的长度和宽度
    int itemWidth = (ui->listWidget->width()-20) / 3;
    int itemHeight = (ui->listWidget->height()) / 2;

    //初始化QListWidget
    ui->listWidget->setIconSize(QSize(itemWidth,itemHeight)); // 每个Item的大小
    ui->listWidget->setResizeMode(QListView::Adjust);
    ui->listWidget->setViewMode(QListView::IconMode);
    //设置不能移动
    ui->listWidget->setMovement(QListView::Static);
    ui->listWidget->setSpacing(0);
    ui->listWidget->horizontalScrollBar()->setDisabled(true);
    ui->listWidget->verticalScrollBar()->setDisabled(true);
    ui->listWidget->setStyleSheet("QListWidget::Item:hover{background-color:rgba(47,46,46,0);border-radius:5px; }"
                                  "QListWidget::item:selected{background-color:rgba(47,46,46,0);color:rgb(61,61,61);border:2px solid #FFC53D;border-radius:5px; }"
                                  "QScrollBar:vertical{width:0px}");
    ui->listWidget->setFocusPolicy(Qt::NoFocus);//文字没虚线
    ui->listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    connect(ui->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(listWidgetClicked(QListWidgetItem*)));
}

void MainWindow::addImageToListWidget()
{
    // 获取容器QlistWidget的长度和宽度
    int itemWidth = (ui->listWidget->width()-20) / 3;
    int itemHeight = (ui->listWidget->height()) / 2;

    // 获取有多少页
    int pages = mDataManager->totalPage();
    for(int n = 1; n <= pages; ++n){
        // 每页创建一个按钮
        QPushButton* button = new QPushButton(QString::number(n));// 按钮以页数命名
        button->setFixedSize(40, 40); // 设置按钮大小

        //绑定分页按钮点击事件
        QObject::connect(button, &QPushButton::clicked, this, &MainWindow::clickPagingButton);
        mButtonList.append(button); // buttonList.push_back(button)，将按钮添加到按钮列表末尾

        // 创建单元项
        // 这里创建的Item使用的背景图是样式表中的默认背景图
        for (int i = 0; i < 6; ++i)
        {
            QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
            ImageInfoItem *widget = new ImageInfoItem;
            item->setSizeHint(QSize(itemWidth, itemHeight));

            ui->listWidget->addItem(item);
            //将宽度增量设置为150，高度增量设置为190，表示每次调整部件大小时，
            //宽度会增加或减少150个单位，高度会增加或减少190个单位。这样可以根据需要调整部件的大小。
            ui->listWidget->setSizeIncrement(150, 190);
            //最重要的是这句将Item设置为一个Widget，而这个Widget就是自定义的ui
            //将ImageInfoItem部件与相应的QListWidgetItem关联起来
            ui->listWidget->setItemWidget(item, widget);
        }

    }

    // 设置按钮在分页中默认的显示规则
    initPagingButton();
    ui->tool->setLayout(mLayout);
    // 给item绑定真实数据,默认更新第一页的数据
    updateListWidget(1);
}

//将图片列表更新为第page页的图片数据，如果最后一页不足6个，需要把上一页的数据清空，再填入最后一页的壁纸
void MainWindow::updateListWidget(int page){
    //获取第page页面的数据当在imageInfoList中
    QList<ImageDataInfo> imageInfoList = mDataManager->getImagesOfPage(page);
    //先初始化listWidget列表的每一项为空数据
    for (int i = 0; i < 6; ++i)
    {
        QListWidgetItem *item = ui->listWidget->item(i);
        QWidget *widget = ui->listWidget->itemWidget(item);
        ImageInfoItem* imageInfoItem = dynamic_cast<ImageInfoItem*>(widget);
        if(imageInfoItem != nullptr){
            ImageDataInfo info;//空数据
            imageInfoItem->addImage(info);
            ui->listWidget->setItemWidget(item, imageInfoItem);
        }
    }
    //根据实际上得到的imageInfoList初始化listWidget
    for (int i = 0; i < imageInfoList.size(); ++i)
    {
        QListWidgetItem *item = ui->listWidget->item(i);
        QWidget * widget =  ui->listWidget->itemWidget(item);
        ImageInfoItem* imageInfoItem = dynamic_cast<ImageInfoItem*>(widget);
        if (imageInfoItem != nullptr) {
            imageInfoItem->addImage(imageInfoList[i]);
            // 设置 ImageInfoItem 作为 QListWidgetItem 的自定义小部件
            ui->listWidget->setItemWidget(item, imageInfoItem);
        }
    }
}

void MainWindow::initPagingButton()
{
    // 创建省略号按钮
    QPushButton *ellipsisButtonLeft = new QPushButton("...");
    QPushButton *ellipsisButtonRight = new QPushButton("...");
    // 不可点击
    ellipsisButtonLeft->setEnabled(false);
    ellipsisButtonRight->setEnabled(false);

    // 按钮列表中设置显示7个
    int visibleButtonCount = 7;
    // 一共多少个按钮，就有多少页壁纸
    int buttonCount = mButtonList.count();
    // 一共只有小于等于7页壁纸
    if(buttonCount <= visibleButtonCount){
        for(int i = 0; i < buttonCount; ++i){
            mLayout->addWidget(mButtonList[i]);
        }
    } else{

        // 默认第一页的样式，显示1-6和最后一个按钮
        for(int i = 0; i < visibleButtonCount - 1; ++i){
            mLayout->addWidget(mButtonList[i]);// 添加按钮到布局
        }
        mLayout->addWidget(ellipsisButtonLeft); // 6之后添加省略按钮
        mLayout->addWidget(mButtonList[buttonCount - 1]);// 添加最后一个按钮
    }

    //    // 点击第几页的按钮，就将该页的值传入槽函数中，该页的值就是按钮的名字
    //    // 连接点击信号槽函数，点击第几页的按钮，就显示第几页的壁纸
    //    QObject::connect(button, &QPushButton::clicked, this, [&]() {
    //        // 保存点击按钮的索引
    //        int clickedIndex = n + 1;

    //        // 更新对应页数的壁纸
    //        mDataManager->setCurPage(clickedIndex);
    //        updateListWidget(mDataManager->curPage());

    //        // 显示相邻的按钮
    //        int startIndex = qMax(0, clickedIndex - 1);
    //        int endIndex = qMin(pages - 1, clickedIndex + 1);

    //        for (int j = startIndex; j <= endIndex; j++) {
    //            if(j > 0 && j < pages){
    //                buttonList.at(j)->show();
    //            }
    //        }

    //        // 隐藏其他按钮，除了1和末尾和 【startInedx，endIndex】区间的按钮
    //        for (int j = 1; j < pages - 1; j++) {
    //            if (j < startIndex || j > endIndex) {
    //                buttonList.at(j)->hide();
    //            }
    //        }
    //        // 显示省略号按钮
    //        if (startIndex > 1) {
    //            ellipsisButton->show();
    //        } else {
    //            ellipsisButton->hide();
    //        }
    //        if (endIndex < pages - 2) {
    //            buttonList.at(pages - 2)->show();
    //        } else {
    //            buttonList.at(pages - 2)->hide();
    //        }
    //    });
}

void MainWindow::changePagingButton()
{

}

void MainWindow::clickPagingButton()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender()); // 获取发出信号的按钮
    if(button){
        // 更新对应页数的壁纸
        QString buttonText = button->text();
        int clickedIndex = buttonText.toInt(); // 获取点击的第几页
        mDataManager->setCurPage(clickedIndex);
        updateListWidget(mDataManager->curPage());

        // 更改分页工具栏的样式
        changePagingButton();
    }
}


