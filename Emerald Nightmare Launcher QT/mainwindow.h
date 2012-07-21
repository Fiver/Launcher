#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_webView_urlChanged(const QUrl &arg1);

    void on_PlayButton_clicked();

    void on_IRCModeCheckBox_clicked();

    void on_DeleteCacheCheckBox_clicked();

    void on_webView_loadFinished(bool arg1);

    void on_actionDelete_Non_Essential_Files_triggered();

    void on_actionDownload_GM_Addon_triggered();

    void on_actionDelete_Settings_triggered();

    void on_actionDelete_Cache_triggered();

    void on_actionSig_MD5_Check_Archives_triggered();

    void on_actionToggle_Debug_triggered();

    void on_actionDownload_Reccomended_Addons_triggered();

    void on_actionDownload_Client_triggered();

    void on_actionDelete_Archive_Interface_Files_triggered();

    void on_actionForce_Update_triggered();

    void on_actionCredits_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
