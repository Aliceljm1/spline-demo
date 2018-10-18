#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    palette = new Palette(this);

    setWindowTitle("B样条曲线模拟程序: B-spline Curve - By RyuZhihao123");
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    ui->groupBox->setGeometry(width()-230,10,211,height()-50);

    palette->setGeometry(0,0,width()-230,height());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lblLink_linkActivated(const QString &link)
{
    QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_check_isShowCtrlPoint_clicked()
{
    palette->showCtrlNode = ui->check_isShowCtrlPoint->isChecked();
    palette->update();
}

void MainWindow::on_check_isShowUpoint_clicked()
{
    palette->showCurveNode = ui->check_isShowUpoint->isChecked();
    palette->update();
}

void MainWindow::on_com_degree_currentIndexChanged(int index)
{
    ui->lblInfo->setText(QString("Leval%1").arg(index+2));
    palette->currentK = index+1;

    palette->generateCurve();
    palette->update();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Backspace:
        palette->ctrlPoints.pop_back();
        break;
    case Qt::Key_C:
        palette->ctrlPoints.clear();
    default:
        break;
    }

    palette->generateCurve();
    palette->update();
}

void MainWindow::on_btnClear_clicked()
{
    palette->ctrlPoints.clear();
    palette->generateCurve();
    palette->update();
}
