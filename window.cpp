#include "window.h"

Window::Window() {
    QString button_style = R"(
        QPushButton {
            background-color: #ffffff;
            border: 2px solid #000000;
            color: #000000;
            padding: 10px 20px;
            font-size: 14px;
            margin: 5px;
            border-radius: 5px;
        }
        QPushButton:hover {
            background-color: #f0f0f0;
        }
        QPushButton:pressed {
            background-color: #d0d0d0;
            color: #333333;
        }
    )";

    QString text_style = R"(
        font-size: 15px;
        color: #FFFFFF;
    )";

    struct1_label_ = new QLabel(this);
    struct1_label_->setText("Структура 1:");
    struct1_label_->setStyleSheet(text_style);

    struct2_label_ = new QLabel(this);
    struct2_label_->setText("Структура 2:");
    struct2_label_->setStyleSheet(text_style);

    struct3_label_ = new QLabel(this);
    struct3_label_->setText("Структура 3:");
    struct3_label_->setStyleSheet(text_style);

    struct4_label_ = new QLabel(this);
    struct4_label_->setText("Структура 4:");
    struct4_label_->setStyleSheet(text_style);

    struct5_label_ = new QLabel(this);
    struct5_label_->setText("Структура 5:");
    struct5_label_->setStyleSheet(text_style);

    auto* struct1_button =
        new QPushButton("Вывести структуру, созданную через { }: ", this);
    struct1_button->setFixedSize(kButtonWidth, kButtonHeight);
    struct1_button->setStyleSheet(button_style);
    connect(struct1_button, &QPushButton::clicked, this, &Window::PrintStruct1);

    auto* struct2_button =
        new QPushButton("Вывести структуру(отдельно созданные поля): ", this);
    struct2_button->setFixedSize(kButtonWidth, kButtonHeight);
    struct2_button->setStyleSheet(button_style);
    connect(struct2_button, &QPushButton::clicked, this, &Window::PrintStruct2);

    auto* struct3_button =
        new QPushButton("Создать и вывести структуру: ", this);
    struct3_button->setFixedSize(kButtonWidth, kButtonHeight);
    struct3_button->setStyleSheet(button_style);
    connect(struct3_button, &QPushButton::clicked, this, &Window::PrintStruct3);

    auto* struct4_button =
        new QPushButton("Вывести структуру(через указатель): ", this);
    struct4_button->setFixedSize(kButtonWidth, kButtonHeight);
    struct4_button->setStyleSheet(button_style);
    connect(struct4_button, &QPushButton::clicked, this, &Window::PrintStruct4);

    auto* struct5_button =
        new QPushButton("Вывести структуру(через ссылку): ", this);
    struct5_button->setFixedSize(kButtonWidth, kButtonHeight);
    struct5_button->setStyleSheet(button_style);
    connect(struct5_button, &QPushButton::clicked, this, &Window::PrintStruct5);

    auto* layout1 = new QGridLayout(this);
    layout1->addWidget(struct1_button, 0, 0);
    layout1->addWidget(struct1_label_, 0, 1);
    layout1->addWidget(struct2_button, 1, 0);
    layout1->addWidget(struct2_label_, 1, 1);
    layout1->addWidget(struct3_button, 2, 0);
    layout1->addWidget(struct3_label_, 2, 1);
    layout1->addWidget(struct4_button, 3, 0);
    layout1->addWidget(struct4_label_, 3, 1);
    layout1->addWidget(struct5_button, 4, 0);
    layout1->addWidget(struct5_label_, 4, 1);
    layout1->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    layout1->setContentsMargins(kMargins, kMargins, kMargins, kMargins);
    setLayout(layout1);
}

void Window::PrintStruct1() {
    Sportsman athlete1 = {
        kAge1, kHeight1,   'M',
        true,  "John Doe", {kScore11, kScore12, kScore13, kScore14, kScore15}};

    QString result =
        QString(
            "Возраст: %1 | Рост: %2м | Пол: %3 | Профессионал?: %4 | Имя: %5 | "
            "Результаты за 5 матчей: %6, %7, %8, %9, %10")
            .arg(athlete1.age)
            .arg(athlete1.height)
            .arg(athlete1.gender)
            .arg(athlete1.isProfessional ? "Да" : "Нет")
            .arg(QString::fromStdString(athlete1.name))
            .arg(athlete1.scores[0])
            .arg(athlete1.scores[1])
            .arg(athlete1.scores[2])
            .arg(athlete1.scores[3])
            .arg(athlete1.scores[4]);

    struct1_label_->setText(result);
}

void Window::PrintStruct2() {
    Sportsman athlete2;
    athlete2.age = kAge2;
    athlete2.height = kHeight2;
    athlete2.gender = 'F';
    athlete2.isProfessional = false;
    strcpy(athlete2.name, "Jay Savoir");
    int sample_scores[kScoresSize] = {kScore21, kScore22, kScore23, kScore24,
                                      kScore25};
    memcpy(athlete2.scores, sample_scores, sizeof(sample_scores));

    QString result =
        QString(
            "Возраст: %1 | Рост: %2м | Пол: %3 | Профессионал?: %4 | Имя: %5 | "
            "Результаты за 5 матчей: %6, %7, %8, %9, %10")
            .arg(athlete2.age)
            .arg(athlete2.height)
            .arg(athlete2.gender)
            .arg(athlete2.isProfessional ? "Да" : "Нет")
            .arg(QString::fromStdString(athlete2.name))
            .arg(athlete2.scores[0])
            .arg(athlete2.scores[1])
            .arg(athlete2.scores[2])
            .arg(athlete2.scores[3])
            .arg(athlete2.scores[4]);

    struct2_label_->setText(result);
}

void Window::PrintStruct3() {
    Sportsman athlete3;


    while (true) {
        bool ok = false;
        QString number = QInputDialog::getText(
            nullptr, "Возраст", "Введите возраст:", QLineEdit::Normal, "", &ok);
        if (ok && !number.isEmpty()) {
            bool n_ok;
            uint age = number.toUInt(&n_ok);
            if (n_ok) {
                athlete3.age = age;
                QMessageBox::information(this, "Результат",
                                         "Возраст успешно введен");
                break;
            } else {
                QMessageBox::warning(nullptr, "Ошибка",
                                     "Введите целое число с учетом диапазона");
            }
        } else {
            QMessageBox::warning(nullptr, "Ошибка", "Введите целое число");
        }
    }


    while (true) {
        bool ok = false;
        QString number = QInputDialog::getText(
            nullptr, "Возраст", "Введите рост(в см):", QLineEdit::Normal, "",
            &ok);
        if (ok && !number.isEmpty()) {
            bool n_ok;
            uint height = number.toUInt(&n_ok);
            if (n_ok) {
                athlete3.height = double(height) / kSmToMCoefficient;
                QMessageBox::information(this, "Результат",
                                         "Рост успешно введен");
                break;
            } else {
                QMessageBox::warning(nullptr, "Ошибка",
                                     "Введите целое число с учетом диапазона");
            }
        } else {
            QMessageBox::warning(nullptr, "Ошибка", "Введите целое число");
        }
    }


    while (true) {
        bool ok = false;
        QString input = QInputDialog::getText(
            nullptr, "Пол", "Введите пол (M/F):", QLineEdit::Normal, "", &ok);
        if (ok && !input.isEmpty()) {
            if (input.length() == 1) {
                QChar symbol = input[0].toUpper();
                if (symbol == 'M' || symbol == 'F') {
                    athlete3.gender = symbol.toLatin1();
                    QMessageBox::information(nullptr, "Результат",
                                             "Пол успешно введен");
                    break;
                } else {
                    QMessageBox::warning(
                        nullptr, "Ошибка",
                        "Введите 'M' (мужской) или 'F' (женский).");
                }
            } else {
                QMessageBox::warning(nullptr, "Ошибка",
                                     "Введите ОДИН символ ('M' или 'F').");
            }
        } else {
            QMessageBox::warning(nullptr, "Ошибка",
                                 "Пол не введён. Попробуйте снова.");
        }
    }


    while (true) {
        bool ok = false;
        QString name = QInputDialog::getText(
            nullptr, "Имя", "Введите имя (до 200 символов):", QLineEdit::Normal,
            "", &ok);
        if (ok && !name.isEmpty() && name.length() < kNameSize) {
            strncpy(athlete3.name, name.toUtf8().constData(), kNameSize - 1);
            athlete3.name[kNameSize - 1] = '\0';
            QMessageBox::information(nullptr, "Результат",
                                     "Имя успешно введено");
            break;
        } else {
            QMessageBox::warning(
                nullptr, "Ошибка",
                "Введите корректное имя (не более 200 символов).");
        }
    }


    for (int i = 0; i < kScoresSize; ++i) {
        while (true) {
            bool ok = false;
            QString number = QInputDialog::getText(
                nullptr, "Оценка",
                QString("Введите результат за матч  №%1:").arg(i + 1),
                QLineEdit::Normal, "", &ok);
            if (ok && !number.isEmpty()) {
                bool n_ok;
                int score = number.toInt(&n_ok);
                if (n_ok && score >= 0 && score <= kMaxScore) {
                    athlete3.scores[i] = score;
                    break;
                }
            }
            QMessageBox::warning(nullptr, "Ошибка",
                                 "Введите число от 0 до 100.");
        }
    }


    while (true) {
        bool ok = false;
        QString input = QInputDialog::getText(
            nullptr, "Профессиональный статус",
            "Является ли спортсмен профессионалом? (Y/N):", QLineEdit::Normal,
            "", &ok);
        if (ok && !input.isEmpty() && input.length() == 1) {
            QChar symbol = input[0].toUpper();
            if (symbol == 'Y' || symbol == 'N') {
                athlete3.isProfessional = (symbol == 'Y');
                QMessageBox::information(nullptr, "Результат",
                                         "Статус успешно введен");
                break;
            }
        }
        QMessageBox::warning(nullptr, "Ошибка",
                             "Введите 'Y' (да) или 'N' (нет).");
    }
    QString result =
        QString(
            "Возраст: %1 | Рост: %2м | Пол: %3 | Профессионал?: %4 | Имя: %5 | "
            "Результаты за 5 матчей: %6, %7, %8, %9, %10")
            .arg(athlete3.age)
            .arg(athlete3.height)
            .arg(athlete3.gender)
            .arg(athlete3.isProfessional ? "Да" : "Нет")
            .arg(QString::fromStdString(athlete3.name))
            .arg(athlete3.scores[0])
            .arg(athlete3.scores[1])
            .arg(athlete3.scores[2])
            .arg(athlete3.scores[3])
            .arg(athlete3.scores[4]);

    struct3_label_->setText(result);
}

void Window::PrintStruct4() {
    auto* athlete4 = new Sportsman;
    athlete4->age = kAge3;
    athlete4->height = kHeight3;
    athlete4->gender = 'M';
    athlete4->isProfessional = true;
    strcpy(athlete4->name, "Nick Johnson");
    int sample_scores[kScoresSize] = {kScore31, kScore32, kScore33, kScore34,
                                      kScore35};
    memcpy(athlete4->scores, sample_scores, sizeof(sample_scores));

    QString result =
        QString(
            "Возраст: %1 | Рост: %2м | Пол: %3 | Профессионал?: %4 | Имя: %5 | "
            "Результаты за 5 матчей: %6, %7, %8, %9, %10")
            .arg(athlete4->age)
            .arg(athlete4->height)
            .arg(athlete4->gender)
            .arg(athlete4->isProfessional ? "Да" : "Нет")
            .arg(QString::fromStdString(athlete4->name))
            .arg(athlete4->scores[0])
            .arg(athlete4->scores[1])
            .arg(athlete4->scores[2])
            .arg(athlete4->scores[3])
            .arg(athlete4->scores[4]);

    struct4_label_->setText(result);
}

void Window::PrintStruct5() {
    Sportsman athlete5;
    Sportsman& ref = athlete5;
    ref.age = kAge4;
    ref.height = kHeight4;
    ref.gender = 'F';
    ref.isProfessional = false;
    strcpy(ref.name, "Anna");
    int scores4[kScoresSize] = {kScore41, kScore42, kScore43, kScore44,
                                kScore45};
    memcpy(ref.scores, scores4, sizeof(scores4));

    QString result =
        QString(
            "Возраст: %1 | Рост: %2м | Пол: %3 | Профессионал?: %4 | Имя: %5 | "
            "Результаты за 5 матчей: %6, %7, %8, %9, %10")
            .arg(ref.age)
            .arg(ref.height)
            .arg(ref.gender)
            .arg(ref.isProfessional ? "Да" : "Нет")
            .arg(QString::fromStdString(ref.name))
            .arg(ref.scores[0])
            .arg(ref.scores[1])
            .arg(ref.scores[2])
            .arg(ref.scores[3])
            .arg(ref.scores[4]);

    struct5_label_->setText(result);
}
