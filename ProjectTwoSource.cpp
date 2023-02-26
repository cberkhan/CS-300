//Name: Project Two
//Author: Crystal Berkhan
//Version: 1.0

#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>

#include "CSVparser.hpp"

using namespace std;

//define the structure to hold course information
struct Course {
	string id;
	string name;
	string preReqs;
};

//method to display course information
void printCourse(Course courses) {
	cout << courses.id << ", " << courses.name << endl;
	cout << "Prerequisites: " << courses.preReqs << endl;
}

//method to print the course list
void printCourseList(vector<Course> courses) {

	for (int i = 0; i < courses.size() - 1; i++) {
		for (int j = 0; j < courses.size() - 1 - j; j++) {
			if (courses[j].id > courses[j + 1].id) {
				swap(courses[j + 1], courses[j]);
			}
		}
	}

	for (int i = 0; i < courses.size(); i++) {
		printCourse(courses[i]);
	}
}

//method to search for a specific course with user input
void courseSearch(vector<Course> courses) {
	//assign courseNumber to string for user input
	string courseNumber;

	cout << "What course do you want to know about?" << endl;
	cin >> courseNumber;

	//loop through the vector 
	//if course is found, output to user
	for (int i = 0; i < courses.size(); i++) {
		if (courses[i].id == courseNumber) {
			printCourse(courses[i]);
			break;
		}
	}
}

//Load a CSV file containing courses into a container
vector<Course> loadCourses(string csvPath) {
	//define a vector data structure to hold courses read
	vector<Course> courses;
	//initialize the csv Parser using the given path
	csv::Parser file = csv::Parser(csvPath);

	try {
		//loop to read rows of a CSV file
		for (int i = 0; i < file.rowCount(); i++) {
			//create data structure and add to the collection of courses
			Course courseData;
			courseData.id = file[i][0];
			courseData.name = file[i][1];
			courseData.preReqs = file[i][2];
			//push this course to the end
			courses.push_back(courseData);
		}
	}

	catch (csv::Error& e) {
		std::cerr << e.what() << std::endl;
	}
	return courses;
}

//partition the vector of courses into two parts, low and high
int partition(vector<Course>& courses, int begin, int end) {
	//set low and high equal to begin and end
	int low = begin;
	int high = end;

	//pick the middle element as pivot point
	int pivot = begin + (end - begin) / 2;

	//while not done
	bool done = false;

	while (!done) {
		//keep incrementing low index while course[low] < courses[pivot]
		while (courses.at(low).id.compare(courses.at(pivot).id) < 0) {
			++low;
		}
		//keep decrementing high index while courses[pivot] < courses[high]
		while (courses.at(pivot).id.compare(courses.at(high).id) < 0) {
			--high;
		}
		//if there are zero or one elements remaining, all courses are partitioned
		if (low >= high) {
			done = true;
		}
		//else, swap the low and high courses
		else {
			swap(courses.at(low), courses.at(high));
			++low;
			--high;
		}
	}
	return high;

}

//perfrom a quick sort on courses
void quickSort(vector<Course>& courses, int begin, int end) {
	//set mid equal to zero
	int mid = 0;

	//if begin is greater than or equal to end, then return
	if (begin >= end) {
		return;
	}

	//midpoint is location of last element in low
	mid = partition(courses, begin, mid);

	//recursively sort low partition (begin to mid)
	quickSort(courses, begin, mid);

	//recursively sort high partition (mid+1 to end)
	quickSort(courses, mid + 1, end);
}


int main(int argc, char* argv[]) {
	//process command line arguments
	string csvPath;
	switch (argc) {
	case 2:
		csvPath = argv[1];
		break;
	default:
		csvPath = "CourseInformation.csv";
	}
	//define a vector to hold courses
	vector<Course> courses;

	int choice = 0;

	while (choice != 4) {
		//display menu while choice is not 4
		cout << "------ Menu ------" << endl;
		cout << "1. Load Data Structure" << endl;
		cout << "2. Course List" << endl;
		cout << "3. Print Course" << endl;
		cout << "4. Exit" << endl;
		cout << "Enter choice" << endl;
		cin >> choice;

		switch (choice) {

		case 1:
			//Method call to load the data structure
			courses = loadCourses(csvPath);

			cout << "Loading Data Structure" << endl;
			cout << courses.size() << " courses read" << endl;

			break;

		case 2:
			cout << "Here is a sample schedule:" << endl;
			cout << endl;

			//Method call to alphanumeric order and display the courses
			quickSort(courses, 0, courses.size() - 1);

			//display course list
			printCourseList(courses);

			cout << endl;
			break;

		case 3:
			//Method to search for a specific course
			courseSearch(courses);

			cout << endl;
			break;


		case 4:
			//end program
			cout << "Thank you for using the course planner!" << endl;
			break;

		default:
			//default if input is not 1-4
			cout << "Invalid input, try again" << endl;
			cout << endl;
			break;
		}

	}
}




