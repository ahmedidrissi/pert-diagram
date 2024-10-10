#include "task.h"
#include <iostream>

Task::Task(std::string ID, std::string name, int duration, std::string resource) {
    this->ID = ID;
    this->name = name;
    this->duration = duration;
    this->resource = resource;
}

Task::~Task() {
    // Destructor
}


std::string Task::getID() {
    return ID;
}

void Task::setID(std::string ID) {
    this->ID = ID;
}


std::string Task::getName() {
    return name;
}

void Task::setName(std::string name) {
    this->name = name;
}


int Task::getDuration() {
    return duration;
}

void Task::setDuration(int duration) {
    this->duration = duration;
}


int Task::getStart() {
    return start;
}

void Task::setStart(int start) {
    this->start = start;
}

int Task::getFinish() {
    return finish;
}

void Task::setFinish(int finish) {
    this->finish = finish;
}


std::string Task::getResource() {
    return resource;
}

void Task::setResource(std::string resource) {
    this->resource = resource;
}


std::vector<Task*> Task::getPredecessors() {
    return predecessors;
}

void Task::addPredecessor(Task* task) {
    predecessors.push_back(task);
}

void Task::removePredecessor(Task* task) {
    for (int i = 0; i < predecessors.size(); i++) {
        if (predecessors[i] == task) {
            predecessors.erase(predecessors.begin() + i);
            break;
        }
    }
}


std::vector<Task*> Task::getSuccessors() {
    return successors;
}

void Task::addSuccessor(Task* task) {
    successors.push_back(task);
}

void Task::removeSuccessor(Task* task) {
    for (int i = 0; i < successors.size(); i++) {
        if (successors[i] == task) {
            successors.erase(successors.begin() + i);
            break;
        }
    }
}


void Task::printTask() {
    std::cout << "ID: " << ID << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Duration: " << duration << std::endl;
    std::cout << "Start: " << start << std::endl;
    std::cout << "Finish: " << finish << std::endl;
    std::cout << "Resource: " << resource << std::endl;
    std::cout << "Predecessors: ";
    for (int i = 0; i < predecessors.size(); i++) {
        std::cout << predecessors[i]->getID() << " ";
    }
    std::cout << std::endl;
    std::cout << "Successors: ";
    for (int i = 0; i < successors.size(); i++) {
        std::cout << successors[i]->getID() << " ";
    }
    std::cout << std::endl;
}
