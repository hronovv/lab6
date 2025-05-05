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
typedef long long ll;
typedef unsigned int uint;
constexpr int kWindowSize = 1600;
constexpr int kButtonWidth = 420;
constexpr int kButtonHeight = 60;
constexpr int kMargins = 25;
constexpr int kSmToMCoefficient = 100;
constexpr uint kAge1 = 25;
constexpr int kMaxScore = 100;
constexpr double kHeight1 = 1.80;
constexpr int kScore11 = 90;
constexpr int kScore12 = 85;
constexpr int kScore13 = 88;
constexpr int kScore14 = 92;
constexpr int kScore15 = 87;

constexpr uint kAge2 = 30;
constexpr double kHeight2 = 1.85;
constexpr int kScore21 = 78;
constexpr int kScore22 = 82;
constexpr int kScore23 = 80;
constexpr int kScore24 = 75;
constexpr int kScore25 = 85;

constexpr uint kAge3 = 27;
constexpr double kHeight3 = 1.90;
constexpr int kScore31 = 88;
constexpr int kScore32 = 90;
constexpr int kScore33 = 85;
constexpr int kScore34 = 87;
constexpr int kScore35 = 86;

constexpr uint kAge4 = 23;
constexpr double kHeight4 = 2.06;
constexpr int kScore41 = 99;
constexpr int kScore42 = 100;
constexpr int kScore43 = 97;
constexpr int kScore44 = 96;
constexpr int kScore45 = 98;

constexpr uint kAge5 = 32;
constexpr double kHeight5 = 1.82;
constexpr int kScore51 = 92;
constexpr int kScore52 = 89;
constexpr int kScore53 = 85;
constexpr int kScore54 = 91;
constexpr int kScore55 = 90;

class Window : public QWidget {
    Q_OBJECT

   public:
    Window();

   private:
    QLabel* struct1_label_;
    QLabel* struct2_label_;
    QLabel* struct3_label_;
    QLabel* struct4_label_;
    QLabel* struct5_label_;
    void PrintStruct1();
    void PrintStruct2();
    void PrintStruct3();
    void PrintStruct4();
    void PrintStruct5();
};


#endif	//WINDOW_H
