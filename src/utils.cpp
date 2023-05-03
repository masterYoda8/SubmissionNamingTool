#include <string>
#include <vector>
#include <sstream>
#include <filesystem>
#include <iostream>

#include "utils.h"


static std::vector<subject> subjects;


void initSubjectVector() {
    subject ds {"ds", "DS", "3-14"};
    subjects.push_back(ds);
    subject pg2 {"pg2", "PG2", "1-14"};
    subjects.push_back(pg2);
    // add more subjects here
}

std::string createFileName(const std::string & addon) {
    
    initSubjectVector();

    // get current filepath
    const std::string filePath = static_cast<std::string>(std::filesystem::current_path());

    // search for a subject in the current filepath; exit if no subject found
    int subjectIndex = getSubjectIndex(filePath);
    std::string subjectNameInFile = subjects.at(subjectIndex).nameInFile;
    std::string groupName = subjects.at(subjectIndex).groupName; 

    // extract numbers from path
    std::string practiseNumber = extractPractiseNumber(filePath);
    std::string taskNumber = extractTaskNumber(filePath);

    // create new filename and return
    std::stringstream newFileName;
    newFileName <<  subjectNameInFile << '-' << groupName << "_U" << practiseNumber << "_" << taskNumber << addon << ".txt";
    return newFileName.str();   
}

int getSubjectIndex(const std::string & filePathRef) {

    int counter;

    for(counter = 0; counter < subjects.size(); counter++){

	std::size_t found = filePathRef.find(subjects.at(counter).nameInPath);

	if(found != std::string::npos) break;

    }

    if(counter == subjects.size()){

        std::cerr << COLOR_RED << "No subject has been found in the filepath" << COLOR_RESET << std::endl;
	std::exit(1);

    }

    return counter;
}

std::string extractPractiseNumber(const std::string & filePathRef) {

    std::size_t found = filePathRef.find(PRACTISE_STRING);

    if(found != std::string::npos){

  	return filePathRef.substr((found + PRACTISE_STRING_LENGTH), 2);	

    } else {

        std::cerr << COLOR_RED << "No practise has been found in the filepath" << COLOR_RESET << std::endl;
        std::exit(1);
	
    }  
}

std::string extractTaskNumber(const std::string & filePathRef) {
    
    std::size_t found = filePathRef.find(TASK_STRING);

    if(found != std::string::npos){
    
        return filePathRef.substr((found + TASK_STRING_LENGTH), 1);

    } else {

	std::cerr << COLOR_RED << "No task has been found in the filepath" << COLOR_RESET << std::endl;
        std::exit(1);

    }
}