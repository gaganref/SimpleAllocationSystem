#include <iostream>
#include <fstream>
#include <vector>
#include "AllocationSystem.h"

using std::cout;
using std::endl;
using std::fstream;
using std::ios;

int main(int argc, char* argv[]) {

    fstream file;
    vector<Supervisor*> supervisorFile;
    vector<Project*> projectFile;
    vector<Student*> studentFile;
    vector<Alloc*> allocFile;


    for (int itr = 1; itr < argc; itr++) {
        file.open(argv[itr], ios::in);
        switch (itr) {
            case 1: {
                std::string str;
                while (std::getline(file, str))
                {
                    supervisorFile.push_back(new Supervisor(str));
                }
            }
                break;
            case 2: {
                std::string str;
                while (std::getline(file, str))
                {
                    projectFile.push_back(new Project(str));
                }
            }
                break;
            case 3: {
                std::string str;
                while (std::getline(file, str))
                {
                    studentFile.push_back(new Student(str));
                }
            }
                break;
            case 4: {
                std::string str;
                while (std::getline(file, str))
                {
                    allocFile.push_back(new Alloc(str));
                }
            }
                break;

            default:
                break;
        }

        file.close();
    }

    ProjectAllocator* projectAllocator = new ProjectAllocator(supervisorFile, projectFile, studentFile, allocFile);
    projectAllocator->validateAllocation();
    delete projectAllocator;

    return 0;
}
