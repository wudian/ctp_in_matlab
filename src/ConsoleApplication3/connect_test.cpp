/* Copyright (C) 2000 MySQL AB

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */

#include <WinSock2.h>
#include <stdio.h>
#include <stdlib.h>
#include "mysql.h"

static void change_user(MYSQL *sock,const char *user, const char *password,
			const char *db,my_bool warning)
{
  if (mysql_change_user(sock,user,password,db) != warning)
  {
    fprintf(stderr,"Couldn't change user to: user: '%s', password: '%s', db: '%s':  Error: %s\n",
	    user, password ? password : "", db ? db : "",
	    mysql_error(sock));
  }
}

#define SELECT_QUERY "select host,user,password from user;"

int main(int argc, char **argv)
{
  MYSQL *sock;
  MYSQL_RES *res;
  MYSQL_ROW row; 
  MYSQL_FIELD *field;
  

  if (!(sock=mysql_init(0)))
  {
    fprintf(stderr,"Couldn't initialize mysql struct\n");
    exit(1);
  }
  
  if (!mysql_real_connect(sock,NULL,"wudian","wudian","test",0,NULL,0))
  {
    fprintf(stderr,"Couldn't connect to engine!\n%s\n",mysql_error(sock));
    perror("");
    exit(1);
  }
  sock->reconnect= 1;

 
  if(mysql_query(sock,SELECT_QUERY))
  {
	  fprintf(stderr,"Query failed (%s)\n",mysql_error(sock));
	  exit(1);
  }
  if (!(res=mysql_store_result(sock)))
  {
	  fprintf(stderr,"Couldn't get result from %s\n",
		  mysql_error(sock));
	  exit(1);
  }

  while(field = mysql_fetch_field(res)) {
	  printf("%s\t", field->name);
  }
  printf("\n");

  int num_fields = mysql_num_fields(res);
  while ((row = mysql_fetch_row(res)))
  {
	  for(int i = 0; i < num_fields; i++)
	  {
		  printf("%s\t", row[i] ? row[i] : "NULL");
	  }
	  printf("\n");
  }

  mysql_free_result(res);
  mysql_close(sock);


  return 0;
}
