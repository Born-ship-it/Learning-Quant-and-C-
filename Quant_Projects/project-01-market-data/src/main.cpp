#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <curl/curl.h>

// RAII wrapper for CURL handle
class CurlHandle {
public:
    CurlHandle() : handle(curl_easy_init()) {
        if (!handle) throw std::runtime_error("Failed to initialize CURL");
    }
    ~CurlHandle() {
        if (handle) curl_easy_cleanup(handle);
    }
    CURL* get() { return handle; }
private:
    CURL* handle;
};

// Callback to write response data
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

int main() {
    try {
        CurlHandle curl;
        std::string response;

        // Fetch S&P 500 index data from a free API
        curl_easy_setopt(curl.get(), CURLOPT_URL, 
            "https://query1.finance.yahoo.com/v8/finance/chart/%5EGSPC?range=1mo&interval=1d");
        curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl.get());
        if (res != CURLE_OK) {
            throw std::runtime_error(curl_easy_strerror(res));
        }

        // Save to file
        std::ofstream out("sp500_data.json");
        out << response;
        out.close();

        std::cout << "Successfully fetched S&P 500 data. Saved to sp500_data.json\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
