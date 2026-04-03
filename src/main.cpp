#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <vector>


class generic {
public:
    struct {
        // help template NAME\nPARAMETERS {e}\nDdescription\n\n optionally additional info after description but ensure double \n at end ADDITIONAL INFORMATION
    } help1;

    struct {

    } help2;

    void fileManage() {
        while (true)
        {
            std::string command;
            std::cout << "* ";
            std::cin >> command;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (command == "new") {
                std::string newPath;
                char choice;

                std::cout << "Enter your new path\n";
                std::getline(std::cin, newPath);

                if (std::filesystem::exists(newPath)) {
                    std::cout << "File already exists, this will cause undefined behavior. Are you sure you wish to continue? (Y/N) \n"; // I broke this somehow
                    std::cin >> choice;
                    choice = tolower(choice); // I don't think two static_casts is necessary here

                    if (choice == 'y') {
                        std::ofstream createFile(newPath);
                        if (createFile.is_open()) {
                            std::cout << "Successfully created file at " << newPath << '\n';
                            createFile.close();
                        }

                        else {
                            std::cout << "Failed to create file\n";
                        }
                    }

                    else if (choice == 'n') {
                        std::cout << "Cancelled creation\n";
                    }

                    else {
                        std::cout << "Invalid response, creation cancelled\n";
                    }
                }
            }

            else if (command == "delete") {
                std::string delpath;
                char areYouSureAboutThat;
                std::getline(std::cin, delpath);

                if (std::filesystem::exists(delpath)) {
                    std::cout << "Are you sure you would like to delete " << delpath << " (Y/N)\n";
                    std::cin >> areYouSureAboutThat;
                    areYouSureAboutThat = tolower(areYouSureAboutThat);

                    if (areYouSureAboutThat == 'y') {
                        if (std::filesystem::remove(delpath)) {
                            std::cout << "Sucessfully removed " << delpath << '\n';
                        }

                        else {
                            std::cout << "Failed to remove " << delpath << " or file did not exist\n";
                        }
                    }

                    else if (areYouSureAboutThat == 'n') {
                        std::cout << "Deletion canceled\n";
                    }

                    else {
                        std::cout << "Invalid response, cancelled\n";
                    }
                }
            }

            else if (command == "copy") {
                std::string path;
                std::string targetPath;

                std::cout << "Enter a path for your new file\n";
                getline(std::cin, path);
                if (std::filesystem::exists(path)) {
                    if (std::filesystem::is_regular_file(path)) {
                        std::cout << "Enter a target path";
                        std::getline(std::cin, targetPath);
                        std::filesystem::copy(path, targetPath);

                        if (std::filesystem::exists(targetPath)) {
                            std::cout << "Sucessfully copied file\n";
                        }

                        else {
                            std::cout << "Failed to copy file\n";
                        }
                    }

                    else {
                        std::cout << "Not a valid file\n";
                    }
                }

                else {
                    std::cout << "Unable to locate file\n";
                }
            }

            else if (command == "cut") {
                std::string cutFile;
                std::string cutFileTarget;
                char choice;

                std::cout << "Enter the path of the file you wish to move\n";
                std::getline(std::cin, cutFile);

                if (std::filesystem::exists(cutFile) && std::filesystem::is_regular_file(cutFile)) {
                    std::cout << "Enter the target path\n";
                    std::getline(std::cin, cutFileTarget);

                    if (!std::filesystem::exists(cutFileTarget)) {
                    bandaid_fix:
                        std::cout << "Continuing may cause undefined behavior, are you sure you wish to continue?\n";
                        std::cin >> choice;
                        choice = tolower(choice);

                        if (choice == 'y') {
                            std::filesystem::copy(cutFile, cutFileTarget);

                            if (std::filesystem::exists(cutFileTarget)) {
                                std::cout << "Successfully copied " << cutFile << " to " << cutFileTarget << '\n';
                                if (!std::filesystem::remove(cutFile)) {
                                    std::cout << "Failed to remove original file at " << cutFile << '\n';
                                }
                            }

                            else {
                                std::cout << "Failed to copy\n";
                            }
                        }

                        else if (choice == 'n') {
                            std::cout << "Cancelled operation\n";
                        }

                        else {
                            std::cout << "Invalid response\nCancelled operation\n";
                        }
                    }
                    else {
                        goto bandaid_fix;
                    }
                }

                else {
                    std::cout << "Invalid file\n";
                }
            }

            else if (command == "read") {
                std::string readPath;

                std::cout << "Enter the path\n";
                std::getline(std::cin, readPath);

                if (std::filesystem::exists(readPath) && std::filesystem::is_regular_file(readPath)) {
                    std::ifstream readFile(readPath);

                    if (readFile.is_open()) {
                        std::string line;

                        while (std::getline(readFile, line)) {
                            std::cout << line << '\n';
                        }
                    }
                    else {
                        std::cout << "Failed to read file\n";
                    }
                }

                else {
                    std::cout << "Invalid file\n";
                }
            }

            else if (command == "view") {
                std::string viewPath; // TBD
            }

            else if (command == "write") {
                std::string writeFile;
                std::string reportText;

                if (std::filesystem::exists(writeFile)) {
                    std::string writeText;

                    std::ofstream write(writeFile);
                    if (write.is_open()) {
                        std::getline(std::cin, writeText);
                        write << writeText;
                        write.close();

                        if (writeText.length() < 50) {
                            for (int i = 0; i < writeText.length(); i++) {
                                reportText += writeText[i];
                            }

                            std::cout << "Wrote " << reportText << " (" << writeText.length() - reportText.length() << " excluded)" << " to " << writeFile;
                        }

                        else {
                            std::cout << "Wrote " << writeText << " to " << writeFile;
                        }
                    }

                    else {
                        std::cout << "Failed to create file\n";
                    }
                }

                else {
                    std::cout << "File does not exist\n";
                }

            }

            else if (command == "check") {
                std::string checkFile;

                std::getline(std::cin, checkFile);

                if (std::filesystem::exists(checkFile)) {
                    std::cout << checkFile << " exists\n";
                }

                else {
                    std::cout << checkFile << " does not exist\n";
                }
            }

            else if (command == "list") {
                std::string pathList;

                std::getline(std::cin, pathList);
                if (std::filesystem::is_directory(pathList)) {
                    for (const auto& file : std::filesystem::directory_iterator(pathList)) {
                        std::cout << file << '\n';
                    }
                }

                else {
                    std::cout << "Not a directory\n";
                }
            }

            else if (command == "exit") {
                break;
            }

            else {
                std::cout << "Invalid syntax\n";
            }
        }
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// can never see the split otherwise
    void letterFrequency() {
        std::string user_input;
        std::string txt;
        std::string letterfreqfile;
        int amount;
        char alphabet[] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m',
                           'n','o','p','q','r','s','t','u','v','w','x','y','z' };
        std::vector<int> frequency;

        std::cout << "*****************" << '\n';
        std::cout << "Letter Frequency Detector" << '\n';
        std::cout << "Enter your message" << '\n';

        getline(std::cin, user_input);

        std::transform(user_input.begin(), user_input.end(), user_input.begin(),
            [](unsigned char c) { return std::tolower(c); });

        for (int i = 0; i < sizeof(alphabet) / sizeof(char); i++) {
            amount = 0;

            for (int j = 0; j < user_input.length(); j++) {
                if (user_input[j] == alphabet[i]) {
                    amount += 1;
                }
            }

            std::cout << alphabet[i] << ": " << amount << '\n';
            frequency.push_back(amount);
        }
        std::cout << "Do you wish to save this to a text file? (y/n)\n";
        std::cin >> txt;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::transform(txt.begin(), txt.end(), txt.begin(), [](unsigned char c) { return std::tolower(c); });
        if (txt == "y") {
            char* userProfile = nullptr;
            size_t len = 0;
            if (_dupenv_s(&userProfile, &len, "USERPROFILE") == 0 && userProfile != nullptr) {
                std::cout << "Enter a name for your file\n";
                std::getline(std::cin, letterfreqfile);
                std::string path = std::string(userProfile) + "\\Downloads\\frequency_" + letterfreqfile + ".txt";
                std::ofstream file(path);

                if (!file) {
                    std::cerr << "couldn't create file";
                    free(userProfile);
                }

                else {
                    for (int i = 0; i < 26; i++) {
                        file << alphabet[i] << ": " << frequency[i] << std::endl;
                    }
                    std::cout << path << '\n';

                    file.close();
                    free(userProfile);
                }
            }
        }

        else {
            std::cerr << "bye";
        }
    }

    void bubbleSort() {
        int temp;

        std::vector<int> array; // array but vector

        while (true) {
            std::cout << "Enter your numbers (0 for exit)\n";
            std::cin >> temp;
            if (temp != 0) {
                array.push_back(temp);
            }

            else {
                break;
            }

        }

        temp = 0;

        for (int i = 0; i < sizeof(array) / sizeof(int); i++) {
            for (int j = 0; j < sizeof(array) / sizeof(int) - 1; j++) {
                if (array[j] > array[j + 1]) {
                    temp = array[j + 1];
                    array[j + 1] = array[j];
                    array[j] = temp;
                }
            }
        }

        for (int number : array) {
            std::cout << number << std::endl;
        }
    }

    int random() {
        int max;
        int min;

        srand(static_cast<unsigned int>(time(nullptr)));
        std::cout << "Enter the maximum number\n";
        std::cin >> max;
        std::cout << "Enter the minimum number\n";
        std::cin >> min;

        return rand() % (max - min + 1) + min;
    }

    void run() {
        std::string choice;

        while (true) {
            std::cout << "> ";
            std::getline(std::cin, choice);
            std::transform(choice.begin(), choice.end(), choice.begin(), [](unsigned char c) { return std::tolower(c); });

            if (choice == "bubble") {
                bubbleSort();
            }

            else if (choice == "letterfreq") {
                letterFrequency();
            }

            else if (choice == "help") {
                std::cout << "no help for you yet\n";
            }

            else if (choice == "txt") {
                std::string text;
                std::string textReport;
                std::string fileName;
                std::string formatted;

                text.clear();
                textReport.clear();
                std::cout << "Enter the name for your txt\n";
                std::getline(std::cin, fileName);
                std::cin.clear();
                std::ofstream File(fileName + ".txt");
                std::cout << "Enter your text\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, text);

                for (size_t i = 0; i < text.length(); i++) {
                    formatted += text[i];
                    if ((i + 1) % 90 == 0) formatted += '\n';
                }
                text = formatted;

                File << text;

                if (text.length() > 50) {
                    for (int i = 0; i < 50; i++) {
                        textReport += text[i];
                    }

                    std::cout << fileName << " created at " << fileName + ".txt" << " with text " << textReport << " (" << text.length() - textReport.length() << " excluded)";
                }
                 
                else {
                    std::cout << fileName << " created at " << fileName + ".txt" << "with text" << text;
                }

                File.close();
            }

            else if (choice == "random") {
                std::cout << random() << '\n';
            }

            else if (choice == "clear") {
                std::system("cls");
            }

            else if (choice == "file") {
                std::cout << "Type exit to exit file management mode\n";
                fileManage();
            }

            else if (choice == "exit") {
                break;
            }

            else {
                std::cout << "Invalid command, type help for a list\n";
            }
        }
    }
};

int main() {
    std::cout << "C++ Utilities\n";
    std::cout << "==============================\n";
    generic main;
    main.run();
    std::cout << "==============================\n";
    return 0;
}
