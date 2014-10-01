#include <iostream>
#include <string>
#include <dirent.h>
#include <vector>
#include <stdio.h>
#include <unistd.h>

using namespace std;

struct process{
	process();
	process(string, int, vector<string>, string);
	void setProcess(string, int, vector<string>, string);
	int pid;
	string proc_exe;
	string name;
	vector<string> handles;
};

process::process()
{
	pid = 0;
}
process::process(string name, int pid, vector<string> handles, string proc_exe)
{
	setProcess(name, pid, handles, proc_exe);
}

void process::setProcess(string newName, int newPid, vector<string> newHandles, string newProc_exe)
{
	pid			= newPid;
	name 		= newName;
	handles 	= newHandles;
	proc_exe 	= newProc_exe;
}

int main()
{
	vector<process> processes;
	process proc;
	FILE *file;
	struct dirent* entry;
	int filenode;
    char filename[0xFFF];
    char proclnk[0xFFF];
    int MAXSIZE = 0xFFF;
	ssize_t r;

	DIR* dir = opendir("/proc/");
	if (!dir)
	{
		perror("OPENDIR");
	}
	while ((entry = readdir(dir)) != NULL)
	{
		sprintf(proclnk, "/proc/%s/exe", entry->d_name);
        r = readlink(proclnk, filename, MAXSIZE);

		//proc.setProcess(,entry->d_name,,);
		//processes.push_back(proc);
		if (r < 0)
		{
			//printf("failed to readlink\n");
			//break;
		}
		filename[r] = '\0';

		printf("PID: %s    Filename: %s\n", entry->d_name, filename);
	}
	return 0;
}
