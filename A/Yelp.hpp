#include <memory>
#include <odb/core.hxx>
#include <odb/lazy-ptr.hxx>
#include <set>
#include <string>

#pragma db view
class StarCount{
public:
	int stars;
	int count;
};

#pragma db view query("select top 1 text, last_elapsed_time from sys.dm_exec_query_stats cross apply sys.dm_exec_sql_text(sql_handle) order by last_execution_time desc")
class LastQueryTime{
public:
	std::string text;
	long elapsed_time;
};

class business;
class hours;
class review;
class user;

#pragma db object
class business {
public:
	#pragma db id
	std::string id;

	std::string name;
	std::string neighborhood;
	std::string address;
	std::string city;
	std::string state;
	std::string postal_code;
	float latitude;
	float longitude;
	float stars;
	int review_count;
	int is_open;
 	
    #pragma db value_not_null inverse(business_id)
	std::set<std::shared_ptr<hours>> business_hours;
};

#pragma db object
class hours {
public:
	#pragma db id
	int id;

	std::string hours;
	
	#pragma db not_null
	odb::lazy_weak_ptr<business> business_id;
};

#pragma db object
class review {
public:
	#pragma db id
	std::string id;

	int stars;
	std::string date;
	std::string text;
	int useful;
	int funny;
	int cool;

	#pragma db not_null
	std::shared_ptr<business> business_id;

	#pragma db not_null
	odb::lazy_weak_ptr<user> user_id;
};

#pragma db object
class user {
public:
	#pragma db id
	std::string id;

	std::string name;
	int review_count;
	std::string yelping_since;
	int useful;
	int funny;
	int cool;
	int fans;
	float average_stars;
	int compliment_hot;
	int compliment_more;
	int compliment_profile;
	int compliment_cute;
	int compliment_list;
	int compliment_note;
	int compliment_plain;
	int compliment_cool;
	int compliment_funny;
	int compliment_writer;
	int compliment_photos;

	#pragma db inverse(user_id)
	std::set<std::shared_ptr<review>> reviews;
}; 

