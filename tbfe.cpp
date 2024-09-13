#include <cstdlib>
#include <ios>
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

int main() {
	using std::cout;
	using std::cin;
	using std::string;

	string tinput; // this will take in the commands give by the user
    	static std::filesystem::path current_path = std::filesystem::current_path(); // get the current directory
    	static std::filesystem::path previous_path = current_path; // track the previous directory	

	cout << "tbfe>" << current_path << "> ";
	cin >> tinput;

	if(tinput == "help") {
		cout << "\nhelp: shows all the command for tbfe" << '\n' << '\n' << '\n';
		cout << "ls: lists all the files and directories in the current directory" << '\n' << '\n' << '\n';
		cout << "cr: creates a file or directory" << '\n' << '\n' << '\n';
		cout << "goto: changes the directory (use .. to go back a directory and - to the previous directory you were in)" << '\n' << '\n' << '\n';
		cout << "rn: renames a file or directory" << '\n' << '\n' << '\n';
		cout << "mv: moves a file or directory to another directory" << '\n' << '\n' << '\n';
		cout << "exit: exits tbfe" << '\n' << '\n' << '\n';
		cout << "clear: clears all the output" << '\n' << '\n' << '\n';
		cout << "rm: removes a file or directory" << '\n' << '\n' << '\n';
		cout << "rd: outputs all the contents of a file" << '\n' << '\n' << '\n';
		main();
	}
	else if (tinput == "ls") {
		for (const auto& entry : std::filesystem::directory_iterator(current_path)) {
                	cout << (entry.is_directory() ? "[DIR]  " : "[FILE] ") << entry.path().filename().string() << '\n';
            	}

		main();
	}
	else if (tinput == "cr") {
		char crinput; // this will take in if the user wants to create a file or directory
		string nameOf_FOrD; // this means name of file or directory not name of ford

		cout << "Enter the what do want to create 'f' for file, 'd' for directory. Write 'e' to exit: ";
		cin >> crinput;

		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clears input buffer

		while (true) {
            		if (crinput == 'f') {
                		cout << "Enter the name of the file: ";
				std::getline(cin, nameOf_FOrD);

				std::filesystem::path file_path = current_path / nameOf_FOrD;
                		std::ofstream file(file_path);  // Create the file
                		cout << "File '" << nameOf_FOrD << "' created successfully.\n";
				break;
            		}
            		else if (crinput == 'd') {
                		cout << "Enter the name of the directory: ";
                		std::getline(cin, nameOf_FOrD);

                		std::filesystem::path dir_path = current_path / nameOf_FOrD;
                		std::filesystem::create_directory(dir_path);  // Create the directory
                		cout << "Directory '" << nameOf_FOrD << "' created successfully.\n";
				break;
            		}
            		else if (crinput == 'e') {
                		cout << "Exiting creation prompt.\n";
                		break;
            		}
            		else {
                		cout << "Error: '" << crinput << "' is not a valid command. Use 'f', 'd', or 'e'.\n";
            		}
        	}

        	main();  // Loop back to the start
	}
	else if (tinput == "clear") {
		#if defined(_WIN32)
			system("cls"); // for Windows
		#else
			system("clear"); // for Linux/MacOS
		#endif
		main();
	}
	else if (tinput == "goto") {
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clears the newline left in the input buffer
		string gtinput; // this will take in the name and change the directory accordingly

        	cout << "Enter the directory name: ";
        	std::getline(std::cin, gtinput);

        	// Check if the input is empty and handle it
        	if (gtinput.empty()) {
            		cout << "Error: No directory entered.\n";
            		main();  // Loop back to the start
            		return 0;  // Return early to prevent further execution
        	}

        	std::filesystem::path new_path;
        	if (gtinput == "..") {
            		// Go to the parent directory
            		new_path = current_path.parent_path();
        	}
        	else if (gtinput == "-") {
            		// Go to the previous directory
            		new_path = previous_path;
        	}
        	else {
            		// Go to the specified directory
            		new_path = current_path / gtinput;
        	}

        	// Check if the new path exists and is a directory
        	if (std::filesystem::exists(new_path) && std::filesystem::is_directory(new_path)) {
            		previous_path = current_path;  // Update previous path before changing
            		current_path = new_path;  // Change the current directory
            		cout << "Directory changed to: " << current_path << '\n';
        	}
        	else {
            		cout << "Error: Directory '" << gtinput << "' does not exist.\n";
        	}
        	main();
	}
	else if (tinput == "rn") {
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clears the newline left in the input buffer

		string rninput; // this will take the input and change the name of the file or directory accordingly
		string fOrD_input; // this will take the file or directory of what the user typed

		cout << "Enter a file or directory: ";
		std::getline(cin, fOrD_input);

		std::filesystem::path old_path = current_path / fOrD_input;

		if (std::filesystem::exists(old_path)) {
			cout << "Enter the new name: ";
			std::getline(cin, rninput);

			std::filesystem::path new_path = current_path / rninput;

			try {
				std::filesystem::rename(old_path, new_path);
				cout << "Renamed successfully to '" << rninput << "'\n";
			} catch (const std::filesystem::filesystem_error& e) {
				std::cerr << "Error renaming: " << e.what() << '\n';
			}
		} else {
			cout << "Error: '" << fOrD_input << "' does not exist in the current directory.\n";
		}

		main();
	}
	else if (tinput == "rm") {
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clears the newline left in the input buffer

		string rminput; // gets the file or directory given by the user

		cout << "Enter the name of the file or directory you want to remove: ";
		std::getline(cin, rminput);

		std::filesystem::path path_to_remove = current_path / rminput;

    		try {
        		if (std::filesystem::exists(path_to_remove)) {
            			if (std::filesystem::is_directory(path_to_remove)) {
                			// It's a directory; attempt to remove it and all its contents
                			std::filesystem::remove_all(path_to_remove);
                			cout << "Directory '" << rminput << "' and its contents removed successfully.\n";
            			} else {
                			// It's a file; attempt to remove it
                			std::filesystem::remove(path_to_remove);
                				cout << "File '" << rminput << "' removed successfully.\n";
            				}
        		} else {
            			cout << "Error: '" << rminput << "' does not exist in the current directory.\n";
        		}
    		}
		catch (const std::filesystem::filesystem_error& e) {
        		std::cerr << "Error removing: " << e.what() << '\n';
    		}
		main();
	}
	else if (tinput == "mv") {
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clears the newline left in the input buffer

		string nameOf_FOrD, mvinput; // mvinput will take in the path the user want there file or directory to be in 

		cout << "Enter the file or directory you want to move: ";
		std::getline(cin, nameOf_FOrD);

		std::filesystem::path source_path = current_path / nameOf_FOrD;

    		if (!std::filesystem::exists(source_path)) {
        		cout << "Error: '" << nameOf_FOrD << "' does not exist in the current directory.\n";
        		main();
        		return 0;
    		}

		cout << "Enter the path you want the file or directory you want to move it in: ";
    		std::getline(cin, mvinput);

    		std::filesystem::path destination_path = std::filesystem::path(mvinput) / nameOf_FOrD;

    		try {
        		std::filesystem::rename(source_path, destination_path);  // Move the file or directory
        		cout << "Moved '" << nameOf_FOrD << "' to '" << destination_path.string() << "' successfully.\n";
    		} catch (const std::filesystem::filesystem_error& e) {
        		std::cerr << "Error moving: " << e.what() << '\n';
    		}
		main();
	}
	else if (tinput == "rd") {
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clears the newline left in the input buffer

		string rdinput, rdcontent; // rdinput takes in the file user inputed. rdcontent will take in the contents of rdFile
		std::fstream rdFile;

		cout << "Enter the name of the file you want to read: ";
		std::getline(cin, rdinput);

		rdFile.open(rdinput, std::ios::in); // this takes in the input of the user aka takes in the contents of rdinput

		if (rdFile.is_open()) {
			while (std::getline(rdFile, rdcontent)) {
				cout << rdcontent << '\n';
			}
			rdFile.close();
		}
		else {
			cout << "Error: \"" << rdinput << "\" does not exist in the current directory\n";
			main();
		}
		main();
	}
	else if (tinput == "exit") {
		cout << "Exiting tbfe\n";
		return 0;
	}
	else{
		cout << "Error: \"" << tinput << "\" is not a command in tbfe. To see all the commands in tbfe, write \"help\"\n";
		main();
		}
	return 0;
}
