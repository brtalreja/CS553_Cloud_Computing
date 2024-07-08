#include <iostream>
#include <string>
#include <sw/redis++/redis++.h>
#include <fstream>
#include <unordered_map>
#include <chrono>



using namespace sw::redis;

int main(){

        auto redis = Redis("tcp://127.0.0.1:6379");
        std::ifstream dataset_keys("keys.txt");
        std::ifstream dataset_values("values.txt");
        std::unordered_map<std::string, std::string> pairs;
        int count = 0;
        if(dataset_keys && dataset_values){
                std::string key, value;
                while (std::getline(dataset_keys, key) && std::getline(dataset_values, value)){
                        pairs[key] = value;
                        count ++;
                }

        } else {
                std::cout << "Unable to open the file" << std::endl;
                return 0;

        }
        auto start_write = std::chrono::system_clock::now();
        for(auto &[key, value]: pairs){
                redis.set(key, value);
        }
        auto end_write = std::chrono::system_clock::now();
        auto duration_write = std::chrono::duration_cast<std::chrono::milliseconds>(end_write - start_write).count();
        std::cout << "Timetaken for write: "<< duration_write << std::endl;
        auto start_read = std::chrono::system_clock::now();
        for(auto &[key, value]: pairs){
                auto val = redis.get(key);
                if(!val){
                        std::cout << "Unable to read value from redis" << std::endl;
                }
        }
        auto end_read = std::chrono::system_clock::now();
        auto duration_read = std::chrono::duration_cast<std::chrono::milliseconds>(end_read - start_read).count();
        std::cout << "Timetaken for read: "<< duration_read << std::endl;
        auto start = std::chrono::system_clock::now();
        for(auto &[key, value]: pairs){
                auto val = redis.del(key);
                if(!val){
                        std::cout << "Unable to read value from redis" << std::endl;
                }
        }
        auto end = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "Timetaken for delete: "<< duration << std::endl;
}
