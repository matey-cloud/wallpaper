
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //去掉软件标题栏，自己来实现  Qt::FramelessWindowHint
    //设置窗体透明，但里面的控件不透明,这个可以用来做不规则的窗体效果
    //如果是规则的矩形窗体这个可以不用
//    setAttribute(Qt::WA_TranslucentBackground,true);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    setWindowIcon(QIcon(":/images/title.png"));//可执行程序图标

    initListWigdet();

}

MainWindow::~MainWindow()
{
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
    ui->listWidget->setIconSize(QSize(itemWidth,itemHeight));
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
    //给item绑定真实数据
    updateListWidget(1); // page 从1开始
}

//将图片列表更新为第page页的图片数据
void MainWindow::updateListWidget(int page){
    //获取第page页面的数据当在imageInfoList中
     QList<ImageDataInfo> imageInfoList = DataManager::GetImageInfoList(page);
    //先初始化listWidget列表的每一项为空数据
    for (int i = 0; i < ui->listWidget->count(); ++i)
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
