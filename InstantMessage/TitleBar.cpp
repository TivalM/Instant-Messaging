#include "TitleBar.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QFile>
#include <QMouseEvent>


#define BUTTON_HEIGHT 30        // 按钮高度;
#define BUTTON_WIDTH 30         // 按钮宽度;
#define TITLE_HEIGHT 30         // 标题栏高度;


TitleBar::TitleBar(QWidget *parent,  int windowType) :
	QWidget(parent)
	, windowType(windowType)
	, m_colorR(153)
	, m_colorG(153)
	, m_colorB(153)
	, m_isPressed(false)
	, m_buttonType(MIN_MAX_BUTTON)
	, m_windowBorderWidth(0)
	, m_isTransparent(false)
{
	// 初始化;
	initControl();
	initConnections();
	// 加载本地样式
	loadStyleSheet("BarButton");
}

TitleBar::~TitleBar()
{

}


// 初始化控件;
void TitleBar::initControl()
{
	icon = new QLabel;
	titleContentPtr = new QLabel;
	if (windowType == 0) {
		//登陆与注册界面标题栏
		btMinSimpleBar = new QPushButton;
		btRestoreSimpleBar = new QPushButton;
		btMaxSimpleBar = new QPushButton;
		btCloseSimpleBar = new QPushButton;

		btMinSimpleBar->setProperty("style", "btBar");
		btRestoreSimpleBar->setProperty("style", "btBar");
		btMaxSimpleBar->setProperty("style", "btBar");
		btCloseSimpleBar->setProperty("style", "btBar");

		btMinSimpleBar->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
		btRestoreSimpleBar->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
		btMaxSimpleBar->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
		btCloseSimpleBar->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));

		titleContentPtr->setObjectName("TitleContent");
		btMinSimpleBar->setObjectName("ButtonMin");
		btRestoreSimpleBar->setObjectName("ButtonRestore");
		btMaxSimpleBar->setObjectName("ButtonMax");
		btCloseSimpleBar->setObjectName("ButtonClose");

		btMinSimpleBar->setToolTip(QStringLiteral("最小化"));
		btRestoreSimpleBar->setToolTip(QStringLiteral("还原"));
		btMaxSimpleBar->setToolTip(QStringLiteral("最大化"));
		btCloseSimpleBar->setToolTip(QStringLiteral("关闭"));

		btMinSimpleBar->setFlat(true);
		btRestoreSimpleBar->setFlat(true);
		btMaxSimpleBar->setFlat(true);
		btCloseSimpleBar->setFlat(true);

		QHBoxLayout *mylayout = new QHBoxLayout(this);
		mylayout->addWidget(icon);
		mylayout->addWidget(titleContentPtr);

		mylayout->addWidget(btMinSimpleBar);
		mylayout->addWidget(btRestoreSimpleBar);
		mylayout->addWidget(btMaxSimpleBar);
		mylayout->addWidget(btCloseSimpleBar);

		mylayout->setContentsMargins(5, 0, 0, 0);
		mylayout->setSpacing(0);

		btMinSimpleBar->setIcon(QIcon(":/src/image/min.svg"));
		btMaxSimpleBar->setIcon(QIcon(":/src/image/max.png"));
		btCloseSimpleBar->setIcon(QIcon(":/src/image/close.svg"));
		btRestoreSimpleBar->setIcon(QIcon(":/src/image/restore.png"));

		titleContentPtr->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
		this->setFixedHeight(TITLE_HEIGHT);
		this->setWindowFlags(Qt::FramelessWindowHint);
	} else {
		//主界面标题栏
		barForm = new QWidget;
		functionBarUI.setupUi(barForm);

		QHBoxLayout *mylayout = new QHBoxLayout(this);
		mylayout->addWidget(barForm);

		mylayout->setContentsMargins(0, 0, 0, 0);
		mylayout->setSpacing(0);

		functionBarUI.btRestore->setVisible(false);
		functionBarUI.btMin->setIcon(QIcon(":/src/image/min.svg"));
		functionBarUI.btMax->setIcon(QIcon(":/src/image/max.png"));
		functionBarUI.btClose->setIcon(QIcon(":/src/image/close.svg"));
		functionBarUI.btRestore->setIcon(QIcon(":/src/image/restore.png"));
		functionBarUI.btRing->setIcon(QIcon(":/src/image/ring.png"));
		functionBarUI.btSessions->setIcon(QIcon(":/src/image/chat.svg"));
		functionBarUI.btSessions->setIconSize(QSize(30, 30));
		functionBarUI.btFriends->setIcon(QIcon(":/src/image/friend.png"));
		functionBarUI.btFriends->setIconSize(QSize(30, 30));
		functionBarUI.btTool->setIcon(QIcon(":/src/image/tool.png"));
		functionBarUI.btTool->setIconSize(QSize(30, 30));
		functionBarUI.btAdd->setIcon(QIcon(":/src/image/add.png"));

		this->setFixedHeight(55);
		this->setWindowFlags(Qt::FramelessWindowHint);

		//载入头像
		functionBarUI.headImg->setPixmap(QPixmap(":/src/image/head.png"));
		functionBarUI.headImg->setScaledContents(true);
	}
}

// 信号槽的绑定;
void TitleBar::initConnections()
{
	if (windowType == 0) {
		connect(btMinSimpleBar, SIGNAL(clicked()), this, SLOT(onButtonMinClicked()));
		connect(btRestoreSimpleBar, SIGNAL(clicked()), this, SLOT(onButtonRestoreClicked()));
		connect(btMaxSimpleBar, SIGNAL(clicked()), this, SLOT(onButtonMaxClicked()));
		connect(btCloseSimpleBar, SIGNAL(clicked()), this, SLOT(onButtonCloseClicked()));
	} else {
		connect(functionBarUI.btMin, SIGNAL(clicked()), this, SLOT(onButtonMinClicked()));
		connect(functionBarUI.btRestore, SIGNAL(clicked()), this, SLOT(onButtonRestoreClicked()));
		connect(functionBarUI.btMax, SIGNAL(clicked()), this, SLOT(onButtonMaxClicked()));
		connect(functionBarUI.btClose, SIGNAL(clicked()), this, SLOT(onButtonCloseClicked()));
	}
}

// 设置标题栏背景色,在paintEvent事件中进行绘制标题栏背景色;
// 在构造函数中给了默认值，可以外部设置颜色值改变标题栏背景色;
void TitleBar::setBackgroundColor(int r, int g, int b, bool isTransparent)
{
	m_colorR = r;
	m_colorG = g;
	m_colorB = b;
	m_isTransparent = isTransparent;
	update();
}

// 设置标题栏图标;
void TitleBar::setTitleIcon(QString filePath, QSize IconSize)
{
	QPixmap titleIcon(filePath);
	icon->setPixmap(titleIcon.scaled(IconSize));
}

// 设置标题内容;
void TitleBar::setTitleContent(QString tContent, int titleFontSize)
{
	// 设置标题字体大小;
	QFont font = titleContentPtr->font();
	font.setBold(true);
	font.setPointSize(titleFontSize);
	titleContentPtr->setFont(font);
	// 设置标题内容;
	titleContentPtr->setText(tContent);
}

// 设置标题栏长度;
void TitleBar::setTitleWidth(int width)
{
	this->setFixedWidth(width);
}

// 设置标题栏上按钮类型;
// 由于不同窗口标题栏上的按钮都不一样，所以可以自定义标题栏中的按钮;
// 这里提供了四个按钮，分别为最小化、还原、最大化、关闭按钮，如果需要其他按钮可自行添加设置;
void TitleBar::setButtonType(ButtonType buttonType)
{
	if (windowType == 1)
		return;
	m_buttonType = buttonType;

	switch (buttonType) {
	case MIN_BUTTON: {
		btRestoreSimpleBar->setVisible(false);
		btMaxSimpleBar->setVisible(false);
	}
	break;
	case MIN_MAX_BUTTON: {
		btRestoreSimpleBar->setVisible(false);
	}
	break;
	case ONLY_CLOSE_BUTTON: {
		btMinSimpleBar->setVisible(false);
		btRestoreSimpleBar->setVisible(false);
		btMaxSimpleBar->setVisible(false);
	}
	break;
	default:
		break;
	}
}

// 设置标题栏中的标题是否会自动滚动，跑马灯的效果;
void TitleBar::setTitleRoll()
{
	connect(&m_titleRollTimer, SIGNAL(timeout()), this, SLOT(onRollTitle()));
	m_titleRollTimer.start(200);
}

// 设置窗口边框宽度;
void TitleBar::setWindowBorderWidth(int borderWidth)
{
	m_windowBorderWidth = borderWidth;
}

// 保存窗口最大化前窗口的位置以及大小;
void TitleBar::saveRestoreInfo(const QPoint point, const QSize size)
{
	m_restorePos = point;
	m_restoreSize = size;
}

// 获取窗口最大化前窗口的位置以及大小;
void TitleBar::getRestoreInfo(QPoint &point, QSize &size)
{
	point = m_restorePos;
	size = m_restoreSize;
}

Ui::FunctionTitleBar *TitleBar::getUI()
{
	return &functionBarUI;
}

// 绘制标题栏背景色;
void TitleBar::paintEvent(QPaintEvent *event)
{
	// 是否设置标题透明;
	if (!m_isTransparent) {
		//设置背景色;
		QPainter painter(this);
		QPainterPath pathBack;
		pathBack.setFillRule(Qt::WindingFill);
		pathBack.addRoundedRect(QRect(0, 0, this->width(), this->height()), 3, 3);
		painter.setRenderHint(QPainter::Antialiasing, true);
		painter.fillPath(pathBack, QBrush(QColor(m_colorR, m_colorG, m_colorB)));
	}

	// 当窗口最大化或者还原后，窗口长度变了，标题栏的长度应当一起改变;
	// 这里减去m_windowBorderWidth ，是因为窗口可能设置了不同宽度的边框;
	// 如果窗口有边框则需要设置m_windowBorderWidth的值，否则m_windowBorderWidth默认为0;
	if (this->width() != (this->parentWidget()->width() - m_windowBorderWidth)) {
		this->setFixedWidth(this->parentWidget()->width() - m_windowBorderWidth);
	}
	QWidget::paintEvent(event);
}

// 双击响应事件，实现双击标题栏进行最大化和最小化操作;
void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
	if (windowType == 0) {
		// 只有存在最大化、还原按钮时双击才有效;
		if (m_buttonType == MIN_MAX_BUTTON) {
			// 通过最大化按钮的状态判断当前窗口是处于最大化还是原始大小状态;
			// 或者通过单独设置变量来表示当前窗口状态;
			if (btMaxSimpleBar->isVisible()) {
				onButtonMaxClicked();
			} else {
				onButtonRestoreClicked();
			}
		}
	} else {
		if (functionBarUI.btMax->isVisible()) {
			onButtonMaxClicked();
		} else {
			onButtonRestoreClicked();
		}
	}

	return QWidget::mouseDoubleClickEvent(event);
}

// 以下通过mousePressEvent、mouseMoveEvent、mouseReleaseEvent三个事件实现了鼠标拖动标题栏移动窗口的效果;
void TitleBar::mousePressEvent(QMouseEvent *event)
{
	if (windowType == 0) {
		if (m_buttonType == MIN_MAX_BUTTON) {
			// 在窗口最大化时禁止拖动窗口;
			if (btMaxSimpleBar->isVisible()) {
				m_isPressed = true;
				m_startMovePos = event->globalPos();
			}
		} else {
			m_isPressed = true;
			m_startMovePos = event->globalPos();
		}
	} else {
		m_isPressed = true;
		m_startMovePos = event->globalPos();
	}

	return QWidget::mousePressEvent(event);
}

void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
	if (m_isPressed) {
		QPoint movePoint = event->globalPos() - m_startMovePos;
		QPoint widgetPos = this->parentWidget()->pos();
		m_startMovePos = event->globalPos();
		this->parentWidget()->move(widgetPos.x() + movePoint.x(), widgetPos.y() + movePoint.y());
	}
	return QWidget::mouseMoveEvent(event);
}

void TitleBar::mouseReleaseEvent(QMouseEvent *event)
{
	m_isPressed = false;
	return QWidget::mouseReleaseEvent(event);
}

// 加载本地样式文件;
// 可以将样式直接写在文件中，程序运行时直接加载进来;
void TitleBar::loadStyleSheet(const QString &sheetName)
{
	QFile file("G:\\GitHub\\Instant-Messaging\\InstantMessage\\css\\" + sheetName + ".css");
	file.open(QFile::ReadOnly);
	if (file.isOpen()) {
		QString styleSheet = this->styleSheet();
		styleSheet += QLatin1String(file.readAll());
		this->setStyleSheet(styleSheet);
	} else
		qDebug() << "No such file";
}

// 以下为按钮操作响应的槽;
void TitleBar::onButtonMinClicked()
{
	emit signalButtonMinClicked();
}

void TitleBar::onButtonRestoreClicked()
{
	if (windowType == 0) {
		btRestoreSimpleBar->setVisible(false);
		btMaxSimpleBar->setVisible(true);
	} else {
		functionBarUI.btRestore->setVisible(false);
		functionBarUI.btMax->setVisible(true);
	}
	emit signalButtonRestoreClicked();
}

void TitleBar::onButtonMaxClicked()
{
	if (windowType == 0) {
		btMaxSimpleBar->setVisible(false);
		btRestoreSimpleBar->setVisible(true);
		emit signalButtonMaxClicked();
	} else {
		functionBarUI.btMax->setVisible(false);
		functionBarUI.btRestore->setVisible(true);
		emit signalButtonMaxClicked();
	}
}

void TitleBar::onButtonCloseClicked()
{
	emit signalButtonCloseClicked();
}

// 该方法主要是让标题栏中的标题显示为滚动的效果;
void TitleBar::onRollTitle()
{
//	static int nPos = 0;
//	QString titleContent = m_titleContent;
//	// 当截取的位置比字符串长时，从头开始;
//	if (nPos > titleContent.length())
//		nPos = 0;

//	titleContent->setText(titleContent.mid(nPos));
//	nPos++;
}
