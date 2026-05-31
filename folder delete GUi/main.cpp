#include<iostream>
#include<string>
#include<Windows.h>
#include <cstdint>
#include <cstdio>
#include <memory>
#include <array>
void kill_process(uint32_t pid_uint){
    DWORD pid = pid_uint;
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
    if (hProcess) {
        TerminateProcess(hProcess, 0);
        CloseHandle(hProcess);
}
}


std::string executeWindowsCommand(const std::string& cmd) {
    std::string result;
    std::array<char, 128> buffer;


    FILE* pipe = _popen(cmd.c_str(), "r");
    if (!pipe) {
        return "Ошибка: Не удалось запустить команду.";
    }


    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }


    int returnCode = _pclose(pipe);

    return result;
}




std::string return_pid(std::string location)
{
	std::string command = "handle " + location;
	std::string line = executeWindowsCommand(command.c_str());
        std::string target = "pid:";
    size_t pos = line.find(target);

    if (pos != std::string::npos) {
      
        pos += target.length();

        while (pos < line.length() && line[pos] == ' ') {
            pos++;
        }

        size_t end_pos = line.find(' ', pos);
        std::string pid_str = line.substr(pos, end_pos - pos);
        uint32_t pid = std::stoul(pid_str);
        return pid_str;
    }
    else {
        return"NO FOUND";
    }
}


int main() {
	std::string input {};
    std::cout << "enter the file path: ";
	std::cin >> input;
    uint32_t x = std::stoul(return_pid(input));
    std::cout << "pid: " << x;
    /*УБИЦСТВО ПРОЦЕСА!!!!*/
    kill_process(x);
    //!!!!!!!!!!!!!!!!!!!!!!!
    Sleep(5000);
    //if (return_pid(input) != UINT32_MAX) {
    //    std::cout << "pid = ", return_pid(input);
    //}
    //else {
    //    std::cout << "error or object not found";
    //}
}
