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

  char pswd[] = "client";
  char host[] = "localhost";
  char username[] = "client";
  char db[] = "srv_clnt";
  char client_ip[] = "127.0.0.1";
  char ip[16], msg[256];
  char str_code[20];
  char sql[100];

  MYSQL *con = mysql_init(NULL);

  if (con == NULL)
  {
      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
  }

  if (mysql_real_connect(con, host, username, pswd, db, 0, NULL, 0) == NULL)
  {
      finish_with_error(con);
  }


  while(1)
  {
	  printf("\n\nEnter \"get\" for getting messages!\n");
	  printf("Enter \"send\" for sending messages!\n");
	  printf("Enter \"quit\" for quitting program!\n");
	  scanf("%s", str_code);

	  if(strcmp(str_code, "send") == 0)
	  {

		  printf("\n\nEnter destination  IP: ");
		  scanf("%s", ip);

		  printf("Enter Message: ");
		  scanf("%s", msg);

		  sprintf(sql, "INSERT INTO client(IP, MSG) VALUES('%s', '%s')", ip, msg);
		  if (mysql_query(con, sql))
		  {
			  finish_with_error(con);
		  }
	  }

	  if(strcmp(str_code, "get") == 0)
	  {
		  //GET messages for this client
		  printf("\n\nMESSAGES FOR THIS CLIENT:\n\n");

		  sprintf(sql, "SELECT * FROM client WHERE ip='%s'", client_ip);
		  if (mysql_query(con, sql))
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
		  exit(0);
	  }
  }
}
