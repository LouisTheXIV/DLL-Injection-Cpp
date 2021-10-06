#include <iostream>
#include <windows.h>
#include <string>
#include <thread>
#include <libloaderapi.h>

using namespace std;

void getProcID(const char* window_title, DWORD &process_id) 
{
    GetWindowThreadProcessId(FindWindow(NULL, window_title), &process_id);
}

void error(const char* error_title, const char* error_msg)
{
    MessageBox(0, error_msg, error_title, 0);
    exit(-1);
}

bool DLLExists(string file_name)
{
    struct stat buffer;
    return (stat(file_name.c_str(), &buffer) == 0);
}

int main()
{
    DWORD proc_id = NULL;
    char dll_path[MAX_PATH];
    const char* dll_name = "InjectDLL.dll";
    const char* window_title = "Untitled - Notepad";

    if (!DLLExists(dll_name)) {
        error("DLLExists", "DLL Doesn't exist!");
    }

    if (!GetFullPathName(dll_name, MAX_PATH, dll_path, nullptr)) {
        error("GetFullPath", "failed to get full path of DLL!");
    }

    getProcID(window_title, proc_id);
    if (proc_id == NULL) {
        error("GetProcessID", "failed to get process id!");
    }

    HANDLE h_process = OpenProcess(PROCESS_ALL_ACCESS, NULL, proc_id);
    if (!h_process) {
        error("OpenProcess", "failed to open a handle to process!");
    }

    void* allocated_memory = VirtualAllocEx(h_process, nullptr, MAX_PATH, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (!allocated_memory) {
        error("AllocateMemory", "failed to allocate memory!");
    }

    if (!WriteProcessMemory(h_process, allocated_memory, dll_path, MAX_PATH, nullptr)) {
        error("WriteProcessMemory", "failed to write to process memory!");
    }

    HANDLE h_thread = CreateRemoteThread(h_process, nullptr, NULL, LPTHREAD_START_ROUTINE(LoadLibraryA), allocated_memory, NULL, nullptr);
    if (!h_thread) {
        error("CreateRemoteThread", "failed to create remote thread!");
    }

    CloseHandle(h_process);
    VirtualFreeEx(h_process, allocated_memory, NULL, MEM_RELEASE);
    MessageBox(0, "Successfully Injected!", "Success", 0);
}

