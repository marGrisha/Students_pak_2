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
    void addMarkRandomly(Student &Student) override
    {
        addMark(Student);
    }

private:
    int randomNumberMood = rand() % 3 + 3;
};

class Subject
{
public:
    Subject(std::string name) : name(name) {}

    const std::string &getName() const
    {
        return name;
    }
    void addTutor(Tutor &tutor)
    {
        tutors.push_back(&tutor);
    }

    void addStudent(Student &Student)
    {
        Students.push_back(&Student);
    }

    bool hasTutor(const Tutor &tutor) const
    {
        return std::find(tutors.begin(), tutors.end(), &tutor) != tutors.end();
    }

    const std::vector<Student *> &getStudents() const
    {
        return Students;
    }
    void conductSubject()
    {
        std::cout << "препода: ";
        for (Tutor *tutor : tutors)
        {
            std::cout << tutor->getName() << " ";
        }
        std::cout << "провели занятие студентам: ";
        for (Student *Student : Students)
        {
            std::cout << Student->getName() << " ";
        }
        std::cout << std::endl
                  << "Результаты пары " << this->getName() << ":" << std::endl;
        std::cout << "-------------" << std::endl;
        for (Tutor *tutor : tutors)
        {
            for (Student *Student : Students)
            {
                if (rand() % 2 == 0)
                {
                    if (tutor->getMood())
                    {
                        // В хорошем настроении
                        int numMarks = rand() % 5 + 1;
                        for (int i = 0; i < numMarks; ++i)
                        {
                            tutor->addMarkRandomly(*Student);
                        }
                    }
                    else
                    {
                        // В плохом настроении
                        int numMarks = rand() % 3 + 1;
                        for (int i = 0; i < numMarks; ++i)
                        {
                            tutor->addMarkRandomly(*Student);
                        }
                    }
                }
            }
        }
        std::cout << "-------------" << std::endl;
    }

private:
    std::string name;
    std::vector<Tutor *> tutors;
    std::vector<Student *> Students;
};

class Parent
{
public:
    Parent(std::string name) : name(name) {}

    const std::string &getName() const
    {
        return name;
    }

    void addChild(Student &Student)
    {
        children.push_back(&Student);
    }

    bool hasChild(const Student &Student) const
    {
        return std::find(children.begin(), children.end(), &Student) != children.end();
    }

    void tellAboutAllChildren() const
    {
        std::cout << "Рассказ о всех студентах:" << std::endl;
        for (const Student *Student : children)
        {
            tellAboutChild(Student);
        }
        std::cout << std::endl;
    }