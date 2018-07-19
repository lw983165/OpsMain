#include <QMainWindow>
#include <memory>
#include <QTcpServer>
#include <QTcpSocket>
#include <QSettings>
#include <QDebug>
#include <QTimer>
#include <QDateTime>
class Canvas;
class Tool;
class SelectionTool;
class DrawCircleTool;
class DrawRectangleTool;
class DrawLineTool;
class ValueChangeTool;
class GlobalDrawProperties;
class MainCommandStack;
class QJsonObject;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    Canvas* getCanvas();
    //void setActiveTool(Tool *tool);
   // bool isDirty() const;
    //bool promptUnsavedWork();
    //void saveFile();
    //void setCommandStackIdx(int val);
   // void mainCommandStackHasChanged();
    QString getTitle() const;
    ~MainWindow();

    QString getCanvasFile() const;
    void setCanvasFile(const QString &value);



public slots:
    void timerUpdate(void);
private slots:
    void on_toolButton_20_triggered();

private:
    void uncheckAllToolbar();
    void resetCommandStack();
    QEvent* newValueChangeEvent(const QJsonObject* json);

    MainCommandStack *m_mcs;

    Ui::MainWindow *ui;
    Canvas *m_canvas;
    Tool *m_activeTool;
    GlobalDrawProperties *m_gp;
    QString m_appName;
    QString m_canvasFile;
    int m_appStackIdx;
    bool m_isFileSet;

    std::unique_ptr<SelectionTool> m_selectionTool;
    std::unique_ptr<ValueChangeTool> m_valueChangeTool;
};

