#include<iostream>
#include<fstream>
using namespace std;

class Object;
class Page;
class User;
class Post;
class Memory;
class Facebook;

//Template for deallocation
template<class myClass>
void Deallocation(myClass** toDelete)
{
	for (int i = 0; toDelete[i] != NULL; i++)
	{
		delete toDelete[i];
	}
	delete[] toDelete;
}


class Helper
{
public:
	static int StringLenght(char* str)
	{
		int stringLen = 0;
		if (str != NULL)
		{
			for (char* temp = str; *temp != '\0'; temp++)
				stringLen++;
		}

		return stringLen;
	}

	static char* GetStringFromBuffer(char* buffer)
	{
		int strLen = StringLenght(buffer);
		char* str = 0;

		if (strLen > 0)
		{
			str = new char[strLen + 1];
			char* tempDest = str;
			for (char* tempSrc = buffer; *tempSrc != '\0'; tempSrc++, tempDest++)
			{
				*tempDest = *tempSrc;
			}
			*tempDest = '\0';
		}
		return str;
	}

	static bool Verify(char* temp, char* ID)
	{
		int i = 0, j = 0;
		bool flag = true;

		int len1 = Helper::StringLenght(temp);
		int len2 = Helper::StringLenght(ID);

		if (len2 > len1)
		{
			while (temp[i] != '\0')
			{
				if (ID[i] == temp[i])
				{
					flag = true;
				}
				else
				{
					flag = false;
					break;
				}
				i++;
			}
		}
		else
		{
			while (temp[j] != '\0')
			{
				if (ID[j] == temp[j])
				{
					flag = true;
				}
				else
				{
					flag = false;
					break;
				}
				j++;
			}
		}
		return flag;
	}
};

class Object
{
private:
	char* ID;

public:
	Object()
	{
		ID = NULL;

	}

	void SetID(char* id)
	{
		ID = Helper::GetStringFromBuffer(id);
	}

	char* GetID()
	{
		return ID;
	}

	//Destructor
	~Object()
	{
		if (ID != NULL)
		{
			delete[]ID;
		}
	}

	//Virtual Fuctions
	virtual void PrintName()
	{

	}

	virtual void SetTimeline(Post* post)
	{

	}

	virtual void PrintTimeline()
	{

	}

	virtual void PrintLikedBy()
	{
	}
};

class Activity
{
private:
	int type;
	char* value;
public:
	Activity()
	{
		type = 0;
		value = NULL;
	}

	void ReadActivityFromFile(ifstream& fin)
	{
		fin >> type;
		char temp[80];
		fin.getline(temp, 80);
		value = Helper::GetStringFromBuffer(temp);
	}

	int GetType()
	{
		return type;
	}

	char* GetValue()
	{
		return value;
	}

	~Activity()
	{
		if (value != NULL)
		{
			delete[]value;
		}
	}

};

class Date
{
private:
	int Day;
	int Month;
	int Year;
	static Date CurrentDate;
public:
	Date(int D = 0, int M = 0, int Y = 0);
	void Print();
	~Date();
	void SetDay(int);
	void SetMonth(int);
	void SetYear(int);
	int GetDay();
	void SetDate();
	int YearDifference(Date date);
	bool CompareDate(Date);
	bool CheckDate(Date date);


	void ReadDateFromFile(ifstream& fin)
	{
		fin >> Day;
		fin >> Month;
		fin >> Year;
	}

	static void SetCurrentDate(int d = 0, int m = 0, int y = 0)
	{
		CurrentDate.Day = d;
		CurrentDate.Month = m;
		CurrentDate.Year = y;
	}
	static void PrintCurrentDate() {
		cout << "(" << CurrentDate.Day << "/" << CurrentDate.Month << "/" << CurrentDate.Year << ")";
	}
	/*void SetSharedDate()
	{
		Day = CurrentDate.Day;
		Month = CurrentDate.Month;
		Year = CurrentDate.Year;
	}*/

	bool IfAllowedInMemory(Date d)
	{
		if (Day == d.Day && Month == d.Month && Year != d.Year)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void GetCurrentDate()
	{
		Day = CurrentDate.Day;
		Month = CurrentDate.Month;
		Year = CurrentDate.Year;
	}

};
Date Date::CurrentDate = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// DATE CLASS FUCTIONS ///////////////////////////////////////////
Date::Date(int D, int M, int Y)
{
	Day = D;
	Month = M;
	Year = Y;

}
Date::~Date()
{

}
void Date::Print()
{
	cout << "(" << Day << "/" << Month << "/" << Year << ")";
}
void Date::SetDay(int d)
{
	Day = d;
}
void Date::SetMonth(int m)
{
	Month = m;
}
void Date::SetYear(int y)
{
	Year = y;
}
int Date::GetDay()
{
	return Day;
}
void Date::SetDate()
{
	SetDay(Day);
	SetMonth(Month);
	SetYear(Year);
}
int Date::YearDifference(Date date)
{
	return(Year - date.Year);
}
bool Date::CompareDate(Date D2)
{
	if (Year > D2.Year)
	{
		return true;
	}
	else if (Year == D2.Year)
	{
		if (Month > D2.Month)
		{
			return true;
		}
		else if (Month == D2.Month)
		{
			if (Day > D2.Day)
			{
				return true;
			}
			else if (Day == D2.Day)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
bool Date::CheckDate(Date date)
{
	if (Day == date.Day || Day == (date.Day) + 1)
	{
		return true;
	}
	else
		return false;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// COMMENT CLASS /////////////////////////////////////////////////
class Comment
{
private:
	static int totalComment;

	char* commentID;
	char* commentText;
	Object* CommentBy;

public:

	Comment()
	{
		commentID = 0;
		commentText = 0;
		CommentBy = 0;
	}

	void SetComment(char* text, Object* obj)
	{
		commentID = NULL;
		commentText = Helper::GetStringFromBuffer(text);
		CommentBy = obj;
	}

	void ReadCommentsFromFile(ifstream& fin)
	{
		char temp[80];
		fin >> temp;
		commentID = Helper::GetStringFromBuffer(temp);

	}

	void AddCommentBy(Object* obj)
	{
		CommentBy = obj;
	}

	void ReadCommentTextFromFile(ifstream& fin)
	{
		char temp[80];
		fin.getline(temp, 80);
		commentText = Helper::GetStringFromBuffer(temp);
	}

	char* GetCommentText()
	{
		return commentText;
	}

	void PrintName()
	{
		CommentBy->PrintName();
	}

	Comment* GetComment()
	{
		return this;
	}

	//Destructor
	~Comment()
	{
		if (commentID != NULL)
		{
			delete[]commentID;
		}
		if (commentText != NULL)
		{
			delete[]commentText;
		}
	}

};
int Comment::totalComment = 0;


////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// POST CLASS ////////////////////////////////////////////////////
class Post
{
private:
	int postType;
	char* postID;
	Activity* act;
	char* text;
	Date SharedDate;
	Object* SharedBy;
	Comment** comments;
	Object** likedBy;

	int likedbyCount;
	int commentsCount;
public:
	Post()
	{
		postType = 0;
		postID = NULL;
		text = NULL;
		act = 0;
		SharedDate = 0;
		SharedBy = 0;
		comments = 0;
		likedBy = 0;
		likedbyCount = 0;
		commentsCount = 0;
	}

	void ReadPostsFromFile(ifstream& fin)
	{
		fin >> postType;
		char temp[80];
		if (postType == 1)
		{
			fin >> temp;
			postID = Helper::GetStringFromBuffer(temp);
			SharedDate.ReadDateFromFile(fin);
			fin.ignore();
			fin.getline(temp, 80);
			text = Helper::GetStringFromBuffer(temp);

		}
		else if (postType == 2)
		{
			fin >> temp;
			postID = Helper::GetStringFromBuffer(temp);
			SharedDate.ReadDateFromFile(fin);
			fin.ignore();
			fin.getline(temp, 80);
			text = Helper::GetStringFromBuffer(temp);
			act = new Activity;
			act->ReadActivityFromFile(fin);
		}
		else
		{

		}
	}

	void SetSharedBy(Object* obj)
	{
		SharedBy = obj;
	}

	void SetLikedBy(Object* obj)
	{
		if (likedbyCount == 0)
		{
			this->likedBy = new Object * [10];
			for (int i = 0; i < 10; i++)
			{
				likedBy[i] = new Object;
				likedBy[i] = nullptr;
			}
		}
		likedBy[likedbyCount] = obj;
		likedbyCount++;
	}

	bool VerifyID(char* temp)
	{
		int i = 0, j = 0;
		bool flag = true;

		int len1 = Helper::StringLenght(temp);
		int len2 = Helper::StringLenght(SharedBy->GetID());

		if (len2 > len1)
		{
			while (temp[i] != '\0')
			{
				if (SharedBy->GetID()[i] == temp[i])
				{
					flag = true;
				}
				else
				{
					flag = false;
					break;
				}
				i++;
			}
		}
		else
		{
			while (temp[j] != '\0')
			{
				if (SharedBy->GetID()[j] == temp[j])
				{
					flag = true;
				}
				else
				{
					flag = false;
					break;
				}
				j++;
			}
		}
		return flag;
	}

	bool VerifyPost(char* temp)
	{
		int i = 0, j = 0;
		bool flag = true;

		int len1 = Helper::StringLenght(temp);
		int len2 = Helper::StringLenght(postID);

		if (len2 > len1)
		{
			while (temp[i] != '\0')
			{
				if (postID[i] == temp[i])
				{
					flag = true;
				}
				else
				{
					flag = false;
					break;
				}
				i++;
			}
		}
		else
		{
			while (temp[j] != '\0')
			{
				if (postID[j] == temp[j])
				{
					flag = true;
				}
				else
				{
					flag = false;
					break;
				}
				j++;
			}
		}
		return flag;
	}

	void AddComments(Comment* com)
	{
		if (commentsCount == 0)
		{
			this->comments = new Comment * [10];
			for (int i = 0; i < 10; i++)
			{
				comments[i] = new Comment;
				comments[i] = nullptr;
			}
		}
		comments[commentsCount] = com;
		commentsCount++;
	}

	virtual void PrintPost(bool flag)
	{
		if (postType == 2)
		{
			cout << endl << "---";
			SharedBy->PrintName();
			if (act->GetType() == 1)
			{
				cout << " is feeling " << act->GetValue() << endl;
			}
			else if (act->GetType() == 2)
			{
				cout << " is thinking about " << act->GetValue() << endl;
			}
			else if (act->GetType() == 3)
			{
				cout << " is making " << act->GetValue() << endl;
			}
			else if (act->GetType() == 4)
			{
				cout << " is celebrating " << act->GetValue() << endl;
			}
			else {}
			cout << "'" << text << "'" << endl;
		}
		else
		{
			cout << endl << "---";
			SharedBy->PrintName();
			cout << " shared " << text;
		}
		if (flag == true)
		{
			SharedDate.Print();
		}
		cout << endl;
		int i = 0;
		char* name;
		if (comments != NULL)
		{
			while (comments[i] != NULL)
			{
				cout << "\t\t";
				comments[i]->PrintName();
				cout << " wrote: " << comments[i]->GetCommentText() << endl << endl;
				i++;
			}
		}
	}

	void CommentOnPost(char* commentText, Object* obj)
	{

		comments[commentsCount] = new Comment;
		comments[commentsCount]->SetComment(commentText, obj);
		AddComments(comments[commentsCount]);

	}

	void ViewLikedByList()
	{
		int i = 0;
		cout << endl << "_________________________________________________________________________" << endl;
		cout << "Command:\t ViewLikedByList (" << postID << ")" << endl << endl;
		cout << endl << "-------------------------------------------------------------------------" << endl;
		cout << "Post liked by:" << endl;
		while (likedBy[i] != NULL)
		{
			likedBy[i]->PrintLikedBy();
			i++;
			cout << endl;
		}

	}

	void ViewPostComments()
	{
		cout << endl << "_________________________________________________________________________" << endl;
		cout << "Command:\t ViewPost (" << postID << ")" << endl << endl;
		cout << endl << "-------------------------------------------------------------------------" << endl;
		PrintPost(true);

	}

	void LikePost(Object* obj)
	{
		cout << endl << "_________________________________________________________________________" << endl;
		cout << "Command:\t LikePost (" << postID << ")" << endl << endl;
		cout << endl << "-------------------------------------------------------------------------" << endl;
		if (likedbyCount < 10)
		{
			likedBy[likedbyCount] = obj;
			likedbyCount++;
		}
	}

	void SetPost(char* temp, char* str, Post* post)
	{
		postType = 0;
		postID = Helper::GetStringFromBuffer(temp);
		text = Helper::GetStringFromBuffer(str);
		SharedBy = post->SharedBy;
		SharedDate.GetCurrentDate();
		comments = NULL;
		likedBy = NULL;
	}

	Date GetSharedDate()
	{
		if (this != NULL)
		{
			return SharedDate;
		}
		else
			return NULL;
	}

	void PrintMemory()
	{
		cout << "~~~~~";
		SharedBy->PrintName();
		cout << " shared a memory~~~~~" << endl;
		cout << text;
	}

	//Destructor
	virtual ~Post()
	{
		if (postID != NULL)
		{
			delete[] postID;
		}
		if (postType == 2 && act != NULL)
		{
			delete act;
		}
		else
		{
		}
		if (text != NULL)
		{
			delete text;
		}
		if (comments != NULL)
		{
			for (int i = 0; i < commentsCount; i++) {
				if (comments != 0)
					delete comments[i];
			}
			delete[]comments;
		}
		if (likedBy != NULL)
		{
			delete[]likedBy;
		}
	}
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// Memory CLASS //////////////////////////////////////////////////
class Memory :public Post
{
private:

	Post* prevPost;

public:

	Memory()
	{
		prevPost = NULL;
	}

	void SetPrevPost(Post* post)
	{
		prevPost = post;
	}




	void PrintYearsAgo(Date date)
	{
		cout << "(" << date.YearDifference(prevPost->GetSharedDate()) << " years ago" << ")" << endl;
	}

	void PrintPost(bool flag)
	{
		PrintMemory();
		Date date = GetSharedDate();
		date.Print();
		cout << endl;
		PrintYearsAgo(date);
		prevPost->PrintPost(true);
	}

	~Memory()
	{

	}
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// Page CLASS ////////////////////////////////////////////////////
class Page :public Object
{
	char* title;
	Post** Timeline;
	int TimelineCount;

public:

	Page()
	{
		title = NULL;
		Timeline = NULL;
		TimelineCount = 0;
	}

	void ReadPageFromFile(ifstream& fin)
	{
		char temp[50];
		fin >> temp;
		SetID(temp);
		fin.getline(temp, 50);
		title = Helper::GetStringFromBuffer(temp);
	}

	char* GetTitle()
	{
		return title;
	}

	void PrintName()
	{
		cout << title;
	}

	void SetTimeline(Post* post)
	{
		if (TimelineCount == 0)
		{
			this->Timeline = new Post * [10];
			for (int i = 0; i < 10; i++)
			{
				Timeline[i] = nullptr;
			}
		}
		Timeline[TimelineCount] = post;
		TimelineCount++;
	}

	void PrintTimeline()
	{
		cout << endl << "_________________________________________________________________________" << endl;
		cout << "Command:\t ViewTimeline" << endl;
		cout << endl << "-------------------------------------------------------------------------" << endl;
		PrintName();
		cout << "-Timeline" << endl << endl;
		cout << endl << "-------------------------------------------------------------------------" << endl;
		int i = 0;
		while (Timeline[i] != NULL)
		{
			Timeline[i]->PrintPost(true);
			i++;
		}


	}

	void PrintLikedBy()
	{
		cout << GetID() << "-";
		PrintName();
	}

	void PrintListView()
	{
		cout << GetID() << " - " << title << endl;
	}

	//Destructor
	~Page()
	{
		//cout << GetID() << " ~Page() called" << endl;
		if (title != NULL)
			delete[]title;
		if (Timeline != NULL)
		{
			Deallocation(Timeline);
		}
	}
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// USER CLASS ////////////////////////////////////////////////////
class User :public Object
{
	char* firstName;
	char* lastName;
	User** friendList;
	Page** likedpages;
	Post** Timeline;

	int pagesCount;
	int friendCount;
	int TimelineCount;
public:

	User()
	{
		firstName = NULL;
		lastName = NULL;
		friendList = NULL;
		likedpages = NULL;
		Timeline = NULL;
		pagesCount = 0;
		friendCount = 0;
		TimelineCount = 0;
	}

	void AddLikedPages(Page*& pages)
	{
		if (pagesCount == 0)
		{
			this->likedpages = new Page * [10];
			for (int i = 0; i < 10; i++)
			{
				likedpages[i] = nullptr;
			}
		}
		if (pages != NULL)
		{
			likedpages[pagesCount] = pages;
			pagesCount++;
		}
		else
		{
			likedpages = NULL;
		}
	}

	void LoadUserFromFile(ifstream& fin, char**& temp1)
	{
		char temp[30];
		fin >> temp;
		SetID(temp);
		fin >> temp;
		firstName = Helper::GetStringFromBuffer(temp);
		fin >> temp;
		lastName = Helper::GetStringFromBuffer(temp);

		int i = 0;

		fin >> temp;

		if (temp[0] != '-')
		{
			temp1 = new char* [10];
			for (int j = 0; j < 10; j++)
			{
				temp1[j] = nullptr;
			}
			while (temp[0] != '-')
			{
				temp1[i] = Helper::GetStringFromBuffer(temp);
				fin >> temp;
				i++;
			}
			temp1[i] = NULL;
		}
		else
		{
			temp1 = NULL;
		}

	}

	void AddFriends(User* friends)
	{
		if (friendCount == 0)
		{
			this->friendList = new User * [10];
			for (int i = 0; i < 10; i++)
			{
				friendList[i] = nullptr;
			}
		}
		if (friends != NULL)
		{
			friendList[friendCount] = friends;
			friendCount++;
		}
		else
		{
			friendList = NULL;
		}
	}


	void SeeMemories(Date date)
	{
		date.GetCurrentDate();
		cout << endl << "_________________________________________________________________________" << endl;
		cout << "Command:\t SeeYourMemories()" << endl << endl;
		cout << endl << "-------------------------------------------------------------------------" << endl;
		for (int i = 0; i < TimelineCount; i++)
		{
			if (Timeline[i]->GetSharedDate().IfAllowedInMemory(date) == true)
			{
				cout << "We hope you enjoy looking back and sharing your memories on Facebook,from the most recent to those long ago." << endl << endl;
				cout << "On this day" << endl;
				cout << date.YearDifference(Timeline[i]->GetSharedDate()) << " years ago" << endl;
				Timeline[i]->PrintPost(true);
			}
		}
	}

	void PrintLikedBy()
	{
		cout << GetID() << "-";
		PrintName();
	}

	void PrintListView()
	{
		cout << GetID() << " - " << firstName << " " << lastName << endl;
	}

	void PrintView()
	{
		cout << "Command:\tSet Current User " << this->GetID() << endl;
		cout << this->firstName << " " << this->lastName << " successfully set as current user" << endl << endl;

		cout << endl << "Command:\tView Friend List" << endl;
		cout << endl << "-------------------------------------------------------------------------" << endl;

		cout << this->firstName << " " << this->lastName << "-Friend List" << endl << endl;

		if (friendList != NULL)
			ViewFriendList();

		cout << endl << "-------------------------------------------------------------------------" << endl;
		cout << endl << "Command:\tView Liked Pages" << endl;
		cout << endl << "-------------------------------------------------------------------------" << endl;

		cout << this->firstName << " " << this->lastName << "-Liked Pages" << endl << endl;
		if (likedpages != NULL)
			ViewLikedPages();
		cout << endl << "-------------------------------------------------------------------------" << endl;
	}

	void ViewFriendList()
	{
		int i = 0;
		while (friendList[i] != NULL)
		{
			friendList[i]->PrintListView();
			i++;
		}
	}

	void ViewLikedPages()
	{
		int i = 0;
		while (likedpages[i] != NULL)
		{
			likedpages[i]->PrintListView();
			i++;
		}
	}

	Object** FriendsPagesList()
	{
		int i = 0, j = 0;

		if (friendList != NULL)
		{
			while (friendList[i] != NULL)
			{
				i++;
			}
		}

		if (likedpages != NULL)
		{
			while (likedpages[j] != NULL)
			{
				j++;
			}
		}

		Object** obj = new Object * [i + j + 1];

		for (int k = 0; k < i; k++)
		{
			obj[k] = new Object;
			obj[k] = friendList[k];
		}
		for (int k = 0; k < j; k++)
		{
			obj[i] = new Object;
			obj[i] = likedpages[k];
			i++;
		}
		obj[i] = NULL;

		return obj;
	}

	void PrintName()
	{
		cout << firstName << " " << lastName;
	}

	void SetTimeline(Post* post)
	{
		if (TimelineCount == 0)
		{
			this->Timeline = new Post * [10];
			for (int i = 0; i < 10; i++)
			{
				Timeline[i] = nullptr;
			}
		}

		Timeline[TimelineCount] = post;
		TimelineCount++;
	}

	void PrintTimeline()
	{
		cout << endl << "_________________________________________________________________________" << endl;
		cout << "Command:\t ViewTimeline" << endl;
		cout << endl << "-------------------------------------------------------------------------" << endl;
		PrintName();
		cout << "-Timeline" << endl << endl;
		cout << endl << "-------------------------------------------------------------------------" << endl;
		int i = 0;

		while (Timeline[i] != NULL)
		{
			Timeline[i]->PrintPost(true);
			i++;
		}
	}

	//Destructor
	~User()
	{
		//cout << GetID() << " ~User() called " << endl;

		if (firstName != NULL)
			delete[]firstName;

		if (lastName != NULL)
			delete[]lastName;

		if (friendList != NULL)
		{
			delete[]friendList;
		}
		if (likedpages != NULL)
		{
			delete[] likedpages;
		}
		if (Timeline != NULL)
		{
			Deallocation(Timeline);
		}
	}
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// Facebook CLASS ////////////////////////////////////////////////
class Facebook
{
	Page** pages;
	User** users;
	Post** posts;
	Comment** comments;
	static int totalPages;
	static int totalUsers;
	static int totalPosts;
	static int totalComment;
	static int usercount;
public:

	Facebook()
	{
		pages = NULL;
		users = NULL;
		posts = NULL;
		comments = NULL;
	}


	void LoadPages(ifstream& fin)
	{
		fin >> totalPages;
		pages = new Page * [totalPages + 1];
		int i = 0;
		for (i; i < totalPages; i++)
		{
			pages[i] = new Page;
			pages[i]->ReadPageFromFile(fin);
		}
		pages[i] = NULL;
	}

	void LoadUsers(ifstream& fin)
	{
		fin >> totalUsers;
		users = new User * [totalUsers + 1];

		char*** tempFriendID = new char** [20];


		char temp[10];
		char* tempPageID;

		Page* pg;

		int i = 0;
		for (i; i < totalUsers; i++)
		{
			//reading users
			users[i] = new User;
			users[i]->LoadUserFromFile(fin, tempFriendID[i]);

			//reading liked pages
			fin >> temp;
			while (temp[0] != '-')
			{
				tempPageID = Helper::GetStringFromBuffer(temp);
				pg = SearchPagebyID(tempPageID);
				users[i]->AddLikedPages(pg);
				delete[]tempPageID;

				fin >> temp;
			}
			usercount++;
		}

		User* friendptr;
		for (int i = 0; i < 20; i++)
		{
			if (tempFriendID[i] != NULL)
			{
				for (int j = 0; j < 10; j++)
				{
					if (tempFriendID[i][j] != NULL)
					{
						friendptr = SearchUserbyID(tempFriendID[i][j]);
						users[i]->AddFriends(friendptr);
					}
					else
					{
						break;
					}
				}
			}
		}

		users[i] = NULL;

		//Deallocating tempFriendID
		for (int i = 0; i < 20; i++)
		{
			delete tempFriendID[i];
		}
		delete[] tempFriendID;
	}

	void LoadPost(ifstream& fin)
	{
		int j = 0;
		fin >> totalPosts;
		posts = new Post * [totalPosts + 1];
		Object* obj;
		char temp[80];
		int i = 0;
		for (i; i < totalPosts; i++)
		{
			posts[i] = new Post;
			posts[i]->ReadPostsFromFile(fin);
			fin >> temp;
			// For SharedBy
			if (temp[0] == 'u')
			{
				obj = SearchUserbyID(temp);
				posts[i]->SetSharedBy(obj);
				obj->SetTimeline(posts[i]);
			}
			else if (temp[0] == 'p')
			{
				obj = SearchPagebyID(temp);
				posts[i]->SetSharedBy(obj);
				obj->SetTimeline(posts[i]);
			}
			else
			{
				obj = NULL;
			}


			//For LikedBy
			fin >> temp;
			if (temp[0] != '-')
			{
				if (temp[0] == 'u')
				{
					obj = SearchUserbyID(temp);
					posts[i]->SetLikedBy(obj);
				}
				else if (temp[0] == 'p')
				{
					obj = SearchPagebyID(temp);
					posts[i]->SetLikedBy(obj);
				}

				//fin >> temp;
				while (temp[0] != '-')
				{
					fin >> temp;
					if (temp[0] == 'u')
					{
						obj = SearchUserbyID(temp);
						posts[i]->SetLikedBy(obj);
					}
					else if (temp[0] == 'p')
					{
						obj = SearchPagebyID(temp);
						posts[i]->SetLikedBy(obj);
					}
					j++;
				}
			}
			else
			{
				obj = NULL;
			}
		}
		//posts[i] = NULL;
	}

	void LoadComments(ifstream& fin)
	{
		fin >> totalComment;
		Object* obj;
		Post* post;
		char temp[80];
		comments = new Comment * [totalComment + 1];
		int i = 0;
		for (i; i < totalComment; i++)
		{
			comments[i] = new Comment;
			comments[i]->ReadCommentsFromFile(fin);

			fin >> temp;
			post = SearchPostbyID(temp);
			post->AddComments(comments[i]);

			fin >> temp;
			if (temp[0] == 'u')
			{
				obj = SearchUserbyID(temp);
				comments[i]->AddCommentBy(obj);
			}
			else if (temp[0] == 'p')
			{
				obj = SearchPagebyID(temp);
				comments[i]->AddCommentBy(obj);
			}
			else
			{
				obj = NULL;
				comments[i]->AddCommentBy(obj);
			}

			comments[i]->ReadCommentTextFromFile(fin);
		}
		comments[i] = NULL;
	}

	//Search Functions
	User* SearchUserbyID(char* tempFriendID)
	{
		bool flag;
		for (int i = 0; i < 20; i++)
		{
			flag = Helper::Verify(tempFriendID, users[i]->GetID());
			if (flag == true)
			{
				return users[i];
				break;
			}
			else
			{
				continue;
			}
		}
		delete[] tempFriendID;
		return NULL;
	}

	Post* SearchPostbyID(char* temp)
	{
		bool flag;
		for (int i = 0; i < 11; i++)
		{
			flag = posts[i]->VerifyPost(temp);
			if (flag == true)
			{
				return posts[i];
				break;
			}
			else
			{
				continue;
			}
		}
		return NULL;
	}

	Page* SearchPagebyID(char* tempPageID)
	{
		bool flag, flag1 = false;
		for (int i = 0; i < 12; i++)
		{
			flag = Helper::Verify(tempPageID, pages[i]->GetID());
			if (flag == true)
			{

				return pages[i];
			}
			else
			{
				continue;
			}
		}
		return 0;
	}

	Post* FindSharedID(char* ID)
	{
		bool flag;
		for (int i = 0; i < 11; i++)
		{
			flag = posts[i]->VerifyID(ID);
			if (flag == true)
			{
				return posts[i];
				break;
			}
			else
			{
				continue;
			}
		}
		return NULL;
	}


	//Opening files
	void OpenPages(const char* fileName)
	{
		ifstream fin;
		fin.open(fileName);
		if (fin.is_open())
		{
			Facebook::LoadPages(fin);
			fin.close();
		}
		else
		{
			cout << "File is not open" << endl;
		}
	}

	void OpenComments(const char* fileName)
	{
		ifstream fin;
		fin.open(fileName);
		if (fin.is_open())
		{
			Facebook::LoadComments(fin);
			fin.close();
		}
		else
		{
			cout << "File is not open" << endl;
		}
	}

	void OpenUsers(const char* fileName)
	{
		ifstream fin;
		fin.open(fileName);
		if (fin.is_open())
		{
			Facebook::LoadUsers(fin);
			fin.close();
		}
		else
		{
			cout << "File is not open" << endl;
		}
	}

	void OpenPosts(const char* fileName)
	{
		ifstream fin;
		fin.open(fileName);
		if (fin.is_open())
		{
			Facebook::LoadPost(fin);
			fin.close();
		}
		else
		{
			cout << "File is not open" << endl;
		}
	}

	void LoadData(const char* fileName, const char* fileName2, const char* fileName3, const char* fileName4)
	{
		OpenPages(fileName);
		OpenUsers(fileName2);
		OpenPosts(fileName3);
		OpenComments(fileName4);
	}

	void SetSystemDate(Date date)
	{
		cout << "Command: \t Set current System Date";
		date.Print();
		cout << endl;
	}

	void Homepage(Object** obj, Object* current)
	{
		int i = 0;
		char* name;
		Post* post;
		cout << "Command:\t View Home" << endl;
		cout << endl << "-------------------------------------------------------------------------" << endl;
		current->PrintName();
		cout << " -HomePage" << endl;
		cout << endl << "-------------------------------------------------------------------------" << endl;

		Date currentdate(15, 11);
		currentdate.SetDate();
		bool flag;
		Date verify;
		while (obj[i] != NULL)
		{
			name = obj[i]->GetID();
			post = FindSharedID(name);
			verify = post->GetSharedDate();
			if (verify.GetDay() == NULL)
			{
				break;
			}
			flag = currentdate.CheckDate(post->GetSharedDate());
			if (post != NULL && flag != false)
			{
				post->PrintPost(false);
				cout << endl << endl;
			}
			i++;
		}
	}


	void PostComments(Object* current)
	{
		char str3[] = "post4";
		char commentText[] = " Good Luck for your Result";
		cout << endl << "_________________________________________________________________________" << endl;
		cout << "Command: \t PostComments(" << str3 << ", " << commentText << ")" << endl;
		cout << endl << "-------------------------------------------------------------------------" << endl;
		Post* pst3 = SearchPostbyID(str3);
		pst3->CommentOnPost(commentText, current);

		pst3->ViewPostComments();

	}

	void AddComment(Object* current)
	{
		char str10[] = "post8";
		char commentTxt[] = "Thanks for the wishes";
		cout << endl << "_________________________________________________________________________" << endl;
		cout << "Command: \t PostComments(" << str10 << ", " << commentTxt << ")" << endl;
		cout << endl << "-------------------------------------------------------------------------" << endl;
		Post* pst4 = SearchPostbyID(str10);
		pst4->CommentOnPost(commentTxt, current);
		pst4->ViewPostComments();
	}

	Memory* SetMemory(char* temp, char* str, Post* post)
	{
		Memory* memoryPtr = new Memory;
		memoryPtr->SetPost(temp, str, post);
		return memoryPtr;
	}

	void Run()
	{

		/////////Set System Date//////
		Date date(15, 11, 2017);
		SetSystemDate(date);
		Date::SetCurrentDate(15, 11, 2017);
		cout << "System Date: \t";
		Date::PrintCurrentDate();
		cout << endl << endl;



		///////// Set user//////////
		char str[] = "u7";
		User* current = SearchUserbyID(str);
		current->PrintView();


		//////////HomePage///////////
		cout << endl << "_________________________________________________________________________" << endl;
		cout << endl << "" << endl;
		Object** obj = current->FriendsPagesList();
		Homepage(obj, current);


		//////////View user Timeline////
		current->PrintTimeline();


		/////////View Liked List////////
		char str2[] = "post5";
		Post* post2 = SearchPostbyID(str2);
		post2->ViewLikedByList();


		/////////Like A Post///////////
		Object* obj2 = NULL;
		if (str[0] == 'p')
		{
			obj2 = SearchPagebyID(str);
		}
		else if (str[0] == 'u')
		{
			obj2 = SearchUserbyID(str);
		}
		else
		{
		}
		post2->LikePost(obj2);
		post2->ViewLikedByList();


		/////////View Post Comments///////
		PostComments(current);


		//////////Add Comment/////////////
		AddComment(current);

		///////////Share Memory///////////
		char temp[] = "post10";
		char text[] = "Never thought I will be specialist in this field...";
		Post* post3 = SearchPostbyID(temp);




		////////////See memory////////////
		current->SeeMemories(date);


		//////Timeline with shared memory////
		Memory* temp_memory = 0;
		temp_memory = SetMemory(temp, text, post3);
		temp_memory->SetPrevPost(post3);
		current->SetTimeline(temp_memory);
		current->PrintTimeline();


		///////////View page Timeline///////
		char str4[] = "p1";
		Page* currentPage = SearchPagebyID(str4);
		currentPage->PrintTimeline();
	}

	~Facebook()
	{
		//Destructor

		Deallocation(pages);
		Deallocation(users);

		delete[] comments;
		delete[] posts;
	}
};
int Facebook::totalPages = 0;
int Facebook::totalUsers = 0;
int Facebook::usercount = 0;
int Facebook::totalPosts = 0;
int Facebook::totalComment = 0;

int main()
{
	Facebook fb;

	fb.LoadData("Pages.txt", "Users.txt", "Post.txt", "Comments.txt");

	fb.Run();

	return 0;
}