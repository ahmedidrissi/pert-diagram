// Purpose: Header file for Task class

#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>

class Task {
/*
 * Task class represents a task in the project.
 * 
 * Attributes:
 * - ID: unique identifier of the task
 * - name: name of the task
 * - duration: duration of the task in days
 * - start: start time of the task in days
 * - finish: finish time of the task in days
 * - predecessors: list of tasks that need to be completed before this task can start
 * - successors: list of tasks that depend on this task
 * - resource: name of the resource assigned to the task
 * 
 * Methods:
 * - constructor: creates a new task with the given ID, name, duration, and resource
 * - destructor: destroys the task
 * - getID: returns the ID of the task
 * - getName: returns the name of the task
 * - getDuration: returns the duration of the task
 * - getStart: returns the start time of the task
 * - getFinish: returns the finish time of the task
 * - getPredecessors: returns the list of predecessors of the task
 * - getSuccessors: returns the list of successors of the task
 * - getResource: returns the resource assigned to the task
 * - setStart: sets the start time of the task
 * - setFinish: sets the finish time of the task
 * - addPredecessor: adds a task to the list of predecessors
 * - addSuccessor: adds a task to the list of successors
 * - removePredecessor: removes a task from the list of predecessors
 * - removeSuccessor: removes a task from the list of successors
 * - printTask: prints the details of the task
 */

private:
    int ID;
    std::string name;
    int duration;
    int start;
    int finish;
    std::vector<Task*> predecessors;
    std::vector<Task*> successors;
    std::string resource;

public:
    Task(int ID, std::string name, int duration, std::string resource); // constructor
    ~Task(); // destructor

    int getID();
    std::string getName();
    int getDuration();
    int getStart();
    int getFinish();
    std::vector<Task*> getPredecessors();
    std::vector<Task*> getSuccessors();
    std::string getResource();

    void setStart(int start);
    void setFinish(int finish);
    void addPredecessor(Task* task);
    void addSuccessor(Task* task);
    void removePredecessor(Task* task);
    void removeSuccessor(Task* task);

    void printTask();    
};

#endif