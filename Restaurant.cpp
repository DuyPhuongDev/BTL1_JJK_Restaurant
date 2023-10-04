#include "main.h"

extern int MAXSIZE;
class imp_res : public Restaurant
{
	private:
		int size;
	public:	
		imp_res(): size(0) {};

		void RED(string name, int energy);
		void BLUE(int num);
		void PURPLE();
		void REVERSAL();
		void UNLIMITED_VOID();
		void DOMAIN_EXPANSION();
		void LIGHT(int num);
};

void imp_res::RED(string name, int energy){
	cout << name << " " << energy << endl;
	customer *cus = new customer (name, energy, nullptr, nullptr);
	if(energy>0){
		/* chú thuật sư */
	}else if(energy<0){
		/* oán linh */
	}else{
		// bo qua
	}
	cout<<MAXSIZE<<endl;
}

void imp_res::BLUE(int num){
	cout << "blue "<< num << endl;
}

void imp_res::PURPLE(){
	cout << "purple"<< endl;
}

void imp_res::REVERSAL(){
	cout << "reversal" << endl;
}

void imp_res::UNLIMITED_VOID(){
	cout << "unlimited_void" << endl;
}

void imp_res::DOMAIN_EXPANSION(){
	cout << "domain_expansion" << endl;
}

void imp_res::LIGHT(int num){
	cout << "light " << num << endl;
}