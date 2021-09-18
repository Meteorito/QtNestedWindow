#ifndef NESTEDWINDOW_H
#define NESTEDWINDOW_H
#include <windows.h>
#include <winuser.h>
#include <QObject>
#include <QTimer>
/**
 * @brief The NestedWindow class
 */
class NestedWindow:public QObject
{
    Q_OBJECT
public:
  NestedWindow(QObject* parent = nullptr);
  ~NestedWindow();

  Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
  Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)
  Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
  Q_PROPERTY(int heigth READ heigth WRITE setHeigth NOTIFY heigthChanged)

  //Regist the window params of other program windows ,including window Class Name
  //and window Title Name.We can use these in qml program.
  Q_PROPERTY(QString otherWinClassName READ otherWinClassName WRITE setOtherWinClassName NOTIFY otherWinClassNameChanged)
  Q_PROPERTY(QString otherWinTitleName READ otherWinTitleName WRITE setOtherWinTitleName NOTIFY otherWinTitleNameChanged)

  //Regist the Qt window Title.
  Q_PROPERTY(QString qtWindowTitle READ qtWindowTitle WRITE setQtWindowTitle NOTIFY qtWindowTitleChanged)

  //set the nested window position
 Q_INVOKABLE  void setWindowPos(int x,int y,int width,int height);
  //close the nested window
Q_INVOKABLE   void closeNestedWindow();

  int x() const;
  void setX(int newX);

  int y() const;
  void setY(int newY);

  int width() const;
  void setWidth(int newWidth);

  int heigth() const;
  void setHeigth(int newHeigth);

  const QString &otherWinClassName() const;
  void setOtherWinClassName(const QString &newOtherWinClassName);

  const QString &otherWinTitleName() const;
  void setOtherWinTitleName(const QString &newOtherWinTitleName);

  const QString &qtWindowTitle() const;
  void setQtWindowTitle(const QString &newQtWindowTitle);

signals:
  void xChanged();

  void yChanged();

  void widthChanged();

  void heigthChanged();

  void otherWinClassNameChanged();

  void otherWinTitleNameChanged();

  void qtWindowTitleChanged();

private slots:
  void timerOutCheck();

  void moveOtherWindow();

private:
  HWND qt_win;
  HWND other_win;
  //Use a timer to detect the existence of a window
  QTimer* pTimer;
  int m_x;
  int m_y;
  int m_width;
  int m_heigth;
  QString m_otherWinClassName;
  QString m_otherWinTitleName;
  QString m_qtWindowTitle;
};

#endif // NESTEDWINDOW_H
