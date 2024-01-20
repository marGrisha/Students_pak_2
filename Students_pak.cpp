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
    void tellAboutOneRandomChild() const
    {
        if (children.empty())
        {
            std::cout << "Нет студентов для рассказа." << std::endl;
            return;
        }

        int randomIndex = rand() % children.size();
        tellAboutChild(children[randomIndex]);
        std::cout << std::endl;
    }

    void tellAboutAverageChildren() const
    {
        if (children.empty())
        {
            std::cout << "Нет студентов для рассказа." << std::endl;
            return;
        }

        double averageMark = calculateAverageMark();
        std::cout << "Рассказ о средней успеваемости студентов: " << (averageMark >= 4.5 ? "Хорошая" : "Плохая") << std::endl;
        std::cout << std::endl;
    }

    void tellAboutSpecificChild(const Student *Student) const
    {
        auto it = std::find(children.begin(), children.end(), Student);
        if (it != children.end())
        {
            tellAboutChild(*it);
        }
        else
        {
            std::cout << "Ошибка: Этот студент не является ребенком родителя/опекуна." << std::endl;
        }
    }

protected:
    virtual void tellAboutChild(const Student *Student) const
    {
        std::cout << "Опекун/родитель " << name << " рассказывает о своем ребенке " << Student->getName() << ": ";
        if (goodMood)
        {
            std::cout << (Student->isExcellentStudent() ? "Отличник" : "Не отличник") << std::endl;
        }
        else
        {
            std::cout << "У всегда все хорошо." << std::endl;
        }
    }

    double calculateAverageMark() const
    {
        double sum = 0.0;
        for (const Student *Student : children)
        {
            sum += (Student->isExcellentStudent() ? 5.0 : 3.0);
        }

        return sum / children.size();
    }

private:
    std::string name;
    bool goodMood = (rand() % 2 == 0);
    std::vector<const Student *> children;
};

class GrandParent : public Parent
{
public:
    GrandParent(std::string name) : Parent(name) {}
    void tellAboutChild(const Student *Student) const override
    {
        if (hasChild(*Student))
        {
            std::cout << "Бабушка " << getName() << " рассказывает о своем внуке " << Student->getName() << ": ";
            std::cout << "Всегда был хорошим, красивым, но лентяем." << std::endl;
        }
        else
        {
            // Бабушка рассказывает
            std::cout << "Бабушка " << getName() << " рассказывает о чужом ребенке " << Student->getName() << ": ";
            if (goodMood)
            {
                std::cout << (Student->isExcellentStudent() ? "Отличник" : "Не отличник") << std::endl;
            }
            else
            {
                std::cout << "У все норм." << std::endl;
            }
        }
    }

private:
    std::string name;
    bool goodMood = (rand() % 2 == 0);
    std::vector<const Student *> children;
};

class Council
{
public:
    Council(const std::string &name) : name(name) {}

    void addParticipant(Tutor &tutor)
    {
        tutors.push_back(&tutor);
    }

    void addParticipant(Parent &Parent)
    {
        Parents.push_back(&Parent);
    }

    void discussSubjects()
    {
        std::cout << "Начало обсуждения на собрании: " << name << std::endl;

        for (Subject &subject : subjects)
        {
            std::cout << "Обсуждение предмета: " << subject.getName() << std::endl;

            for (Tutor *tutor : tutors)
            {
                if (subject.hasTutor(*tutor))
                {
                    for (Student *Student : subject.getStudents())
                    {
                        Parent *Parent = findParentOfStudent(*Student);
                        if (Parent)
                        {
                            Parent->tellAboutSpecificChild(Student);
                        }
                        else
                        {

                            childrenWithoutParents.push_back(Student);
                        }
                    }
                }
            }
        }

        // огласка списка студентов, чьи опекуны отсутствуют на собрании
        if (!childrenWithoutParents.empty())
        {
            std::cout << "Дети, чьи родители/опекуны отсутствуют на собрании:" << std::endl;
            for (const Student *Student : childrenWithoutParents)
            {
                std::cout << Student->getName() << std::endl;
            }
        }

        std::cout << "Завершение собрания: " << name << std::endl;
    }

    void addSubject(const Subject &subject)
    {
        subjects.push_back(subject);
    }

private:
    Parent *findParentOfStudent(const Student &Student)
    {
        for (Parent *Parent : Parents)
        {
            if (Parent->hasChild(Student))
            {
                return Parent;
            }
        }
        return nullptr;
    }

    std::string name;
    std::vector<Tutor *> tutors;
    std::vector<Parent *> Parents;
    std::vector<Subject> subjects;
    std::vector<const Student *> childrenWithoutParents;
};

int main()
{
    std::srand(std::time(0));
    setlocale(LC_ALL, "Russian");

    Tutor tutor1("Волобуев");
    RandomlyTutor tutor2("Марицкий");
    GrandParent Parent1("Зина");
    Parent Parent2("Иван");
    Student Student1("Сухоруков");
    Student Student2("Киселев");
    Student Student3("Сидоров");

    Parent1.addChild(Student1);
    Parent2.addChild(Student2);

    Subject subject1("Математический анализ");
    subject1.addTutor(tutor1);
    subject1.addTutor(tutor2);
    subject1.addStudent(Student1);
    subject1.addStudent(Student2);
    subject1.conductSubject();

    Subject subject2("Математическая логика");
    subject2.addTutor(tutor2);
    subject2.addStudent(Student3);
    subject2.conductSubject();

    Parent1.tellAboutAllChildren();
    Parent2.tellAboutOneRandomChild();

    tutor1.addMark(Student1, 4);
    tutor1.addMark(Student2, 5);
    tutor1.addMark(Student3, 3);

    Parent1.tellAboutSpecificChild(&Student1);
    Parent2.tellAboutAverageChildren();

    Council council("Университетское собрание");
    council.addParticipant(tutor1);
    council.addParticipant(tutor2);
    council.addParticipant(Parent1);
    council.addParticipant(Parent2);
    council.addSubject(subject1);
    council.addSubject(subject2);

    council.discussSubjects();

    return 0;
}
// мяу