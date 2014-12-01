#include <stdio.h>
#include <windows.h>
#include <mysql.h>

//spit out mysql_error for connection
void finishWithError(MYSQL *conn)
{
  fprintf(stderr, "%s\n", mysql_error(conn));
  mysql_close(conn);
  exit(1);
}

//run a mysql query
void queryDatabase(MYSQL *conn, char *query)
{
  if (mysql_query(conn, query))
  {
    finishWithError(conn);
  }
}

//begin
int main(int argc, char *argv[])
{

  //file output
  char *filename = "output.csv";
  char *mode = "w";
  //open file for output
  FILE *file;
  file = fopen(filename, mode);
  //error check
  if(file == NULL) {
    printf("file open failure");
    exit(1);
  }

/* DON"T NEED UNLESS QUERY FILE FEATURE IS ADDED
  //file read
  char *filename2 = "query.txt";
  char *mode2 = "r";
  //open file for read
  FILE *file2;
  file2 = fopen(filename2, mode2);
  //error check
  if(file2 == NULL) {
    printf("failed to read query file");
    exit(1);
  }
*/

  //initiation of a connection handle structure
  MYSQL *conn = mysql_init(NULL);

  //error check
  if (conn == NULL)
  {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }

  //connect to mysql database
  if (mysql_real_connect(conn, "localhost","root",
          "drowssap", "stocks", 0, NULL, 0) == NULL)
  {
    finishWithError(conn);
  }

/*
  THIS SHOULDN"T BE UNCOMMENTED
  //allocating 6000 chars to querystring...not sure if this is a good idea
  char querystring[6000];
  char ch;
  printf("trying fgetc: \n");
  while( ( ch = fgetc(file2) ) != EOF ) {
      querystring[ strlen(querystring) ] = ch;
      querystring[strlen(querystring)]
      printf("%c",ch);
    }
    printf("\n");
    printf(querystring);
*/

  //write query
  char *query =  "SELECT spm1.date, \n"
  "(( ln(spm1.close/spm1.open)) - (ln(spm2.close/spm2.open)))*100 \n"
  "FROM stocks.stock_prices_minute spm1 \n"
  "INNER JOIN stocks.stock_prices_minute spm2 \n"
  "ON spm1.date = spm2.date \n"
  "WHERE spm1.symbol = 'AAPL' \n"
  "AND spm2.symbol = 'GOOG' \n";
  //"AND spm1.date > '2012-08-01' \n"
  //"AND spm1.date < '2013-06-01'";
  //use query function
  queryDatabase(conn,query);

  //store result
  MYSQL_RES *result = mysql_store_result(conn);
  if(result == NULL)
  {
    finishWithError(conn);
  }

  //get number of fields
  int num_fields = mysql_num_fields(result);

  MYSQL_ROW row;

  while ((row = mysql_fetch_row(result)))
  {
    for(int i = 0; i < num_fields; i++)
    {
      fprintf(file, "%s, ", row[i] ? row[i] : "NULL");
      //printf("%s ", row[i] ? row[i] : "NULL");
    }
      fprintf(file, "\n");
      //printf("\n");
  }

  //make sure we close the connection
  mysql_close(conn);

  //print out version info
  printf("MySQL client version: %s\n", mysql_get_client_info());

  //make sure to close the file
  fclose(file);

  return(0);
}
