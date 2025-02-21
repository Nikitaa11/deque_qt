#pragma once

#include <QMainWindow>
#include <QStringListModel>
#include <QListWidgetItem>
#include <random>

#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void SetRandomGen(const std::mt19937 &random_gen);

private slots:

    void on_pop_back_clicked();

    void on_push_back_clicked();

    void on_clear_clicked();

    void on_btn_tea_clicked();

    void on_btn_cakes_clicked();

    void on_erase_clicked();

    void on_insert_clicked();

    void on_edit_clicked();

    void on_btn_minus_clicked();

    void on_btn_plus_clicked();

    void on_begin_clicked();

    void on_end_clicked();

    void on_list_widget_currentRowChanged(int currentRow);

    void on_resize_clicked();

    void on_count_clicked();

    void on_min_element_clicked();

    void on_max_element_clicked();

    void on_find_clicked();

    void on_sort_clicked();

    void on_sOrT_clicked();

    void on_unique_clicked();

    void on_reverse_clicked();

    void on_shuffle_clicked();

    void on_pop_front_clicked();

    void on_push_front_clicked();

    void on_lower_bound_clicked();

    void on_upper_bound_clicked();

private:
    void ApplyModel();
    void ApplyIterator();

private:
    Model deque_model_;
    Ui::MainWindow *ui;
    std::mt19937 random_gen_;
};
