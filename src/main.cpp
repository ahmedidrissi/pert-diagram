#include "task.cpp"
#include "../include/json.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using json = nlohmann::json;

int main() {
    // Create a list of tasks
    std::vector<Task*> tasks;

    // Read tasks from JSON file
    std::ifstream inputFile("../data/tasks.json");

    // Check if the file is open
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file" << std::endl;
        return 1;
    }

    // Parse the JSON file
    json data;
    inputFile >> data;

    // Iterate over the tasks in the JSON file
    for (auto& element : data["data"]) {

        // Get the resource name
        std::string resource = element["resource"];

        // Iterate over the tasks for the given resource
        for (auto& task : element["tasks"]) {

            // Create a new task object
            Task* newTask = new Task(task["id"], task["name"], task["duration"], resource);

            // Add predecessors to the task
            std::vector<std::string> predecessors = task["predecessors"];
            for (auto& pred : predecessors) {
                Task* predecessor = nullptr;
                for (auto& t : tasks) {
                    if (t->getID() == pred) {
                        predecessor = t;
                        break;
                    }
                }
                if (predecessor != nullptr) {
                    newTask->addPredecessor(predecessor);
                }
            }

            // Add the task to the list of tasks
            tasks.push_back(newTask);
        }
    }

    // Add successors to the tasks
    for (auto& task : tasks) {
        for (auto& pred : task->getPredecessors()) {
            pred->addSuccessor(task);
        }
    }

    // Start time is the maximum of the start time plus duration of all predecessors
    // Start(task_i) = max(Start(task_j) + Duration(task_j)) for all task_j in Predecessors(task_i)
    for (auto& task : tasks) {
        if (task->getPredecessors().size() == 0) {
            task->setStart(0);
        } else {
            int max = 0;
            for (auto& pred : task->getPredecessors()) {
                if (pred->getStart() + pred->getDuration() > max) {
                    max = pred->getStart() + pred->getDuration();
                }
            }
            task->setStart(max);
        }
    }
    
    // Finish time is the minimum of the finish time minus duration of all successors
    // Finish(task_i) = min(Finish(task_j) - Duration(task_i)) for all task_j in Successors(task_i)
    for (auto it = tasks.rbegin(); it != tasks.rend(); ++it) {
        Task* task = *it;
        if (task->getSuccessors().size() == 0) {
            task->setFinish(task->getStart() + task->getDuration());
        } else {
            int min = 999999;
            for (auto& succ : task->getSuccessors()) {
                if (succ->getFinish() - succ->getDuration() < min) {
                    min = succ->getFinish() - succ->getDuration();
                }
            }
            task->setFinish(min);
        }
    }

    // Print the tasks
    for (auto& task : tasks) {
        task->printTask();
    }

    return 0;
}
