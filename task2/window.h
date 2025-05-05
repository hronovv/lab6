#ifndef WINDOW_H
#define WINDOW_H
#include <bits/stdc++.h>
#include <QApplication>
#include <QFileDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QTextEdit>
#include "QComboBox"
#include "QInputDialog"
#include "QLabel"
#include "QMessageBox"
#include "QString"
#include "struct.h"
constexpr int kSpacing = 20;
constexpr int kMargins = 20;
constexpr int kWindowSize = 1600;
constexpr int kButtonWidth = 400;
constexpr int kButtonHeight = 55;
constexpr double kMaxHeight = 3.0;
constexpr int kMaxAge = 200;
constexpr int kMaxScore = 100;

class Window : public QWidget {
    Q_OBJECT

   public:
    Window();

   private:
    void Wchar_Write_Read();
    void Arr_Write_Read();
    void EnterAndSaveSportsmanData();
    void EnterAndSaveSportsmanData_Binary();
    void EnterAndSaveSentence();
};


#endif	//WINDOW_H
