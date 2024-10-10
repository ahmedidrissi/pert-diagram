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

    // Print the tasks with resource "G"
    for (auto& task : tasks) {
        if (task->getResource() == "G") {
            std::cout << "Task ID: " << task->getID() << std::endl;
            std::cout << "Task Name: " << task->getName() << std::endl;
            std::cout << "Task Duration: " << task->getDuration() << std::endl;
            std::cout << "Task Resource: " << task->getResource() << std::endl;
            std::cout << "Task Predecessors: ";
            for (auto& pred : task->getPredecessors()) {
                std::cout << pred->getID() << " ";
            }
            std::cout << std::endl;
            std::cout << std::endl;
        }
    }
    return 0;
}
