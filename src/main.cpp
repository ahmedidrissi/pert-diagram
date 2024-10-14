#include "task.cpp"
#include "../include/json.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using json = nlohmann::json;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

// define a recursive function to calculate the start time of a task
int calculateStart(Task* task) {
    if (task->getPredecessors().size() == 0) {
        return 0;
    } else {
        int max = 0;
        for (auto& pred : task->getPredecessors()) {
            if (calculateStart(pred) + pred->getDuration() > max) {
                max = calculateStart(pred) + pred->getDuration();
            }
        }
        return max;
    }
}

// define a recursive function to calculate the finish time of a task
int calculateFinish(Task* task) {
    if (task->getSuccessors().size() == 0) {
        return task->getStart() + task->getDuration();
    } else {
        int min = 999999;
        for (auto& succ : task->getSuccessors()) {
            if (calculateFinish(succ) - succ->getDuration() < min) {
                min = calculateFinish(succ) - succ->getDuration();
            }
        }
        return min;
    }
}
    
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

            // Add the task to the list of tasks
            tasks.push_back(newTask);
        }
    }

    // Link the tasks based on the JSON file
    for (auto& element : data["data"]) {

        // Iterate over the tasks for the given resource
        for (auto& task : element["tasks"]) {

            // Get the task object
            Task* currentTask = nullptr;
            for (auto& t : tasks) {
                if (t->getID() == task["id"]) {
                    currentTask = t;
                    break;
                }
            }

            // Iterate over the predecessors for the given task
            for (auto& pred : task["predecessors"]) {

                // Get the predecessor task object
                Task* predecessorTask = nullptr;
                for (auto& t : tasks) {
                    if (t->getID() == pred) {
                        predecessorTask = t;
                        break;
                    }
                }

                // Add the predecessor to the current task
                currentTask->addPredecessor(predecessorTask);
            }
        }
    }

    // Close the input file
    inputFile.close();

    // Add successors to the tasks
    for (auto& task : tasks) {
        for (auto& pred : task->getPredecessors()) {
            pred->addSuccessor(task);
        }
    }

    // Start time is the maximum of the start time plus duration of all predecessors
    // Start(task_i) = max(Start(task_j) + Duration(task_j)) for all task_j in Predecessors(task_i)
    for (auto& task : tasks) {
        task->setStart(calculateStart(task));
    }

    
    // Finish time is the minimum of the finish time minus duration of all successors
    // Finish(task_i) = min(Finish(task_j) - Duration(task_i)) for all task_j in Successors(task_i)
    for (auto it = tasks.rbegin(); it != tasks.rend(); ++it) {
        Task* task = *it;
        task->setFinish(calculateFinish(task));
    }

    // Print using DOT format
    std::ofstream outputFile("../output/tasks.dot");

    // Check if the file is open
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open file" << std::endl;
        return 1;
    }

    // Write the DOT file header
    outputFile << "digraph G {" << std::endl;

    // Write the tasks to the DOT file
    for (auto& task : tasks) {
        outputFile << "  " << task->getID() << " [shape=rect, style=filled, fillcolor=lightblue, label=<<table border=\"0\" cellborder=\"1\" cellspacing=\"0\"><tr><td>" << task->getID() << " (" << task->getDuration() << ")</td><td>" << task->getStart() << ", " << task->getFinish() << "</td></tr></table>>];" << std::endl;
    }

    // Write the edges to the DOT file
    for (auto& task : tasks) {
        for (auto& succ : task->getSuccessors()) {
            outputFile << "  " << task->getID() << " -> " << succ->getID() << ";" << std::endl;
        }
    }

    // Write the DOT file footer
    outputFile << "}" << std::endl;

    // Close the output file
    outputFile.close();

    // Generate the PNG file
    std::string command = "dot -Tpng ../output/tasks.dot -o ../output/tasks.png";
    system(command.c_str());

    return 0;
}
