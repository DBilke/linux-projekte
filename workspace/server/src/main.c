#include "main.h"

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

int main(int argc, char **argv)
{

  /* CLIENT FOR MYSQL MESSAGE TRANSFER
   * ENTER pswd, host, username, testdb
   * ENTER client_script
   * ENTER IP of current client
   *
   */

  char root_pswd[] = "root";
  char root_host[] = "localhost";
  char root_username[] = "root";
  char root_db[] = "test";
  char pswd[] = "server";
  char host[] = "localhost";
  char username[] = "server";
  char db[] = "srv_clnt";
  char server_ip[] = "127.0.0.1";
  char setup_sql_file[] = "/home/dbilke/init.sql";
  char cleanup_sql_file[] = "/home/dbilke/cleanup.sql";

  char sql_cmd[100];
  char sys_cmd[200];
  char str_code[20];

  // SET UP MYSQL DATABASE
  sprintf(sys_cmd, "mysql --host=%s --user=%s --password=%s --database=%s -e \"source %s;\"",
		  root_host,
		  root_username,
		  root_pswd,
		  root_db,
		  setup_sql_file);
  system(sys_cmd);

  MYSQL *con = mysql_init(NULL);

  // CONNECT AND SET UP TABLE
  if (con == NULL)
  {
      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
  }

  if (mysql_real_connect(con, host, username, pswd, db, 0, NULL, 0) == NULL)
  {
      finish_with_error(con);
  }

  sprintf(sql_cmd, "INSERT INTO server(IP) VALUES('%s')", server_ip);
  if (mysql_query(con, sql_cmd))
  {
      finish_with_error(con);
  }


  //GET client messages

  while(1)
  {
	  printf("\n\nEnter \"get\" for getting messages!\n");
	  printf("Enter \"delete\" for deleting all messages!\n");
	  printf("Enter \"quit\" for quitting program!\n");
	  scanf("%s", str_code);

	  if(strcmp(str_code, "delete") == 0)
	  {
		  if (mysql_query(con, "DELETE FROM client"))
		   {
			   finish_with_error(con);
		   }
		  printf("\nDELETED ALL MESSAGES!\n");
	  }

	  if(strcmp(str_code, "get") == 0)
	  {
		  //GET messages for this client
		  printf("\n\nCLIENT MESSAGES:\n\n");

		  if (mysql_query(con, "SELECT * FROM client"))
		   {
			   finish_with_error(con);
		   }

		   MYSQL_RES *result = mysql_store_result(con);

		   if (result == NULL)
		   {
			   finish_with_error(con);
		   }

		   int num_fields = mysql_num_fields(result);

		   MYSQL_ROW row;

		   while ((row = mysql_fetch_row(result)))
		   {
			   for(int i = 0; i < num_fields; i++)
			   {
				   printf("%s ", row[i] ? row[i] : "NULL");
			   }
				   printf("\n");
		   }
		   mysql_free_result(result);
	  }

	  if(strcmp(str_code, "quit") == 0)
	  {
		  mysql_close(con);

		  // CLEAN UP MYSQL DATABASE
		  sprintf(sys_cmd, "mysql --host=%s --user=%s --password=%s --database=%s -e \"source %s;\"",
				  root_host,
				  root_username,
				  root_pswd,
				  root_db,
				  cleanup_sql_file);
		  system(sys_cmd);

		  exit(0);
	  }
  }

  mysql_close(con);

  exit(0);
}
