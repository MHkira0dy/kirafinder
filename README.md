# kirafinder

This tool is a multithreaded subdomain scanner written in C++ that utilizes libcurl for making HTTP requests.

Include Statements:

The code includes several standard C++ libraries (iostream, string, fstream, cstdlib) and additional libraries such as curl/curl.h for making HTTP requests, thread for multithreading, mutex for synchronization, queue for managing a queue of subdomains, and condition_variable for thread synchronization.
Global Variables:

std::mutex mtx;: This mutex is used to synchronize access to shared resources.
std::condition_variable cv;: This condition variable is used for thread synchronization.
std::queue<std::string> subdomains;: This queue is used to hold the subdomains to be scanned.
Function Definitions:

write_callback: This function is a callback function used by libcurl to handle HTTP response data.
checkURL: This function is executed by each thread to perform the actual URL checking.
printHelp: This function prints out the help message for using the program.
Main Function:

The main function parses command-line arguments to get the domain name and DNS file.
It reads subdomains from the specified DNS file and pushes them into the subdomains queue.
It retrieves the number of available CPU cores to determine the number of threads to spawn.
Threads are created, each executing the checkURL function.

The main thread waits until all subdomains are processed by the worker threads using the condition variable cv.
Once all threads finish their tasks, the program exits.
Usage:

The program is intended to be used from the command line.
It expects the user to provide a domain name and a DNS file containing subdomains to scan.
Output:

If a subdomain responds with an HTTP status code of 200, it prints the URL in green color to the console.
Error Handling:

The program performs basic error handling such as checking for the existence of files and correct command-line arguments.
Overall, this tool is designed to scan a list of subdomains for a given domain in parallel using multiple threads, making HTTP requests and printing out any subdomains that return a successful response.



![image](https://github.com/o337/kirafinder/assets/126006169/80e3abd8-647d-4f7d-99f1-cfe015f96525)
