#include <algorithm>
#include "AllocationSystem.h"

// ------------------- Global Functions ----------------------
string getWordFromString(const string& inString, int position) {
    string word;

    int current_position = 1;
    for (auto itr: inString) {
        if (itr == ' ') {
            if (current_position == position) {
                if(!word.empty()){
                    return word;
                }
            }
            word = "";
            current_position += 1;
        } else {
            word += itr;
        }
    }

    if (current_position == position) {
        return word;
    }

    return "";
}

string getSubString(const string& inString, int start_word_position) {
    string substring;

    while (true) {
        string word = getWordFromString(inString, start_word_position);

        if (word.empty()) {
            break;
        }
        substring += word;
        substring += " ";

        start_word_position += 1;
    }

    return substring.substr(0, substring.size() - 1);
}

int noOfWordsInString(const string &inString) {
    int word_count = 0;

    for(auto itr : inString){
        if(itr == ' '){
            word_count++;
        }
    }

    word_count++;

    return word_count;
}

int stringToInt(const string& inString) {
    if(inString.empty()){
        return -1;
    }

    try{
        return stoi(inString);
    }
    catch (const std::invalid_argument& ia) {
        return -1;
    }
    catch (const std::out_of_range& oor) {
        return -1;
    }
    catch (const std::exception& e)
    {
        return -1;
    }
}

// ------------------- Supervisor Class ----------------------

Supervisor::Supervisor() {
    id_ = "";
    load_ = -1;
    allocations_ = 0;
}

Supervisor::~Supervisor() = default;

Supervisor::Supervisor(const string& inputLine) {
    id_ = getWordFromString(inputLine, 1);
    load_ = stringToInt(getWordFromString(inputLine, 2));
    allocations_ = 0;
}

const string& Supervisor::getId() const {
    return id_;
}

int Supervisor::getLoad() const {
    return load_;
}

int Supervisor::getAllocations() const {
    return allocations_;
}

void Supervisor::addAllocations() {
    allocations_++;
}

bool Supervisor::isAvailable() const {
    if(allocations_ < load_ && load_ > 0){
        return true;
    }
    return false;
}

void Supervisor::validateAllocation() {
    if(allocations_ > load_){
        cout << "Supervisor " << "\"" << id_ << "\""
             << " has load " << load_
             << " but is allocated "
             << allocations_ << " projects" << endl;
    }
}

// ------------------- Project Class ----------------------

Project::Project() {
    id_ = -1;
    supervisor_id_ = "";
    multiplicity_ = -1;
    project_title_ = "";
    allocations_ = 0;
}

Project::~Project() = default;

Project::Project(const string& inputLine) {
    id_ = stringToInt(getWordFromString(inputLine, 1));
    supervisor_id_ = getWordFromString(inputLine, 2);
    multiplicity_ = stringToInt(getWordFromString(inputLine, 3));
    project_title_ = getSubString(inputLine, 4);
    allocations_ = 0;
}

int Project::getId() const {
    return id_;
}

const string& Project::getSupervisorId() const {
    return supervisor_id_;
}

int Project::getMultiplicity() const {
    return multiplicity_;
}

const string& Project::getProjectTitle() const {
    return project_title_;
}

int Project::getAllocations() const {
    return allocations_;
}

void Project::addAllocations() {
    allocations_++;
}

bool Project::isAvailable() const {
    if(allocations_ < multiplicity_ && multiplicity_ > 0){
        return true;
    }
    return false;
}

void Project::validateAllocation() {
    if(allocations_ > multiplicity_){
        cout << "Project " << "\"" << id_ << "\""
            << " has multiplicity " << multiplicity_
            << " but is allocated to "
            << allocations_ << " students" << endl;
    }
}

// ------------------- Student Class ----------------------

Student::Student() {
    id_ = "";
    allocated_ = false;
}

Student::~Student() = default;

Student::Student(const string& inputLine) {
    id_ = getWordFromString(inputLine, 1);
    for (int itr = 2; itr < 6; itr++) {
        string temp_string = getWordFromString(inputLine, itr);
        if(temp_string.empty()){
            choices_.emplace_back(-1);
        }
        else{
            choices_.push_back(stringToInt(temp_string));
        }
    }
    allocated_ = false;
}

const string& Student::getId() const {
    return id_;
}

const vector<int>& Student::getChoices() const {
    return choices_;
}

bool Student::isAllocated() const {
    return allocated_;
}

void Student::setAllocated(const bool inAllocated) {
    allocated_ = inAllocated;
}

// ------------------- Alloc class ----------------------
Alloc::Alloc() {
    student_id_ = "";
    project_id_ = -1;
    score_ = 0;
}

Alloc::Alloc(const string &inputLine) {
    student_id_ = getWordFromString(inputLine, 1);
    project_id_ = stringToInt(getWordFromString(inputLine, 2));
    score_ = 0;
}

Alloc::Alloc(const string& studentId, const int projectId) {
    student_id_ = studentId;
    project_id_ = projectId;
    score_ = 0;
}

Alloc::~Alloc() = default;

const string& Alloc::getStudentId() const {
    return student_id_;
}

int Alloc::getProjectId() const {
    return project_id_;
}

string Alloc::print() const {
    string out_string = student_id_;
    out_string += " ";
    out_string += to_string(project_id_);
    out_string += "\n";
    return out_string;
}

void Alloc::allocScore(int choice) {
    switch (choice) {
        case 1:
            score_ = 4;
            break;
        case 2:
            score_ = 3;
            break;
        case 3:
            score_ = 2;
            break;
        case 4:
            score_ = 1;
            break;
        default:
            score_ = 0;
            break;
    }
}

int Alloc::getScore() const {
    return score_;
}

// ------------------- ProjectAllocator class ----------------------

ProjectAllocator::ProjectAllocator(vector<Supervisor*>& supervisorFile, vector<Project*>& projectFile, vector<Student*>& studentFile, vector<Alloc*>& allocFile)
                : supervisors(supervisorFile), projects(projectFile), students(studentFile), allocations(allocFile)
{
}

ProjectAllocator::~ProjectAllocator() {
    for(auto supervisor : supervisors){
        delete supervisor;
    }
    for(auto project : projects){
        delete project;
    }
    for(auto student : students){
        delete student;
    }
    for(auto alloc : allocations){
        delete alloc;
    }
}

void ProjectAllocator::allocateProject() {
    for(int itr=0; itr<4; itr++){
        for(auto student : students){
            if(!student->isAllocated()){
                Project* curr_project = findProjectById(student->getChoices().at(itr));

                if(curr_project != nullptr){
                    Supervisor* curr_supervisor = findSupervisorById(curr_project->getSupervisorId());
                    if(curr_supervisor != nullptr){
                        if(curr_project->isAvailable() && curr_supervisor->isAvailable()){
                            curr_project->addAllocations();
                            curr_supervisor->addAllocations();
                            student->setAllocated(true);
                            Alloc* alloc = new Alloc(student->getId(), curr_project->getId());
                            alloc->allocScore(itr+1);
                            allocations.push_back(alloc);
                        }
                    }
                }
            }
        }
    }

    for(auto student : students){
        for(auto project : projects){
            if(!student->isAllocated()) {
                if (project != nullptr) {
                    Supervisor *curr_supervisor = findSupervisorById(project->getSupervisorId());
                    if (curr_supervisor != nullptr) {
                        if (project->isAvailable() && curr_supervisor->isAvailable()) {
                            project->addAllocations();
                            curr_supervisor->addAllocations();
                            student->setAllocated(true);
                            Alloc *alloc = new Alloc(student->getId(), project->getId());
                            alloc->allocScore(5);
                            allocations.push_back(alloc);
                        }
                    }
                }
            }
        }
    }

    for(auto student : students){
        if(!student->isAllocated()){
            student->setAllocated(true);
            Alloc* alloc = new Alloc(student->getId(), 0);
            alloc->allocScore(5);
            allocations.push_back(alloc);
        }
    }
}

string ProjectAllocator::print() {
    sort(allocations.begin(), allocations.end(), [](const Alloc* lhs, const Alloc* rhs){
        return lhs->getStudentId() < rhs->getStudentId();
    });

    string out_string;
    int score = 0;
    for(auto alloc : allocations){
        out_string += alloc->print();
        score += alloc->getScore();
    }
    out_string += to_string(score);

    return out_string;
}

Project* ProjectAllocator::findProjectById(const int id) {
    for(auto project : projects){
        if(project->getId() == id){
            return project;
        }
    }
    return nullptr;
}

Supervisor *ProjectAllocator::findSupervisorById(const string& id) {
    for(auto supervisor : supervisors){
        if(supervisor->getId() == id){
            return supervisor;
        }
    }
    return nullptr;
}

Student *ProjectAllocator::findStudentById(const string &id) {
    for(auto student : students){
        if(student->getId() == id){
            return student;
        }
    }
    return nullptr;
}

int ProjectAllocator::countStudentAllocations(const string& studentId) {
    int out_count = 0;

    for(auto student : students){
        if(student->getId() == studentId){
            out_count++;
        }
    }

    return out_count;
}

void ProjectAllocator::validateAllocation() {

    for(auto alloc : allocations){
        Project* curr_project = findProjectById(alloc->getProjectId());

        if(curr_project != nullptr){
            Supervisor *curr_supervisor = findSupervisorById(curr_project->getSupervisorId());
            Student* curr_student = findStudentById(alloc->getStudentId());

            if (curr_supervisor != nullptr && curr_student != nullptr) {
                curr_project->addAllocations();
                curr_supervisor->addAllocations();
                curr_student->setAllocated(true);
            }
        }
    }

    for(auto alloc : allocations){
        Project* curr_project = findProjectById(alloc->getProjectId());

        if(curr_project != nullptr){
            curr_project->validateAllocation();

            Supervisor *curr_supervisor = findSupervisorById(curr_project->getSupervisorId());
            if (curr_supervisor != nullptr) {
                curr_supervisor->validateAllocation();
            }

            Student* curr_student = findStudentById(alloc->getStudentId());
            if (curr_student != nullptr){
                int no_of_student_allocations = countStudentAllocations(curr_student->getId());

                if(no_of_student_allocations > 1){
                    cout << "Student " << "\"" << curr_student->getId() << "\""
                        << " is allocated more than one project" << endl;
                }
                else if(no_of_student_allocations == 0){
                    Project* available_project = findAvailableProject(curr_student);
                    if(available_project != nullptr){
                        cout << "Student " << "\"" << curr_student->getId() << "\""
                             << " is not allocated any project but project "
                             << "\"" << available_project->getId() << "\""
                             << " is still available " << endl;
                    }
                }
                else if(no_of_student_allocations == 1){
                    validateAllocationByChoices(curr_student, curr_project);
                }
            }
        }
    }
}

Project *ProjectAllocator::findAvailableProject(Student* forStudent) {
    for(auto choice : forStudent->getChoices()){
        Project* curr_project = findProjectById(choice);

        if(curr_project != nullptr){
            if(curr_project->isAvailable()){
                return curr_project;
            }
        }
    }

    for(auto project : projects){
        if(project->isAvailable()){
            return project;
        }
    }
    return nullptr;
}

void ProjectAllocator::validateAllocationByChoices(Student *forStudent, Project *allocatedProject) {
    for(auto choice : forStudent->getChoices()){
        Project* curr_project = findProjectById(choice);

        if(curr_project != nullptr){
            if(curr_project == allocatedProject){
                return;
            }
            if(curr_project->isAvailable() && curr_project != allocatedProject){
                cout << "Student " << "\"" << forStudent->getId() << "\""
                     << " is allocated project " <<  "\"" << allocatedProject->getId() << "\""
                     << " but project " <<  "\"" << curr_project->getId() << "\""
                     << " is higher on their preference list and is available " << endl;
                return;
            }
        }
    }
}
