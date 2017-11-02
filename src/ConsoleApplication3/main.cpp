

#include <iostream>
using namespace std;
#include <WinSock2.h>
#include <mysql.h>
#include <thread>
#include <chrono>

static char *server_args[] = {
	"this_program",       /* this string is not used */
	"--datadir='F:\\CTP-MATLAB\\src\\ConsoleApplication3'",
	"--key_buffer_size=32M"
};
static char *server_groups[] = {
	"embedded",
	"server",
	"this_program_SERVER",
	(char *)NULL
};

void thread_fun()
{
	MYSQL *myData; 
	MYSQL_RES * res; 
	MYSQL_ROW row; 
	MYSQL_FIELD *field;

	myData = mysql_init(0);
	static bool	s_bReconnect = true;	
	if (mysql_options(myData, MYSQL_OPT_RECONNECT, &s_bReconnect))
		std::cout << "ÉèÖÃmysqlµÄoptionÊ§°Ü";
	myData = mysql_real_connect( myData, "192.168.25.109", "wudian", "wudian", "test", MYSQL_PORT, NULL, CLIENT_MULTI_STATEMENTS );
	
	if (mysql_query(myData, "create table if not exists tbl(id int, name varchar(10), primary key(id));"))
		std::cout << mysql_error(myData) << endl;
	if (mysql_query(myData, "replace into tbl values(4, 'dd');"))
		std::cout << mysql_error(myData)<< endl;
	if (mysql_query(myData, "replace into tbl values(6, 'd6');"))
		std::cout << mysql_error(myData)<< endl;
	if (mysql_query(myData, "replace into tbl values(7, 'd7');"))
		std::cout << mysql_error(myData)<< endl;


	/*std::chrono::milliseconds dura( 1000 );
	std::this_thread::sleep_for(dura);*/



	/*res = mysql_store_result(myData);

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

	mysql_free_result(res);*/
	mysql_close(myData);
}
#include <boost/date_time/posix_time/posix_time.hpp>
void main()
{
	string res = boost::posix_time::to_iso_string(boost::posix_time::microsec_clock::local_time());
	res = res.substr(9, 6);
	res.insert(2, ":");
	res.insert(5, ":");

	printf("%x\t%X\t%x", 122, 122, -122);
	if (mysql_library_init(0, nullptr, nullptr))
		return;
	std::thread t1(thread_fun);
	std::thread t2(thread_fun);
	thread_fun();
	t1.join();
	t2.join();
}


/*
#include <iostream>
#include <string>
#include <regex>

int main()
{
	// Simple regular expression matching
	std::string fnames[] = {"foo.txt", "bar.txt", "baz.dat", "zoidberg"};
	std::regex txt_regex("[a-z]+\\.txt");

	for (const auto &fname : fnames) {
		std::cout << fname << ": " << std::regex_match(fname, txt_regex) << '\n';
	}   

	// Extraction of a sub-match
	std::regex base_regex("([a-z]+)(\\.txt)");
	std::smatch base_match;

	for (const auto &fname : fnames) {
		if (std::regex_match(fname, base_match, base_regex)) {
			for (std::smatch::iterator it=base_match.begin(); it!=base_match.end(); ++it)
				cout << it->str() << '\n';
			// The first sub_match is the whole string; the next
			// sub_match is the first parenthesized expression.
			if (base_match.size() == 2) {
			std::ssub_match base_sub_match = base_match[1];
			std::string base = base_sub_match.str();
			std::cout << fname << " has a base of " << base << '\n';
			}
		}
	}

	// Extraction of several sub-matches
	std::regex pieces_regex("([a-z]+)\\.([a-z]+)");
	std::smatch pieces_match;

	for (const auto &fname : fnames) {
		if (std::regex_match(fname, pieces_match, pieces_regex)) {
			std::cout << fname << '\n';
			for (size_t i = 0; i < pieces_match.size(); ++i) {
				std::ssub_match sub_match = pieces_match[i];
				std::string piece = sub_match.str();
				std::cout << "  submatch " << i << ": " << piece << '\n';
			}   
		}   
	}   
}*/