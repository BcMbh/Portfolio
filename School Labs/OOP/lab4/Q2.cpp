#include<iostream>
#include<iomanip>
#include<cstring>
using namespace std;
 
//define class
class Trivia
{ 	private: //private data members
		string name, country, game_name;
		int age;
		float score[3];
		char status [20];
	public: //public member functions
		void setParticipant() //set user input data to variables
		{ 	
			cin.ignore(); //ignore or clear one or more characters from the input buffer
			cout<<"\nEnter Name\t: ";
			getline(cin,name); //set input to string variable (will have bug if buffer not cleared)
			cout<<"Enter Country\t: ";
			getline(cin, country);
			cout<<"Enter Age\t: ";
			cin>>age;
			cin.ignore(); //ignore or clear one or more characters from the input buffer
			cout<<"Enter Game Name : ";
			getline(cin, game_name);
		}
	// a) void score_Gained() function
		void score_Gained() //prompt user to input scores for 3 series of quizzes
		{
			for(int i=0;i<3;i++) //loop to store input in score array
			{
				cout<<setw(14)<<"Enter Score "<<i+1<<" : ";
				cin>>score[i];
			}
		}
	// b) void average_Val() function
		void average_Val() //function to calculate total then average of 3 quizzes
		{
			double total = 0, average; //initialize appropriate variables
			for(int i=0;i<3;i++) //loop to accumulate total score
			{
				total += score[i];
			}
			average = total/3; //calculate average score
			set_status(average); //pass average value into function
		}
		//function to set status string to variable based on average value
		void set_status (double avg)
		{
			if (avg >= 80 && avg <= 100)
			strcpy(status , "Excellent");
			else if (avg >= 60 && avg < 80)
			strcpy(status , "Great");
			else
			strcpy(status , "Keep Trying");
		}
	// c) void display_result() function
		void display_result() //function to display details, scores, and status
		{
			cout<<"\n------------------------------"<<endl;
			cout<<"	RESULT SCORED"<<endl;
			cout<<"------------------------------"<<endl;
			cout<<"Name \t  : "<<name<<endl;
			cout<<"Country"<<setw(5)<<": "<<country<<endl;
			cout<<"Age \t  : "<<age<<endl;
			cout<<"Game Name : "<<game_name<<endl;
			for(int i=0;i<3;i++) //loop to print each score
			{
				cout<<setw(9)<<"Score "<<i+1<<": "<<score[i]<<endl;
			}
			cout<<"Status"<<setw(6)<<": "<<status<<endl;
		}
};

int main()
{
// d) Write the codes based on the requirements as stated below
	//declare variable
	int noWar;
	//get user input on how many warriors
	cout<<"How many warrior? ";
	cin>>noWar;
	//declare Trivia class object and pointer object
	Trivia TV, *TV1;
	//Make pointer to point to object using address
	TV1 = &TV;
	//for loop to loop over number of warriors
	for(int i=0;i<noWar;i++)
	{
		//call object functions using pointer
		TV1->setParticipant();
		TV1->score_Gained();
		TV1->average_Val();
		TV1->display_result();
	}
}