#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>

/**
 * @class Task
 * @brief Task class represents a task in a project.
 * 
 * Each task has a unique identifier, name, duration, start and finish time, predecessors, successors, and resource.
 */
class Task {

private:
    std::string ID;
    std::string name;
    int duration;
    int start;
    int finish;
    std::vector<Task*> predecessors;
    std::vector<Task*> successors;
    std::string resource;

public:
    /**
     * @brief Construct a new Task object
     * 
     * @param ID Task ID
     * @param name Task name
     * @param duration Task duration
     * @param resource Task resource
     */
    Task(std::string ID, std::string name, int duration, std::string resource);

    /**
     * @brief Destroy the Task object
     */
    ~Task();

    /**
     * @brief Get the ID of the task
     * 
     * @return std::string Task ID
     */
    std::string getID();

    /**
     * @brief Get the name of the task
     * 
     * @return std::string Task name
     */
    std::string getName();

    /**
     * @brief Get the duration of the task in days
     * 
     * @return int Task duration
     */
    int getDuration();

    /**
     * @brief Get the start time of the task in days
     * 
     * @return int Task start time
     */
    int getStart();

    /**
     * @brief Get the finish time of the task in days
     * 
     * @return int Task finish time
     */
    int getFinish();

    /**
     * @brief Get the predecessors of the task
     * 
     * @return std::vector<Task*> Predecessors of the task
     */
    std::vector<Task*> getPredecessors();

    /**
     * @brief Get the successors of the task
     * 
     * @return std::vector<Task*> Successors of the task
     */
    std::vector<Task*> getSuccessors();

    /**
     * @brief Get the resource of the task
     * 
     * @return std::string Task resource
     */
    std::string getResource();

    /**
     * @brief Set the ID of the task
     * 
     * @param ID Task ID
     */
    void setID(std::string ID);

    /**
     * @brief Set the name of the task
     * 
     * @param name Task name
     */
    void setName(std::string name);

    /**
     * @brief Set the duration of the task in days
     * 
     * @param duration Task duration
     */
    void setDuration(int duration);

    /**
     * @brief Set the start time of the task in days
     * 
     * @param start Task start time
     */
    void setStart(int start);

    /**
     * @brief Set the finish time of the task in days
     * 
     * @param finish Task finish time
     */
    void setFinish(int finish);

    /**
     * @brief Set the resource of the task
     * 
     * @param resource Task resource
     */
    void addPredecessor(Task* task);

    /**
     * @brief Add a successor to the task
     * 
     * @param task Task successor
     */
    void addSuccessor(Task* task);

    /**
     * @brief Remove a predecessor from the task
     * 
     * @param task Task predecessor
     */
    void removePredecessor(Task* task);

    /**
     * @brief Remove a successor from the task
     * 
     * @param task Task successor
     */
    void removeSuccessor(Task* task);

    /**
     * @brief Print the task details
     */
    void printTask();
};

#endif