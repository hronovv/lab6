#ifndef TASK2_STRUCT_H
#define TASK2_STRUCT_H
constexpr int kNameSize = 200;
constexpr int kScoresSize = 5;


struct Sportsman {
    int age;
    double height;
    char gender;
    bool isProfessional;
    char name[kNameSize];
    int scores[kScoresSize];
};

#endif	//TASK2_STRUCT_H
