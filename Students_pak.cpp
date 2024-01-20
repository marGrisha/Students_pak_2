#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>

class Student
{
public:
    Student(std::string name) : name(name) {}

    const std::string &getName() const
    {
        return name;
    }

    void addMark(int mark)
    {
        marks.push_back(mark);
    }

    bool isExcellentStudent() const
    {
        return calculateAverageMark() >= 4.5;
    }

private:
    double calculateAverageMark() const
    {
        if (marks.empty())
        {
            return 0.0;
        }

        double sum = 0.0;
        for (int mark : marks)
        {
            sum += mark;
        }

        return sum / marks.size();
    }

private:
    std::string name;
    std::vector<int> marks;
};

class Tutor
{
public:
    Tutor(std::string name) : name(name) {}

    const std::string &getName() const
    {
        return name;
    }

    bool getMood() const
    {
        return goodMood;
    }

    virtual void addMarkRandomly(Student &Student)
    {
        int adjustedMark = calculateAdjustedMark(Student.isExcellentStudent());
        Student.addMark(adjustedMark);
        markCount++;

        std::cout << "Препод " << name << " поставил оценку " << adjustedMark
                  << " студенту " << Student.getName() << " с " << (goodMood ? "хорошим" : "плохим") << " настроением" << std::endl;

        if (markCount % 5 == 0)
        {
            changeMoodRandomly();
            std::cout << "Настроение препода " << name << " изменилось: "
                      << (goodMood ? "Хорошее" : "Плохое") << std::endl;
        }
    }