#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <curl/curl.h>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <vector>

std::mutex mtx;
std::condition_variable cv;
std::queue<std::string> subdomains;

size_t write_callback(void *contents, size_t size, size_t nmemb, std::string *buffer) {
    size_t realsize = size * nmemb;
    buffer->append((char*)contents, realsize);
    return realsize;
}

void checkURL(const std::string& domain) {
    while (true) {
        std::string subdomain;
        {
            std::unique_lock<std::mutex> lock(mtx);
            if (subdomains.empty()) {
                break;
            }
            subdomain = subdomains.front();
            subdomains.pop();
        }

        std::string url = subdomain + "." + domain;
        CURL *curl;
        CURLcode res;
        curl = curl_easy_init();
        if(curl) {
            std::string readBuffer;
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L); // Timeout after 5 seconds
            res = curl_easy_perform(curl);
            if(res == CURLE_OK) {
                long response_code;
                curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
                if (response_code == 200) {
                    mtx.lock();
                    std::cout << "\033[1;32m" << url << "\033[0m" << std::endl;
                    mtx.unlock();
                }
            }
            curl_easy_cleanup(curl);
        }
    }
    cv.notify_one();
}

void printHelp(const std::string& programName) {
    std::cout << "Usage: " << programName << " -d <domain> <dns.txt>" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  --help        Display this help message" << std::endl;
}

int main(int argc, char *argv[]) {
    if (argc == 2 && std::string(argv[1]) == "--help") {
        printHelp(argv[0]);
        return 0;
    }

    std::cout <<"          [didicas lga3 drari ta3 the hacker news bdarija]" << std::endl;
    std::cout << "                             @MHkira0dy    " << std::endl; // Print your name
    
    if (argc != 4 || std::string(argv[1]) != "-d") {
        std::cerr << "Usage: " << argv[0] << " -d <domain> <dns.txt>" << std::endl;
        return 1;
    }

    std::string domain = argv[2];
    std::string filename = argv[3];

    std::ifstream dnsFile(filename);
    if (!dnsFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    std::string subdomain;
    while (dnsFile >> subdomain) {
        subdomains.push(subdomain);
    }

    int num_threads = std::thread::hardware_concurrency(); // Get number of avail
    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(checkURL, domain);
    }

    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&](){ return subdomains.empty(); });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
