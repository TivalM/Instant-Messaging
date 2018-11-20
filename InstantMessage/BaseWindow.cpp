#include "BaseWindow.h"


BaseWindow::BaseWindow(QWidget *parent, int windowType) :
	QDialog(parent)
{
	// FramelessWindowHint属性设置窗口去除边框;
	// WindowMinimizeButtonHint 属性设置在窗口最小化时，点击任务栏窗口可以显示出原窗口;
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
	sizePolicy();
	// 设置窗口背景透明;
	//  setAttribute(Qt::WA_TranslucentBackground);

	// 注意！！！如果是主窗口不要设置WA_DeleteOnClose属性;
	// 关闭窗口时释放资源;
	//  setAttribute(Qt::WA_DeleteOnClose);
	// 初始化标题栏;
	initTitleBar(windowType);
}


BaseWindow::~BaseWindow()
{

}

void BaseWindow::initTitleBar(int type)
{
	titleBarPtr = new TitleBar(this, type);
	titleBarPtr->move(0, 0);

	connect(titleBarPtr, SIGNAL(signalButtonMinClicked()), this, SLOT(onButtonMinClicked()));
	connect(titleBarPtr, SIGNAL(signalButtonRestoreClicked()), this, SLOT(onButtonRestoreClicked()));
	connect(titleBarPtr, SIGNAL(signalButtonMaxClicked()), this, SLOT(onButtonMaxClicked()));
	connect(titleBarPtr, SIGNAL(signalButtonCloseClicked()), this, SLOT(onButtonCloseClicked()));
}

void BaseWindow::paintEvent(QPaintEvent *event)
{
//	//设置背景色;
//	QPainter painter(this);
//	QPainterPath pathBack;
//	pathBack.setFillRule(Qt::WindingFill);
//	pathBack.addRoundedRect(QRect(0, 0, this->width(), this->height()), 3, 3);
//	painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
//	painter.fillPath(pathBack, QBrush(QColor(238, 223, 204)));

//	return QWidget::paintEvent(event);
}

void BaseWindow::loadStyleSheet(const QString &sheetName)
{
	QFile file(":/Resources/" + sheetName + ".css");
	file.open(QFile::ReadOnly);
	if (file.isOpen()) {
		QString styleSheet = this->styleSheet();
		styleSheet += QLatin1String(file.readAll());
		this->setStyleSheet(styleSheet);
	}
}

void BaseWindow::onButtonMinClicked()
{
	showMinimized();
}

void BaseWindow::onButtonRestoreClicked()
{
	QPoint windowPos;
	QSize windowSize;
	titleBarPtr->getRestoreInfo(windowPos, windowSize);
	this->setGeometry(QRect(windowPos, windowSize));
}

void BaseWindow::onButtonMaxClicked()
{
	titleBarPtr->saveRestoreInfo(this->pos(), QSize(this->width(), this->height()));
	QRect desktopRect = QApplication::desktop()->availableGeometry();
	QRect FactRect = QRect(desktopRect.x() - 3, desktopRect.y() - 3, desktopRect.width() + 6, desktopRect.height() + 6);
	setGeometry(FactRect);
}

void BaseWindow::onButtonCloseClicked()
{
	close();
}

void BaseWindow::resizeEvent(QResizeEvent *event)
{
	Q_UNUSED(event);
	titleBarPtr->resize(this->width(), 30);
}

//void BaseWindow::closeWindow()
//{
//	QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
//	animation->setDuration(1);
//	animation->setStartValue(100);
//	animation->setEndValue(0);
//	animation->start();
//	connect(animation, SIGNAL(QPropertyAnimation::finished()), this, SLOT(this.close()));
//}
