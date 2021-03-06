#include "main.h"

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

int main(int argc, char **argv)
{

  system("mysql --host=localhost --user=root --password=root --database=test -e \"source /home/dbilke/client2_init.sql;\"");

  MYSQL *con = mysql_init(NULL);

  if (con == NULL)
  {
      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
  }

  if (mysql_real_connect(con, "localhost", "client2", "client2",
          "clients", 0, NULL, 0) == NULL)
  {
      finish_with_error(con);
  }

  char *sql = "CREATE TABLE IF NOT EXISTS client2(Id INT PRIMARY KEY AUTO_INCREMENT, IP VARCHAR(15), Message VARCHAR(255))";

  if (mysql_query(con, sql))
  {
      finish_with_error(con);
  }

  if (mysql_query(con, "INSERT INTO client2(IP, Message) VALUES('127.0.0.1', 'TEST HELLO BACK')"))
  {
      finish_with_error(con);
  }

  int id = mysql_insert_id(con);

  printf("The last inserted row id is: %d\n", id);

  mysql_close(con);
  exit(0);
}
