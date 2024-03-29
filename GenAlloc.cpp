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
        switch (itr) {
            case 1: {
                file.open(argv[itr], ios::in);

                std::string str;
                while (std::getline(file, str))
                {
                    supervisorFile.push_back(new Supervisor(str));
                }

                file.close();
            }
                break;
            case 2: {
                file.open(argv[itr], ios::in);

                std::string str;
                while (std::getline(file, str))
                {
                    projectFile.push_back(new Project(str));
                }

                file.close();
            }
                break;
            case 3: {
                file.open(argv[itr], ios::in);

                std::string str;
                while (std::getline(file, str))
                {
                    studentFile.push_back(new Student(str));
                }

                file.close();
            }
                break;
            case 4: {
                file.open(argv[itr], ios::in | ios::out | ios::trunc);

                ProjectAllocator* projectAllocator = new ProjectAllocator(supervisorFile, projectFile, studentFile, allocFile);
                projectAllocator->allocateProject();
                string out_string = projectAllocator->print();

                file << out_string;

                file.close();
                delete projectAllocator;
            }
                break;

            default:
                break;
        }
    }


    return 0;
}
