#ifndef _MY_REDIS_H_
#define _MY_REDIS_H_

struct redisContext;

class MyRedis
{
public:
	MyRedis();
	~MyRedis();

	bool Redis_Init();
	void Redis_Finalize();


private:
	redisContext *r_co;

	bool _Redis_Exec(const char *command);
};

#endif