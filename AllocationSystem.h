#ifndef ALLOC_H
#define ALLOC_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

string getWordFromString(const string& inString, int position);
string getSubString(const string &inString, int start_word_position);
int stringToInt(const string& inString);

class Supervisor{

public:
    Supervisor();
    ~Supervisor();
    Supervisor(const string& inputLine);

    const string& getId() const;
    int getLoad() const;
    int getAllocations() const;
    void addAllocations();
    bool isAvailable() const;
    void validateAllocation();


private:
    string id_;
    int load_;
    int allocations_;   // To keep trac of no of allocated students.txt
};

class Project{

public:
    Project();
    ~Project();
    Project(const string& inputLine);

    int getId() const;
    const string& getSupervisorId() const;
    int getMultiplicity() const;
    const string& getProjectTitle() const;
    int getAllocations() const;
    void addAllocations();
    bool isAvailable() const;
    void validateAllocation();

private:
    int id_;
    string supervisor_id_;
    int multiplicity_;
    string project_title_;
    int allocations_;   // To keep trac of no of allocated students.txt
};

class Student{

public:
    Student();
    ~Student();
    Student(const string& inputLine);

    const string& getId() const;
    const vector<int>& getChoices() const;

    bool isAllocated() const;
    void setAllocated(bool inAllocated);

private:
    string id_;
    bool allocated_;
    vector<int> choices_;
};

class Alloc {
public:
    Alloc();
    ~Alloc();
    Alloc(const string& inputLine);
    Alloc(const string& studentId, int projectId);

    const string& getStudentId() const;
    int getProjectId() const;
    string print() const;
    void allocScore(int choice);
    int getScore() const;

private:
    string student_id_;
    int project_id_;
    int score_;

};

class ProjectAllocator {
public:
    ProjectAllocator(vector<Supervisor*>& supervisorFile, vector<Project*>& projectFile, vector<Student*>& studentFile, vector<Alloc*>& allocFile);
    ~ProjectAllocator();

    void allocateProject();
    void validateAllocation();
    int countStudentAllocations(const string& studentId);
    string print();

private:
    vector<Supervisor*>& supervisors;
    vector<Project*>& projects;
    vector<Student*>& students;
    vector<Alloc*>& allocations;

    Project* findProjectById(int id);
    Supervisor* findSupervisorById(const string& id);
    Student* findStudentById(const string& id);
    Project* findAvailableProject(Student* forStudent);
    void validateAllocationByChoices(Student* forStudent, Project* allocatedProject);
};

#endif //ALLOC_H