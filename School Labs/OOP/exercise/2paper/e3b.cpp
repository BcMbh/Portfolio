#include <iostream>
#include <string>
using namespace std;
class HumanBody
{
	protected:
		string name;
		float height, weight;
	public:
		virtual void display()
		{
			cout << "Name           : " << name << endl;
			cout << "Height (meter) : " << height << endl;
			cout << "Weight (kg)    : " << weight << endl;
		}
				
		virtual ~HumanBody()
		{  cout<<"Destruct base"<<endl;
		}
};

class BMI : public HumanBody
{
	private:
		float bm;
	public:
		BMI(string nm, float wg, float hg) 
		{ 
			bm = 0.0;
			name=nm;
			height=hg;
			weight=wg;
		}
		float calcBMI()
		{
			bm = weight / (height * height);
			return bm;
		}
		
		void display()
		{
			cout << "~Name           : " << name << endl;
			cout << "~Height (meter) : " << height << endl;
			cout << "~Weight (kg)    : " << weight << endl;
			cout << "~BMI            : " << calcBMI()<<endl;
		}
		
		~BMI()
		{  cout<<"Destruct Derived"<<endl;
		}
};

int main()
{	HumanBody *hm = new BMI("Dory Lee", 45, 1.6);
	hm->display();
	delete hm;
	return 0;
}
