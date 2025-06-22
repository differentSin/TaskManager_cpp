#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // For std::find_if

class Task { // Class to represent a task
private:	
	int id{};
	std::string description;
	std::string priority;
	bool completed;
	
public: // Default constructor
		Task(int id = 0, std::string description = "", std::string priority = "Low", bool completed = false)
			: id(id), description(description), priority(priority), completed(completed)
		{
		} // Empty body

		// Getters
		int getId() const { return id; }
		std::string getDescription() const { return description; }
		std::string getPriority() const { return priority; }
		bool isCompleted() const { return completed; }

		// Setters
		void setId(int newId) { this->id = newId; }
		void setDescription(const std::string& newDescription) { this->description = newDescription; }
		void setPriority(const std::string& newPriority) { this->priority = newPriority; }
		void complete(bool isCompleted) { this->completed = isCompleted; }
};


std::vector <Task> listOfTasks; // Global vector to hold tasks

void showMenu() {
	std::cout << "\nMenu:\n";
	std::cout << "1. Add Task\n";
	std::cout << "2. View Tasks\n";
	std::cout << "3. Complete Task\n";
	std::cout << "4. Delete Task\n";
	std::cout << "5. Exit\n";
}

void addTask() {
	std::string description, priority;
	bool completed = false;

	std::cout << "Enter task description: ";
	std::getline(std::cin, description);

	std::cout << "Enter task priority (Low, Medium, High): ";
	std::getline(std::cin, priority);

	std::cout << "Completed? (0 for No, 1 for Yes): ";
	std::cin >> completed;

	std::cin.ignore(); // Clear the newline character from the input buffer

	int id = static_cast<int>(listOfTasks.size()) + 1; // Safely cast size_t to int

	switch (completed) {
		case 0:
			listOfTasks.push_back(Task(id, description, priority, false));
			break;
		case 1:
			listOfTasks.push_back(Task(id, description, priority, true));
			break;
	}

}


void viewTasks() {
	if (listOfTasks.empty()) {
		std::cout << "No tasks available.\n";
		return;
	}
	std::cout << "\nTasks:\n";
	for (const auto& task : listOfTasks) { // Use range-based for loop to iterate through tasks
		std::cout << "ID: " << task.getId() << ", Description: " << task.getDescription() 
				  << ", Priority: " << task.getPriority() 
				  << ", Completed: " << (task.isCompleted() ? "Yes" : "No") << "\n";
	}
}

void completeTask() {
	int id;
	std::cout << "Enter task ID to mark as completed: ";
	viewTasks();

	std::cin >> id;
	std::cin.ignore(); // Clear the newline character from the input buffer
	for (auto& task : listOfTasks) {
		if (task.getId() == id) {
			task.complete(true);
			std::cout << "Task " << task.getId() << " marked as completed.\n";
			return;
		}
	}
	std::cout << "Task with ID " << id << " not found.\n";
}

void deleteTask() {
	int id_to_delete;
	std::cout << "Enter task ID to delete: ";
	viewTasks(); // Show tasks so the user knows which ID to enter
	std::cin >> id_to_delete;
	std::cin.ignore(); // Clear the newline character

	// Use std::find to get an iterator to the task with the matching ID
	auto it = std::find_if(listOfTasks.begin(), listOfTasks.end(),
						   [id_to_delete](const Task& task) {
							   return task.getId() == id_to_delete;
						   });

	// Check if the task was found
	if (it != listOfTasks.end()) {
		listOfTasks.erase(it); // Erase the element pointed to by 'it'
		std::cout << "Task " << id_to_delete << " deleted.\n";

		// IMPORTANT: Re-assign IDs after deletion to keep them sequential
		// This is optional but good if you want IDs to be always 1, 2, 3...
		// If IDs are just unique identifiers, you might not need to re-assign
		int current_id = 1;
		for (auto& task : listOfTasks) {
			task.setId(current_id++);
		}

	}
	else {
		std::cout << "Task with ID " << id_to_delete << " not found.\n";
	}
}

int main() {
	showMenu();
	int choice{};
	while (true) {
		std::cout << "Enter your choice: ";
		std::cin >> choice;
		std::cin.ignore(); // Clear the newline character from the input buffer
		switch (choice) {
			case 1:
				addTask();
				break;
			case 2:
				viewTasks();
				break;
			case 3:
				completeTask();
				break;
			case 4:
				deleteTask();
				break;
			case 5:
				std::cout << "Exiting...\n";
				return 0; // Exit the program
			default:
				std::cout << "Invalid choice. Please try again.\n";
		}
		showMenu(); // Show the menu again after each operation
	}
	
	return 0;
	

}
