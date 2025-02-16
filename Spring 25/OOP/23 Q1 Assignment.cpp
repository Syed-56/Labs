#include <iostream>
#include <string>
using namespace std;
class Skill;
class Sport;
class Mentor;
class Student;

class Skill {
public:
	string skillName;
	int skillID;
	string description;
	
	Skill(string name, int id, string desc);
	
	void updateSkillDescription(string newDescription);
	void showSkillDetails();
};
class Sport {
public:
	string sportName;
	int sportID;
	string description;
	int reqSkillSize;
	Skill *requiredSkills[3];
	
	Sport(string name, int id, string desc);
	
	void addSkill(Skill *s);
	void removeSkill(Skill *s);
};
class Mentor {
public:
	string mentorName;
	int mentorID;
	int maxLearners;
	int sportExpSize;
	int learnerSize=0;
	Sport *sportExpertise[3];
	Student* assignedLearners[10];
	
	Mentor(string name, int id, int maxL);
	
	void assignLearner(Student *s);
	void removeLearner(Student *s);
	void viewLearners();
	void provideGuidance();
};
class Student {
public:
	string studentName;
	int studentID;
	int age;
	int sportInterestSize;
	Mentor* mentorAssigned;
	Sport *sportInterest[3];
	
	Student(string name, int id, int a);
	
	void registerForMentorship(Mentor *m);
	void viewMentorDetails();
	void updateSportInterests(Sport *s);
};

Skill::Skill(string name, int id, string desc) {
		skillName = name;
		skillID = id;
		description = desc;
		cout << "Skill " << name << " created Successfully\n";
	}
Sport::Sport(string name, int id, string desc) {
		sportName = name;
		sportID = id;
		description = desc;
		reqSkillSize = 0;
		for (int i=0; i<3; i++) {
			requiredSkills[i] = nullptr;  
		}
		cout << "Sport " << name << " created Successfully\n";
	}
Mentor::Mentor(string name, int id, int maxL) {
		mentorName = name;
		mentorID = id;
		maxLearners = maxL;
		sportExpSize = 0;
		for(int i=0; i<3; i++) {
			sportExpertise[i] = nullptr;
		}
		for(int i=0; i<10; i++) {
			assignedLearners[i] = nullptr;
		}
		cout << "Mentor " << name << " created Successfully\n";
	}
Student::Student(string name, int id, int a) {
		mentorAssigned = nullptr;
		studentName = name;
		studentID = id;
		age = a;
		sportInterestSize = 0;
		for(int i=0; i<3; i++) {
			sportInterest[i] = nullptr;
		}
		cout << "Student " << name << " created Successfully\n";
	}	

void Skill::updateSkillDescription(string newDescription) {
	cout << "\nSkill Description Updated from " << description << " to " << newDescription << endl;
	description = newDescription;
}
void Skill::showSkillDetails() {
	cout << "Skill Name: " << skillName;
	cout << "\nSkill ID: " << skillID;
	cout << "\nSkill Description: " << description;
}

void Sport::addSkill(Skill *s) {
	for(int i=0; i<reqSkillSize; i++) {
		if(s->skillName == requiredSkills[i]->skillName) {
			cout << "Skill Already Present";
			return;
		}
	}
	if (reqSkillSize<3) {
        requiredSkills[reqSkillSize++] = s;
        cout << "Skill " << s->skillName << " Added Successfully in " << sportName << "\n";
    }
    else	cout << "Max Skills Exceeded\n";
}
void Sport::removeSkill(Skill *s) {
	for(int i=0; i<reqSkillSize; i++) {
		if(requiredSkills[i]->skillName == s->skillName) {
			for (int j=i; j<reqSkillSize-1; j++) {
                requiredSkills[j] = requiredSkills[j+1];
            }
            requiredSkills[reqSkillSize-1] = nullptr;
            reqSkillSize--;
            cout << "Skill " << s->skillName << " Removed Successfully from " << sportName << "\n";
            return;
		}
	}
	cout << "SKill Not Found\n";
}

void Mentor::assignLearner(Student *s) {
	if(s->mentorAssigned != nullptr) {
		cout << "Student Already Assigned a Mentor\n";
		return;
	}
	if (learnerSize<10) {
		assignedLearners[learnerSize++] = s;
		cout << "Learner " << s->studentName << " Assigned to " << mentorName << " Successfully\n";
	}
	else	cout << "Max Learners Exceeded\n";
}
void Mentor::removeLearner(Student *s) {
	for(int i=0; i<learnerSize; i++) {
		if(assignedLearners[i]->studentID == s->studentID) {
			for(int j=i; j<learnerSize-1; j++) {
				assignedLearners[j] = assignedLearners[j+1];
			}
			assignedLearners[learnerSize-1] = nullptr;
			learnerSize--;
			cout << "Learner " << s->studentName << " Removed from " << mentorName << " Successfully\n";
			return;
		}
	}
	cout << "Learner Not Found\n";
}
void Mentor::viewLearners() {
	for(int i=0; i<learnerSize; i++) {
		cout << "Learner " << i+1;
		cout << "\nName: " << assignedLearners[i]->studentName;
		cout << "\nAge: " << assignedLearners[i]->age;
		cout << "\nID: " << assignedLearners[i]->studentID;
		cout << endl;
	}
}
void Mentor::provideGuidance() {
	cout << "Don't Worry! Keep working hard and pushing yourself and desired outcome will be achieved.\n";
}

void Student::registerForMentorship(Mentor *m) {
	if(mentorAssigned != nullptr) {
		cout << "Student Already Assigned a Mentor\n";
		return;
	}
	if(m->learnerSize<3) {
		mentorAssigned = m;
		cout << "Registration of " << studentName << " with " << m->mentorName << " Successfull\n";
	}
	else  cout << "Mentor Already Full\n";
}
void Student::viewMentorDetails() {
	cout << "Mentor Details of " << studentName << ":-" << endl;
	cout << "Mentor Name: " << mentorAssigned->mentorName;
	cout << "\nMentor ID: " << mentorAssigned->mentorID;
	cout << "\nMentor Max Learners: " << mentorAssigned->maxLearners;
	cout << "\n\n";
}
void Student::updateSportInterests(Sport *s) {
	for(int i=0; i<sportInterestSize; i++) {
		if(s->sportName == sportInterest[i]->sportName) {
			cout << "Sport Interest Already Present\n";
			return;
		}
	}
	if(sportInterestSize < 3) {
		sportInterest[sportInterestSize++] = s;
		cout << "Interest " << s->sportName << " Updated Successfully\n";
	}
	else	cout << "Sport Interests full\n";
}

int main(void) {
	Mentor m1("Syed Sultan",240585,10);
	Mentor m2("Syed Khizer",240586,10);
	cout << endl;
	Student s1("Ali Kashif",100,18);
	Student s2("Ali Hussain",200,19);
	Student s3("Hammad",300,20);
	Student s4("Huzaifa Shahid",400,21);
	Student s5("Ismail Silat",500,22);
	cout << endl;
	Sport sp1("Cricket",1000,"Team Sport Played with Bat and Ball to socre run and take wicket");
	Sport sp2("Football",2000,"Outdoor Sport in which one team kicks ball in other teams goal");
	Sport sp3("Boxing",3000,"Fighting sport where players hit eachother to knock them out");
	cout << endl;
	Skill sk1("Batting",1001,"Play shots");
	Skill sk2("Bowling",1002,"Throws a ball");
	Skill sk3("Fielding",1003,"Catch the ball");
	Skill sk4("Running",2001,"Run with Ball");
	Skill sk5("Kicking",2002,"Shoot the Ball");
	Skill sk6("Tackle",2003,"Snatch The Ball");
	Skill sk7("Punching",3001,"To hit");
	Skill sk8("Dodging",3002,"Escape punches");
	Skill sk9("Reflex",3003,"To decieve opponent");
	cout << endl;
	sp1.addSkill(&sk1);
	sp1.addSkill(&sk2);
	sp1.addSkill(&sk3);
	sp1.removeSkill(&sk3);
	sp2.addSkill(&sk4);
	sp2.addSkill(&sk5);
	sp2.addSkill(&sk6);
	sp2.removeSkill(&sk6);
	sp3.addSkill(&sk7);
	sp3.addSkill(&sk8);
	sp3.addSkill(&sk9);
	sp3.removeSkill(&sk9);
	cout << endl;
	m1.sportExpertise[0] = &sp1;
	m1.sportExpertise[1] = &sp2;
	m2.sportExpertise[0] = &sp2;
	m2.sportExpertise[1] = &sp3;
	
	s1.sportInterest[0] = &sp1;
	s1.sportInterest[1] = &sp2;
	s1.updateSportInterests(&sp3);
	s2.sportInterest[0] = &sp2;
	s2.sportInterest[1] = &sp3;
	s2.updateSportInterests(&sp1);
	s3.sportInterest[0] = &sp1;
	s3.sportInterest[1] = &sp3;
	s3.updateSportInterests(&sp2);
	s4.sportInterest[0] = &sp2;
	s4.sportInterest[1] = &sp3;
	s4.updateSportInterests(&sp1);
	s5.sportInterest[0] = &sp1;
	s5.sportInterest[1] = &sp2;
	s5.updateSportInterests(&sp3);
	cout << endl;
	
	sk1.showSkillDetails();
	sk2.updateSkillDescription("Take Wicket by thwroing ball");
	cout<<endl;
	
	s1.registerForMentorship(&m1);
	s2.registerForMentorship(&m2);
	s3.registerForMentorship(&m1);
	s4.registerForMentorship(&m2);
	cout << endl;
	
	s1.viewMentorDetails();
	s2.viewMentorDetails();
	cout << endl;
	
	m1.viewLearners();
	m2.viewLearners();
	cout << endl;
	
	m1.provideGuidance();
	m2.provideGuidance();
	cout << endl;
	
	m1.assignLearner(&s5);
	m2.removeLearner(&s3);
	
return 0;	
}	