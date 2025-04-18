#include <windows.h>
#include <string>
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>
#include<algorithm>


std::string getBestMoveFromStockfish(const std::string& uciPosition, int depth = 10) {
    SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
    HANDLE hChildStd_OUT_Rd = NULL;
    HANDLE hChildStd_OUT_Wr = NULL;
    HANDLE hChildStd_IN_Rd = NULL;
    HANDLE hChildStd_IN_Wr = NULL;

    // Create pipes for STDOUT
    if (!CreatePipe(&hChildStd_OUT_Rd, &hChildStd_OUT_Wr, &sa, 0))
        return "pipe failed (out)";
    if (!SetHandleInformation(hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0))
        return "sethandle failed (out)";

    // Create pipes for STDIN
    if (!CreatePipe(&hChildStd_IN_Rd, &hChildStd_IN_Wr, &sa, 0))
        return "pipe failed (in)";
    if (!SetHandleInformation(hChildStd_IN_Wr, HANDLE_FLAG_INHERIT, 0))
        return "sethandle failed (in)";

    PROCESS_INFORMATION pi;
    STARTUPINFOA si = { sizeof(STARTUPINFOA) };
    si.dwFlags |= STARTF_USESTDHANDLES;
    si.hStdOutput = hChildStd_OUT_Wr;
    si.hStdError = hChildStd_OUT_Wr;
    si.hStdInput = hChildStd_IN_Rd;

    // Start the Stockfish process
    if (!CreateProcessA(
            "stockfish.exe", NULL, NULL, NULL, TRUE,
            CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
        return "failed to start stockfish";
    }

    // Prepare UCI commands
    std::string commands =
        "uci\n"
        "isready\n" +
        uciPosition + "\n" +
        "go depth " + std::to_string(depth) + "\n";
    std::cout<<"uci sent to sf: "<<uciPosition<<std::endl;
    // Write commands to Stockfish's stdin
    DWORD written;
    WriteFile(hChildStd_IN_Wr, commands.c_str(), commands.length(), &written, NULL);
    FlushFileBuffers(hChildStd_IN_Wr); // ensure all data is sent

    // Read output
    std::string output;
    CHAR buffer[4096];
    DWORD bytesRead;
    bool gotBestMove = false;

    while (!gotBestMove && ReadFile(hChildStd_OUT_Rd, buffer, sizeof(buffer) - 1, &bytesRead, NULL)) {
        buffer[bytesRead] = '\0';
        output += buffer;

        if (output.find("bestmove") != std::string::npos) {
            gotBestMove = true;
            break;
        }
    }

    // Extract bestmove
    std::istringstream iss(output);
    std::string line, bestMove;
    while (std::getline(iss, line)) {
        if (line.rfind("bestmove", 0) == 0) {
            std::istringstream lss(line);
            std::string token;
            lss >> token >> bestMove;
            break;
        }
    }

    // Cleanup
    CloseHandle(hChildStd_OUT_Rd);
    CloseHandle(hChildStd_OUT_Wr);
    CloseHandle(hChildStd_IN_Rd);
    CloseHandle(hChildStd_IN_Wr);
    TerminateProcess(pi.hProcess, 0);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return bestMove;
}
bool getCheckStatusFromStockfish(const std::string& uciPosition) {
    SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
    HANDLE hChildStd_OUT_Rd = NULL, hChildStd_OUT_Wr = NULL;
    HANDLE hChildStd_IN_Rd = NULL, hChildStd_IN_Wr = NULL;

    if (!CreatePipe(&hChildStd_OUT_Rd, &hChildStd_OUT_Wr, &sa, 0)) return false;
    if (!SetHandleInformation(hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0)) return false;
    if (!CreatePipe(&hChildStd_IN_Rd, &hChildStd_IN_Wr, &sa, 0)) return false;
    if (!SetHandleInformation(hChildStd_IN_Wr, HANDLE_FLAG_INHERIT, 0)) return false;

    PROCESS_INFORMATION pi;
    STARTUPINFOA si = { sizeof(STARTUPINFOA) };
    si.dwFlags |= STARTF_USESTDHANDLES;
    si.hStdOutput = hChildStd_OUT_Wr;
    si.hStdError = hChildStd_OUT_Wr;
    si.hStdInput = hChildStd_IN_Rd;

    if (!CreateProcessA("stockfish.exe", NULL, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
        return false;
    }

    auto sendCommand = [&](const std::string& cmd) {
        DWORD written;
        WriteFile(hChildStd_IN_Wr, cmd.c_str(), cmd.size(), &written, NULL);
        WriteFile(hChildStd_IN_Wr, "\n", 1, &written, NULL);
        FlushFileBuffers(hChildStd_IN_Wr);
    };

    // Send initialization + position + 'd' command
    sendCommand("uci");
    sendCommand("isready");
    sendCommand(uciPosition); // already in "position startpos moves e2e4 ..." format
    sendCommand("d"); // gives internal board state

    // Wait for 'readyok' to be sure Stockfish is ready
    std::string output;
    CHAR buffer[4096];
    DWORD bytesRead;
    bool isCheck = false;

    auto startsWith = [](const std::string& line, const std::string& prefix) {
        return line.compare(0, prefix.size(), prefix) == 0;
    };

    // Read until we find "Checkers:" or until pipe closes
    while (ReadFile(hChildStd_OUT_Rd, buffer, sizeof(buffer) - 1, &bytesRead, NULL) && bytesRead > 0) {
        buffer[bytesRead] = '\0';
        output += buffer;

        std::istringstream iss(output);
        std::string line;
        while (std::getline(iss, line)) {
            if (line.find("Checkers:") != std::string::npos) {
                std::string checkers = line.substr(line.find(":") + 1);
                checkers.erase(remove_if(checkers.begin(), checkers.end(), ::isspace), checkers.end());

                if (!checkers.empty()) {
                    isCheck = true;
                }
                goto done; // Found what we need, exit early
            }
        }
    }

done:
    // Cleanup
    CloseHandle(hChildStd_OUT_Rd);
    CloseHandle(hChildStd_OUT_Wr);
    CloseHandle(hChildStd_IN_Rd);
    CloseHandle(hChildStd_IN_Wr);
    TerminateProcess(pi.hProcess, 0);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return isCheck;
}