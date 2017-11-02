
#include "MyRedis.h"
#include "hiredis.h"
#include "logger.h"
#include "defines.h"

MyRedis::MyRedis() : r_co(nullptr)
{
}

MyRedis::~MyRedis()
{
}

bool MyRedis::Redis_Init()
{
	struct timeval timeout = { 1, 500000 }; // 1.5 seconds
	r_co = redisConnectWithTimeout((char*)"127.0.0.1", 6379, timeout);
	if (r_co == nullptr || r_co->err) {
		LOG_ERROR << r_co->errstr;
		return false;
	}

	LOG_NORMAL << "Connect to redisServer Success";
	return true;
}

void MyRedis::Redis_Finalize()
{
	redisFree(r_co);
}

bool MyRedis::_Redis_Exec(const char *command)
{
	redisReply *reply = (redisReply*)redisCommand(r_co, command);
	freeReplyObject(reply);
	return true;
}