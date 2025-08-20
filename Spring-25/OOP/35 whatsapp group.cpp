#include <iostream>
#include <ctime>
using namespace std;
string getCurrentTime() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
    return string(buffer);
}
class User {
	string name;
	string about;
	long phoneNum;
	
	public:
	static int userCount;
	User() {}
	User(string n, long phone) : name(n) , phoneNum(phone) {
		userCount++;
	}
	
	void setName(string n) 	  {name = n;}
	void setPhone(long phone) {phoneNum = phone;}
	void setAbout(string a)   {about = a;}
	
	string getName() {return name;}
	long getPhone()  {return phoneNum;}
	string getAbout() {return about;}
};

class Message {
	string text;
	string msgTime;
	User msgSender;
	
	public:
	Message() {}
	Message(string t, User sender, string time) : text(t) , msgSender(sender) , msgTime(time) {
		cout << "Message Delivered\n";
	}
	
	void setText(string t) 			{text = t;}
	void setMsgTime() 			    {msgTime = getCurrentTime();}
	void setMsgSender(User sender)  {msgSender = sender;}
	
	string getText(string t) 			 {return text;}
	string getMsgTime(string time) 		 {return msgTime;}
	User getMsgSender(string sender)	 {return msgSender;}
};
class WhatsappGroup {
	string groupName;
	string groupInfo;
	string groupCreationDate;
	Message *msg;
	User adminList[5];
	User userList[20];
	
	public:
	int adminCount = 1;
	WhatsappGroup(string groupName, string groupInfo, string groupCreationDate) {
		this->groupName = groupName;
		this->groupInfo = groupInfo;
		this->groupCreationDate = getCurrentTime();
		msg = new Message[10];
	}
	WhatsappGroup(const WhatsappGroup& obj) = default;
	
	void setGroupName(string name) 	  {groupName = name;}
	void setGroupInfo(string info) 	  {groupInfo = info;}
	void setCreationDate()			  {groupCreationDate = getCurrentTime();}
	void setMessage(Message m) 	  	  {*msg = m;}
	
	string getGroupName() 	 {return groupName;}
	string getGroupInfo() 	 {return groupInfo;}
	string getCreationDate() {return groupCreationDate ;}
	Message getMessage() 	 {return *msg;}
	
	void addAdmin(User *u) {
		if(adminCount==5) {
			cout << "Admin Limit Reached\n";
			return;
		}
		for(int i=0; i<u->userCount; i++) {
			if(u->getName()==adminList[i].getName()) {
				adminList[adminCount-1] = *u;
				adminCount++;
				return;
			}
		}
		cout << "User Not Found\n";
	}
	void removeAdmin(User *u) {
		if(adminCount==1) {
			cout << "Group can't exist without admin\n";
			return;
		}
		int found=-1;
		for(int i=0; i<u->userCount; i++) {
			if(u->getName()==adminList[i].getName()) {
				found=i;
				adminList[i].setName("Unknown");
				adminList[i].setPhone(00000000);
				adminList[i].setAbout("Not Found");
			}
		}
		if(found==-1) {
			cout << "User not found\n";
			return;
		}
		for(int i=found; i<adminCount; i++) {
			adminList[i] = adminList[i+1];
		}
		adminCount--;
	}
	void sendMessage(Message *m) {
		
	}
	
	~WhatsappGroup() {
		delete[] msg;
	}
};

int main(void) {
	int n;
	cout << "How Many User You want to create: ";
	cin >> n;
	User u[n];
}