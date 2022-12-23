
#include <stdlib.h>
#include <string>
#include<stdio.h>

// include the sql parser
#include "SQLParser.h"

// contains printing utilities
#include "util/sqlhelper.h"


int main(int argc, char* argv[]) {
  std::string query;
  query.resize(1024);
  FILE* fp = fopen("sql_test","r");
  while (fgets((char*)query.c_str() , 1024 ,fp) != NULL)
  {
    printf("sql:%s \t len:%ld\n" , query.c_str() ,query.length() );
    
    // parse a given query
    hsql::SQLParserResult result;
    hsql::SQLParser::parse(query, &result);

  // check whether the parsing was successful
    if (result.isValid()) {
      printf("Parsed successfully!\n");
      printf("Number of statements: %lu\n", result.size());

      for (auto i = 0u; i < result.size(); ++i) {
        // Print a statement summary.
        hsql::printStatementInfo(result.getStatement(i));
      }
    } else {
      fprintf(stderr, "Given string is not a valid SQL query.\n");
      fprintf(stderr, "%s (L%d:%d)\n",
              result.errorMsg(),
              result.errorLine(),
              result.errorColumn());
      return -1;
    }
  }
  return 0;
}
