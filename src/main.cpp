#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <filesystem>

class app {
    public:
        struct {
            // help template NAME\nPARAMETERS {e}\nDdescription\n\n optionally additional info after description but ensure double \n at end ADDITIONAL INFORMATION
        } help1;

        struct {

        } help2;

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
            bool inputting = true;

            std::vector<int> array; // array but vector

            while (inputting) {
                std::cout << "Enter your numbers (0 for exit)\n";
                std::cin >> temp;
                if (temp != 0) {
                    array.push_back(temp);
                }

                else {
                    break;
                    inputting = false; // I think break works in while loops
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
            int random = 0;
            int max;
            int min;

            srand(time(nullptr));
            std::cout << "Enter the maximum number\n";
            std::cin >> max;
            std::cout << "Enter the minimum number\n";
            std::cin >> min;

            return rand() % (max - min + 1) + min;
        }

        void run() {
            std::string choice;
            bool running = true;

            while (running) {
                std::cout << "Enter a command (help for list)\n";
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

                else if (choice == "new") {
                    std::string newfilename;

                    std::getline(std::cin, newfilename);
                    std::ofstream newFile(newfilename);
                    if (newFile.is_open()) {
                        std::cout << "File created at" << newfilename;
                        newFile.close();
                    }

                    else {
                        std::cout << "Failed to create file at " << newfilename << "\n";
                    }
                }

                else if (choice == "write") {
                    std::string writePath;
                    std::string text;
                    std::string formatted;

                    std::getline(std::cin, writePath);

                    std::ofstream writeFile(writePath);
                    std::cout << "Enter your text\n";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::getline(std::cin, text);
                    for (size_t i = 0; i < text.length(); i++) {
                        formatted += text[i];
                        if ((i + 1) % 90 == 0) formatted += '\n';
                    }
                    writeFile << formatted;
                }

                else if (choice == "read") {
                    std::string readFilename;

                    std::getline(std::cin, readFilename);
                    if (std::filesystem::exists(readFilename) && std::filesystem::is_regular_file(readFilename)) {
                        std::string line;
                        std::ifstream readFile(readFilename);

                        if (!readFile.is_open()) {
                            std::cout << "Can't open file\n";
                        }

                        else {
                            while (std::getline(readFile, line)) {
                                std::cout << line << '\n';
                            }
                            readFile.close();
                        }
                    }
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

                else if (choice == "list") {
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

                else if (choice == "random") {
                    std::cout << random() << '\n';
                }

                else if (choice == "clear") {
                    std::system("cls");
                }

                else if (choice == "delete") {
                    std::string delpath;

                    std::cout << "Enter the path to the file you wish to delete\n";
                    std::cin >> delpath;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::filesystem::remove(delpath);
                }

                else if (choice == "exit") {
                    running = false;
                }

                else {
                    std::cout << "Invalid command\n";
                }
            }
        }
};

int main() {
	app main;
	main.run();
    return 0;
}
