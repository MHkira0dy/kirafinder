# kirafinder

This tool is a multithreaded subdomain scanner written in C++ that utilizes libcurl for making HTTP requests.


![image](https://github.com/o337/kirafinder/assets/126006169/80e3abd8-647d-4f7d-99f1-cfe015f96525)

# kirafinder how to install

```
sudo apt update
```
```
https://github.com/MHkira0dy/kirafinder.git
```

# How to run the tool

To run the provided code, you will need:

A C++ compiler installed on your system, such as GCC or Clang.
The libcurl library installed on your system. You can typically install it using your package manager. For example, on Debian-based systems, you can use :
```
apt install libcurl4-openssl-dev
```
A text file containing a list of subdomains (one per line) that you want to check.
Here are the steps to compile and run the code:

Save the provided code into a file, let's say main.cpp.

Compile the code using a C++ compiler along with the libcurl library. For example, you can use the following command:
```
g++ -o checker main.cpp -lcurl -std=c++11 -pthread
```
This command will compile the code into an executable named checker, linking against the libcurl library and enabling C++11 support along with pthread for multithreading.

Make sure you have a text file containing a list of subdomains. Let's say the file is named subdomains.txt and contains one subdomain per line.

Run the compiled executable, providing the domain you want to check and the path to the text file containing subdomains as command-line arguments. For example:

```
./checker -d example.com subdomains.txt
```

Replace example.com with the domain you want to check, and subdomains.txt with the path to your text file containing subdomains.

After running the executable, it will check each subdomain in the list against the specified domain, printing out the URLs that return a HTTP status code of 200



