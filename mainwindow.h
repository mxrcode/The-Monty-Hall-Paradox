#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

#include <random>
#include <ctime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void generate_door_state(QString selected_door);
    QString open_next_door(QString win_door, QString selected_door);

    void form_state_selected();
    void form_state_after();

    void on_door1_clicked();
    void on_door2_clicked();
    void on_door3_clicked();

    void on_change_mind_no_clicked();
    void on_change_mind_yes_clicked();

private:
    Ui::MainWindow *ui;
    QString m_win_door;
    QString m_selected_door = "0";
    QString m_next_door = "0";

    double game_counter_changed = 0;
    double game_counter_not_changed = 0;

    double won_changed = 0;
    double won_not_changed = 0;
};
#endif // MAINWINDOW_H
