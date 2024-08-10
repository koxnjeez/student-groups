#include "settings.h"

class Student {
	char* name = new char[200];
	float average_grade;

public:
	//~Student() {
	//    if (name != nullptr)
	//        delete[] name;
	//}

	Student(string name, float average_grade) {
		strcpy_s(this->name, 200, name.c_str());
		this->average_grade = average_grade;
	}
	Student(string name) : Student(name, rand() % (12 - 1 + 1) + 1) {}
	Student() : Student("Unknown student", rand() % (12 - 1 + 1) + 1) {}

	void SetName(const string& name) {
		strcpy_s(this->name, 200, name.c_str());
	}
	void SetAveGrade(const float average_grade) {
		this->average_grade = average_grade;
	}
	string GetName() const {
		return name;
	}
	float GetAveGrade() {
		return average_grade;
	}

	void Print() {
		cout << name << " --- average grade: " << average_grade << "\n";
	}
};

class Group {
	Student** students = nullptr;
	unsigned short count_students;
	string group_name;
	string group_specialty;
	unsigned short course;

public:
	Group(const Group& orig) {
		this->students = new Student * [count_students];
		for (int i = 0; i < count_students; i++) {
			this->students[i] = orig.students[i];
		}
		this->count_students = orig.count_students;
		this->group_name = orig.group_name;
		this->group_specialty = orig.group_specialty;
		this->course = orig.course;
	}

	~Group() {
		if (students != nullptr)
			delete[] students;
	}

	Group(string group_name, string group_specialty, unsigned short course) {
		count_students = 0;
		students = new Student * [count_students];
		SetGroupName(group_name);
		SetGroupSpecialty(group_specialty);
		SetCourse(course);
	}
	Group(string group_name, string group_specialty) : Group(group_name, group_specialty, 1) {}
	Group(string group_name, unsigned short course) : Group(group_name, "###", course) {}
	Group(string group_name) : Group(group_name, "###", 1) {}
	Group() : Group("###", "###", 1) {}


	void SetGroupName(const string group_name) {
		this->group_name = group_name;
	}
	void SetGroupSpecialty(const string group_specialty) {
		this->group_specialty = group_specialty;
	}
	void SetCourse(const unsigned short course) {
		this->course = course;
	}
	string GetGroupName() const {
		return group_name;
	}
	string GetGroupSpecialty() const {
		return group_specialty;
	}
	unsigned short GetCourse() const {
		return course;
	}

	void AddStudent(Student new_member) {
		count_students++;
		Student** copy = students;
		students = new Student * [count_students];
		for (int i = 0; i < count_students; i++) {
			if (i < count_students - 1) {
				students[i] = copy[i];
			}
			else {
				students[count_students - 1] = new Student(new_member);
			}
		}
		delete[] copy;
	}
	void AddStudent(string name, float average_grade) {
		count_students++;
		Student** copy = students;
		students = new Student * [count_students];
		for (int i = 0; i < count_students; i++) {
			if (i < count_students - 1) {
				students[i] = copy[i];
			}
			else {
				students[count_students - 1] = new Student(name, average_grade);
			}
		}
		delete[] copy;
	}
	void Print() {
		cout << "Group named \"" << GetGroupName() << "\"\nSpecialty: " << GetGroupSpecialty() << " (" << GetCourse() << " course)\nStudents (" << count_students << " members):\n";
		for (int i = 0; i < count_students; i++) {
			students[i]->Print();
		}
		cout << "\n";
	}
};

int main() {
	srand(time(0));
	Group P26("P26", "Developers", 3);
	P26.AddStudent("Chervonenko Vlad", 11);
	P26.AddStudent("Bazelyan Ivan", 12);
	P26.AddStudent("Lolo Muchammed", 10);
	P26.Print();
}