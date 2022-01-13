#include "nestedwindow.h"
#include <sstream>
#include <QDebug>

NestedWindow::NestedWindow(QObject* parent)
{
  Q_UNUSED(parent)
  pTimer = new QTimer(this);
  QObject::connect(pTimer,&QTimer::timeout,this,&NestedWindow::timerOutCheck);


}
/**
 * @brief NestedWindow::~NestedWindow when the Class release,the nested window  will close.
 */
NestedWindow::~NestedWindow()
{
  if(pTimer){
  delete  pTimer;
    pTimer = nullptr;
    }
  closeNestedWindow();
}
/**
 * @brief NestedWindow::setWindowPos  Use the Windows API to set the window position
 * @param x  the X positon relative to the computer screen
 * @param y  the X positon relative to the computer screen
 * @param width  the nested window width
 * @param height  the nested window height
 */
void NestedWindow::setWindowPos(int x, int y, int width, int height)
{
  if(other_win && qt_win){
//    SetWindowLong(other_win, GWL_STYLE, GetWindowLong(other_win, GWL_STYLE) &  ~(WS_EX_WINDOWEDGE | WS_EX_DLGMODALFRAME));
        SetWindowLong(other_win, GWL_STYLE,GetWindowLong(other_win, GWL_EXSTYLE) | WS_EX_TOPMOST);//设置无边框
        SetWindowPos(other_win,HWND_TOPMOST  ,x,y,width,height,SWP_SHOWWINDOW);
    }else{
    }
}
/**
 * @brief NestedWindow::closeNestedWindow
 */
void NestedWindow::closeNestedWindow(){
  if(other_win){
      SendMessageA(other_win,WM_CLOSE,0,0);
    }
}
/**
 * @brief Accroding to the Class properties to move the window
 */
void NestedWindow::moveOtherWindow()
{
  if(other_win){
      MoveWindow(other_win,m_x,m_y,m_width,m_heigth,true);
    }
}
/**
 * @brief The function is used to periodically detect the existence of other window handles.
 */
void NestedWindow::timerOutCheck()
{
  other_win = FindWindow(m_otherWinClassName.toStdWString().data(),m_otherWinTitleName.toStdWString().data());
  qt_win = FindWindow(L"Qt5QWindowOwnDCIcon", m_qtWindowTitle.toStdWString().data());
  if(other_win && qt_win){
      qDebug()<<"find window";
      pTimer->stop();
      SetWindowLong(other_win, GWL_STYLE,GetWindowLong(other_win, GWL_EXSTYLE) | WS_EX_TOPMOST);
      SetWindowPos(other_win,HWND_TOPMOST  ,m_x,m_y,m_width,m_heigth,SWP_SHOWWINDOW);
    }
}

int NestedWindow::x() const
{
  return m_x;
}

void NestedWindow::setX(int newX)
{
  if (m_x == newX)
    return;
  m_x = newX;
  moveOtherWindow();
  emit xChanged();
}

int NestedWindow::y() const
{
  return m_y;
}

void NestedWindow::setY(int newY)
{
  if (m_y == newY)
    return;
  m_y = newY;
  moveOtherWindow();
  emit yChanged();
}

int NestedWindow::width() const
{
  return m_width;
}

void NestedWindow::setWidth(int newWidth)
{
  if (m_width == newWidth)
    return;
  m_width = newWidth;
  moveOtherWindow();
  emit widthChanged();
}

int NestedWindow::heigth() const
{
  return m_heigth;
}

void NestedWindow::setHeigth(int newHeigth)
{
  if (m_heigth == newHeigth)
    return;
  m_heigth = newHeigth;
  moveOtherWindow();
  emit heigthChanged();
}

const QString &NestedWindow::otherWinClassName() const
{
  return m_otherWinClassName;
}

void NestedWindow::setOtherWinClassName(const QString &newOtherWinClassName)
{
  if (m_otherWinClassName == newOtherWinClassName)
    return;
  m_otherWinClassName = newOtherWinClassName;
  emit otherWinClassNameChanged();
}

const QString &NestedWindow::otherWinTitleName() const
{
  return m_otherWinTitleName;
}

void NestedWindow::setOtherWinTitleName(const QString &newOtherWinTitleName)
{
  if (m_otherWinTitleName == newOtherWinTitleName)
    return;
  m_otherWinTitleName = newOtherWinTitleName;
  emit otherWinTitleNameChanged();
}

const QString &NestedWindow::qtWindowTitle() const
{
  return m_qtWindowTitle;
}

void NestedWindow::setQtWindowTitle(const QString &newQtWindowTitle)
{
  if (m_qtWindowTitle == newQtWindowTitle)
    return;
  m_qtWindowTitle = newQtWindowTitle;
  emit qtWindowTitleChanged();
}

bool NestedWindow::load() const
{
  return m_load;
}

void NestedWindow::setLoad(bool newLoad)
{
  if (m_load == newLoad)
    return;
  m_load = newLoad;
  if(m_load == true){
        pTimer->start(10);
    }else {
      pTimer->stop();
}
  emit loadChanged();
}
