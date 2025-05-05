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

    auto* wchar_button =
        new QPushButton("Посимвольная запись/вывод wchar(перезапись)");
    wchar_button->setFixedSize(kButtonWidth, kButtonHeight);
    wchar_button->setStyleSheet(button_style);
    connect(wchar_button, &QPushButton::clicked, this,
            &Window::Wchar_Write_Read);

    auto* array_button = new QPushButton("Массив: запись/чтение(перезапись)");
    array_button->setFixedSize(kButtonWidth, kButtonHeight);
    array_button->setStyleSheet(button_style);
    connect(array_button, &QPushButton::clicked, this, &Window::Arr_Write_Read);

    auto* sportsman_button =
        new QPushButton("Запись/чтение спортсменов(дозапись)");
    sportsman_button->setFixedSize(kButtonWidth, kButtonHeight);
    sportsman_button->setStyleSheet(button_style);
    connect(sportsman_button, &QPushButton::clicked, this,
            &Window::EnterAndSaveSportsmanData);

    auto* sportsman_binary_button =
        new QPushButton("Запись/чтение спортсменов(дозапись/бинарно)");
    sportsman_binary_button->setFixedSize(kButtonWidth, kButtonHeight);
    sportsman_binary_button->setStyleSheet(button_style);
    connect(sportsman_binary_button, &QPushButton::clicked, this,
            &Window::EnterAndSaveSportsmanData_Binary);

    auto* sentence_button =
        new QPushButton("Запись/чтение предложений(дозапись)", this);
    sentence_button->setFixedSize(kButtonWidth, kButtonHeight);
    sentence_button->setStyleSheet(button_style);
    connect(sentence_button, &QPushButton::clicked, this,
            &Window::EnterAndSaveSentence);

    auto* button_layout = new QVBoxLayout(this);
    button_layout->addWidget(wchar_button);
    button_layout->addWidget(array_button);
    button_layout->addWidget(sportsman_button);
    button_layout->addWidget(sportsman_binary_button);
    button_layout->addWidget(sentence_button);
    button_layout->setSpacing(kSpacing);
    button_layout->setContentsMargins(kMargins, kMargins, kMargins, kMargins);
    button_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    setLayout(button_layout);
}


void Window::Wchar_Write_Read() {
    bool ok = false;
    QString qtext = QInputDialog::getText(
        nullptr, "wchar", "Введите текст:", QLineEdit::Normal, "", &ok);


    if (!ok) {
        QMessageBox::information(this, "Отмена",
                                 "Операция отменена пользователем.");
        return;
    }
    if (qtext.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите непустой текст.");
        return;
    }
    std::wstring text = qtext.toStdWString();
    std::wofstream file(
        "/Users/hronov/CLionProjects/Lab6_fixed/Task2/Lab6_1.txt",
        std::ios::out);
    file.imbue(std::locale("ru_RU.UTF-8"));


    if (!file) {
        QMessageBox::critical(this, "Ошибка",
                              "Не удалось открыть файл для записи!");
        return;
    }


    for (wchar_t ch : text) {
        file.put(ch);
    }
    file.close();
    QMessageBox::information(this, "Успех",
                             "Текст успешно записан в файл Lab6_1.txt\n");
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Чтение файла", "Прочитать содержимое файла?",
        QMessageBox::Yes | QMessageBox::No);


    if (reply != QMessageBox::Yes) {
        QMessageBox::information(this, "Отмена", "Чтение файла отменено.");
        return;
    }
    std::wifstream read_file(
        "/Users/hronov/CLionProjects/Lab6_fixed/Task2/Lab6_1.txt",
        std::ios::in);
    read_file.imbue(std::locale("ru_RU.UTF-8"));


    if (!read_file) {
        QMessageBox::critical(this, "Ошибка",
                              "Не удалось открыть файл для чтения!");
        return;
    }
    std::wstring w_text;
    wchar_t ch;
    while (read_file.get(ch)) {
        w_text += ch;
    }
    read_file.close();
    std::wcout.imbue(std::locale("ru_RU.UTF-8"));
    QMessageBox::information(this, "w_string",
                             "Ваш текст: " + QString::fromStdWString(w_text));
}

void Window::Arr_Write_Read() {
    bool ok = false;
    int size = 0;


    while (true) {
        QString input = QInputDialog::getText(
            nullptr, "Размер массива",
            "Введите размер массива:", QLineEdit::Normal, "", &ok);
        if (!ok) {
            QMessageBox::warning(this, "Отмена", "Операция отменена.");
            return;
        }
        bool is_number = false;
        size = input.toInt(&is_number);
        if (is_number && size > 0) {
            break;
        }
        QMessageBox::warning(this, "Ошибка",
                             "Введите корректное положительное число!");
    }
    std::vector<int> arr;


    for (int i = 0; i < size; ++i) {
        int value = 0;
        while (true) {
            QString prompt =
                "Введите элемент массива №" + QString::number(i + 1) + ":";
            QString input = QInputDialog::getText(
                nullptr, "Элемент массива", prompt, QLineEdit::Normal, "", &ok);
            if (!ok) {
                QMessageBox::warning(this, "Отмена", "Операция отменена.");
                return;
            }
            bool is_number = false;
            value = input.toInt(&is_number);
            if (is_number) {
                break;
            }
            QMessageBox::warning(this, "Ошибка",
                                 "Введите корректное целое число!");
        }
        arr.push_back(value);
    }
    std::ofstream write_arr(
        "/Users/hronov/CLionProjects/Lab6_fixed/Task2/Lab6_2.txt",
        std::ios::out);


    if (!write_arr) {
        QMessageBox::critical(this, "Ошибка",
                              "Не удалось открыть файл для записи!");
        return;
    }


    for (int a : arr) {
        write_arr << a << "\\";
    }
    write_arr.close();
    QMessageBox::information(this, "Успех",
                             "Массив успешно записан в Lab6_2.txt");

    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Чтение массива", "Прочитать содержимое файла?",
        QMessageBox::Yes | QMessageBox::No);


    if (reply != QMessageBox::Yes) {
        QMessageBox::information(this, "Отмена", "Чтение файла отменено.");
        return;
    }

    std::ifstream read_file(
        "/Users/hronov/CLionProjects/Lab6_fixed/Task2/Lab6_2.txt",
        std::ios::in);


    if (!read_file) {
        QMessageBox::critical(this, "Ошибка",
                              "Не удалось открыть файл для чтения!");
        return;
    }
    std::string file_content;
    std::getline(read_file, file_content);
    read_file.close();
    std::stringstream ss(file_content);
    std::string token;
    QString output;
    while (std::getline(ss, token, '\\')) {
        if (!token.empty()) {
            output += QString::number(std::stoi(token)) + " ";
        }
    }
    QMessageBox::information(this, "Массив из файла",
                             "Прочитанные элементы:\n" + output);
}

void Window::EnterAndSaveSportsmanData() {
    bool ok = false;
    QString isprof;
    Sportsman sportsman;
    bool input_ok = false;
    sportsman.age =
        QInputDialog::getInt(this, "Возраст", "Введите возраст спортсмена:", 0,
                             0, kMaxAge, 1, &input_ok);


    if (!input_ok) {
        return;
    }
    sportsman.height =
        QInputDialog::getDouble(this, "Рост", "Введите рост спортсмена:", 0.0,
                                0.0, kMaxHeight, 2, &input_ok);


    if (!input_ok) {
        return;
    }
    isprof = QInputDialog::getText(this, "Профессионал?",
                                   "Введите, профессионал или нет (Yes/No):");
    sportsman.isProfessional = (isprof.toLower() == "yes");
    QString name =
        QInputDialog::getText(this, "Имя", "Введите имя спортсмена:");
    if (name.length() >= kNameSize) {
        QMessageBox::warning(this, "Ошибка", "Имя слишком длинное!");
        return;
    }
    std::strncpy(sportsman.name, name.toStdString().c_str(), kNameSize - 1);
    sportsman.name[kNameSize - 1] = '\0';
    QVector<int> scores;


    for (int i = 0; i < kScoresSize; i++) {
        int score = QInputDialog::getInt(
            this, "Результаты", QString("Введите результат %1:").arg(i + 1), 0,
            0, kMaxScore, 1, &input_ok);
        if (!input_ok) {
            return;
        }
        scores.push_back(score);
    }
    std::copy(scores.begin(), scores.end(), std::begin(sportsman.scores));
    std::ofstream ofs("/Users/hronov/CLionProjects/Lab6_fixed/Task2/Lab6_3.txt",
                      std::ios::app);
    ofs << sportsman.age << std::endl
        << sportsman.height << std::endl
        << sportsman.isProfessional << std::endl
        << sportsman.name << std::endl;


    for (int score : sportsman.scores) {
        ofs << score << std::endl;
    }
    ofs.close();
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Чтение данных", "Прочитать содержимое файла?",
        QMessageBox::Yes | QMessageBox::No);


    if (reply == QMessageBox::Yes) {
        std::ifstream ifs(
            "/Users/hronov/CLionProjects/Lab6_fixed/Task2/Lab6_3.txt",
            std::ios::in);
        while (true) {
            int temp_age;
            double temp_height;
            bool temp_prof;
            char temp_name[kNameSize];
            int temp_scores[kScoresSize];
            if (!(ifs >> temp_age)) {
                break;
            }
            ifs >> temp_height >> temp_prof >> temp_name;
            for (int i = 0; i < kScoresSize; i++) {
                ifs >> temp_scores[i];
            }
            QString output = QString(
                                 "Возраст: %1 | Рост: %2 | Профессионал: %3 | "
                                 "Имя: %4\nРезультаты: ")
                                 .arg(temp_age)
                                 .arg(temp_height)
                                 .arg(temp_prof ? "Да" : "Нет")
                                 .arg(QString::fromUtf8(temp_name));
            for (int score : temp_scores) {
                output += QString::number(score) + " ";
            }
            QMessageBox::information(this, "Данные спортсменов", output);
        }
        ifs.close();
    } else {
        QMessageBox::information(this, "Отмена", "Чтение файла отменено.");
    }
}

void Window::EnterAndSaveSportsmanData_Binary() {
    bool ok = false;
    QString isprof;
    Sportsman sportsman;
    bool input_ok = false;
    sportsman.age =
        QInputDialog::getInt(this, "Возраст", "Введите возраст спортсмена:", 0,
                             0, kMaxAge, 1, &input_ok);


    if (!input_ok) {
        return;
    }
    sportsman.height =
        QInputDialog::getDouble(this, "Рост", "Введите рост спортсмена:", 0.0,
                                0.0, kMaxHeight, 2, &input_ok);


    if (!input_ok) {
        return;
    }
    isprof = QInputDialog::getText(this, "Профессионал?",
                                   "Введите, профессионал или нет (Yes/No):");
    sportsman.isProfessional = (isprof.toLower() == "yes");
    QString name =
        QInputDialog::getText(this, "Имя", "Введите имя спортсмена:");
    if (name.length() >= kNameSize) {
        QMessageBox::warning(this, "Ошибка", "Имя слишком длинное!");
        return;
    }
    std::strncpy(sportsman.name, name.toStdString().c_str(), kNameSize - 1);
    sportsman.name[kNameSize - 1] = '\0';
    QVector<int> scores;


    for (int i = 0; i < kScoresSize; i++) {
        int score = QInputDialog::getInt(
            this, "Результаты", QString("Введите результат %1:").arg(i + 1), 0,
            0, kMaxScore, 1, &input_ok);
        if (!input_ok) {
            return;
        }
        scores.push_back(score);
    }
    std::copy(scores.begin(), scores.end(), std::begin(sportsman.scores));
    std::ofstream ofs("/Users/hronov/CLionProjects/Lab6_fixed/Task2/Lab6_4.bin",
                      std::ios::app | std::ios::binary);


    if (!ofs) {
        QMessageBox::critical(this, "Ошибка",
                              "Не удалось открыть файл для записи!");
        return;
    }
    ofs.write((char*)&sportsman, sizeof(Sportsman));
    ofs.close();
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Чтение данных", "Прочитать содержимое файла?",
        QMessageBox::Yes | QMessageBox::No);


    if (reply == QMessageBox::Yes) {
        std::ifstream ifs(
            "/Users/hronov/CLionProjects/Lab6_fixed/Task2/Lab6_4.bin",
            std::ios::in | std::ios::binary);
        if (!ifs) {
            QMessageBox::critical(this, "Ошибка",
                                  "Не удалось открыть файл для чтения!");
            return;
        }
        while (true) {
            Sportsman temp_sportsman;
            if (!ifs.read((char*)&temp_sportsman, sizeof(Sportsman))) {
                break;
            }
            QString output =
                QString(
                    "Возраст: %1 ; Рост: %2 ; Профессионал: %3 ; Имя: "
                    "%4\nРезультаты: ")
                    .arg(temp_sportsman.age)
                    .arg(temp_sportsman.height)
                    .arg(temp_sportsman.isProfessional ? "Да" : "Нет")
                    .arg(QString::fromUtf8(temp_sportsman.name));

            for (int score : temp_sportsman.scores) {
                output += QString::number(score) + " ";
            }
            QMessageBox::information(this, "Данные спортсменов", output);
        }
        ifs.close();
    } else {
        QMessageBox::information(this, "Отмена", "Чтение файла отменено.");
    }
}

void Window::EnterAndSaveSentence() {
    bool ok = false;
    QString qstr =
        QInputDialog::getText(this, "Введите предложение",
                              "Введите строку:", QLineEdit::Normal, "", &ok);
    if (!ok || qstr.isEmpty()) {
        return;
    }
    std::string input = qstr.toStdString();
    const std::string file_path =
        "/Users/hronov/CLionProjects/Lab6_fixed/Task2/Lab6_5.txt";
    std::ofstream ofs(file_path, std::ios::app);


    if (!ofs) {
        QMessageBox::critical(this, "Ошибка",
                              "Не удалось открыть файл для записи!");
        return;
    }
    ofs << input << std::endl;
    ofs.close();
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Чтение файла", "Прочитать все строки из файла?",
        QMessageBox::Yes | QMessageBox::No);


    if (reply != QMessageBox::Yes) {
        QMessageBox::information(this, "Отмена", "Чтение файла отменено.");
        return;
    }
    std::ifstream ifs(file_path, std::ios::in);


    if (!ifs) {
        QMessageBox::critical(this, "Ошибка",
                              "Не удалось открыть файл для чтения!");
        return;
    }
    std::string line;
    int line_number = 1;
    while (std::getline(ifs, line)) {
        QString qline = QString::fromStdString(line);
        QString title = QString("Строка %1").arg(line_number++);
        QMessageBox::information(this, title, qline);
    }
    ifs.close();
}
