#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>
#include <chrono>


using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

int main(){

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
        mongocxx::instance instance{}; // This should be done only once.
        mongocxx::client client{mongocxx::uri{}};
        mongocxx::database db = client["mydb"];
        mongocxx::collection coll = db["test"];
        auto builder = bsoncxx::builder::stream::document{};
        std::vector<bsoncxx::document::value> documents;

        auto start_write = std::chrono::system_clock::now();
        for(auto& [key, value]: pairs) {
                documents.push_back(
                bsoncxx::builder::stream::document{} << key << value << finalize);
        }
        coll.insert_many(documents);
        auto end_write = std::chrono::system_clock::now();
        auto duration_write = std::chrono::duration_cast<std::chrono::milliseconds>(end_write - start_write).count();


        auto start_read = std::chrono::system_clock::now();
        mongocxx::cursor cursor = coll.find({});

        for(auto doc : cursor) {
                std::cout << bsoncxx::to_json(doc) << "\n";
        }
        auto end_read = std::chrono::system_clock::now();                                                                                                                                            1,1           Top
        auto duration_read = std::chrono::duration_cast<std::chrono::milliseconds>(end_read - start_read).count();

        auto start_delete = std::chrono::system_clock::now();
        bsoncxx::stdx::optional<mongocxx::result::delete_result> result =
        coll.delete_many({});
        auto end_delete = std::chrono::system_clock::now();
        auto duration_delete = std::chrono::duration_cast<std::chrono::milliseconds>(end_delete - start_delete).count();

        if(result) {
                std::cout << result->deleted_count() << "\n";
        }
        std::cout << "Timetaken for write: "<< duration_write << std::endl;
        std::cout << "Timetaken for read: "<< duration_read << std::endl;
        std::cout << "Timetaken for delete: "<< duration_delete << std::endl;
}