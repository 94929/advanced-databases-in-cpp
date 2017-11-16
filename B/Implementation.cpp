#include "Implementation.hpp"
#include <iostream>

using namespace std;

//////////////////// Nested Loop Joins ////////////////////

std::vector<std::string> getQualifyingBusinessesIDsVector(Businesses const& b, float latMin, float latMax, float longMin, float longMax) {

	std::vector<std::string> result;
	std::string currId;
	float currLat, currLong;
	for (int i = 0; i < b.ids.size(); i++) {
		currId = b.ids[i];
		currLat = b.latitudes[i];
		currLong = b.longitudes[i];

		if (currLat >= latMin && currLat <= latMax &&
			currLong >= longMin && currLong <= longMax)
			result.push_back(currId);
	}

	return result;
}

std::vector<unsigned long>
performNestedLoopJoinAndAggregation(Reviews const& r, std::vector<std::string> const& qualifyingBusinessesIDs) {

	std::vector<unsigned long> result = {0, 0, 0, 0, 0, 0};
	for (int i = 0; i < r.business_ids.size(); i++)
		for (int j = 0; j < qualifyingBusinessesIDs.size(); j++)
			if (r.business_ids[i] == qualifyingBusinessesIDs[j])
				result[r.stars[i]] += 1;

	return result;
}

//////////////////// Hash Join ////////////////////

std::unordered_set<std::string> getQualifyingBusinessesIDs(Businesses const& b, float latMin, float latMax, float longMin, float longMax) {

	std::unordered_set<std::string> result;
	std::string currId;
	float currLat, currLong;
	for (int i = 0; i < b.ids.size(); i++) {
		currId = b.ids[i];
		currLat = b.latitudes[i];
		currLong = b.longitudes[i];
		
		if (currLat >= latMin && currLat <= latMax &&
			currLong >= longMin && currLong <= longMax)
			result.insert(currId);
	}

	return result;
}

std::vector<unsigned long>
aggregateStarsOfQualifyingBusinesses(Reviews const& r, std::unordered_set<std::string> const& qualifyingBusinesses) {

	std::vector<unsigned long> result = {0, 0, 0, 0, 0, 0};
	for (int i = 0; i < r.business_ids.size(); i++) 
		if (qualifyingBusinesses.count(r.business_ids[i]))
			result[r.stars[i]] += 1;

	return result;
}
