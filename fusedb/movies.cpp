#define MYSQLPP_MYSQL_HEADERS_BURIED
#include <mysql++/mysql++.h>
#include <string>
#include "moviesdb.h"

mysqlpp::Query connect() {
    // Connect to database with: database, server, userID, password
    mysqlpp::Connection myDB("cse381", "localhost", "cse381", "FIXME");
    // Create a query 
    mysqlpp::Query query = myDB.query();

    return myDB.query();
}


void getMovieListing(std::vector<std::string> &movies) {
	movies.push_back("Avatar");
	movies.push_back("Home Alone");
}

void getMovieInfo(const char * path, std::string &buf) {
	buf += "title = " + std::string(path) + "\n";
}




