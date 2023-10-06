#include "main.h"

// extern int MAXSIZE; // using global variable from others file
class imp_res : public Restaurant
{	
	private:
		int numOfCus;
		int numOfQueue;
		customer* customers;
		customer* h_queue;
		customer* t_queue;
		customer* h_list;
		customer* t_list;
		customer* x; // pos of cus has new change
	public:	

		imp_res(): numOfCus(0), numOfQueue(0), customers(nullptr), h_queue(nullptr), t_queue(nullptr), h_list(nullptr), t_list(nullptr), x(nullptr) {};

		/** METHOD HELPER **/
		void InsertCustomerPrev(customer* curr, customer* customer);
		void InsertCustomerNext(customer* curr, customer* customer);
		void InsertQueue(customer* cus);
		void AddList(customer* cus);
		bool IsCusInRestaurant(customer* cus);
		bool IsCusInQueue(customer* cus);
		void removeCus(customer* cus);
		void InsertionSort(customer* list);
		void ShellSort(customer* list);
		customer* findPos(customer* customer);
		void print();
		/** METHOD IMPLIMENT**/
		void RED(string name, int energy);
		void BLUE(int num);
		void PURPLE();
		void REVERSAL();
		void UNLIMITED_VOID();
		void DOMAIN_EXPANSION();
		void LIGHT(int num);
};

/** METHOD IMPLIMENT**/
void imp_res::RED(string name, int energy){
	cout << name << " " << energy << endl;
	customer *cus = new customer (name, energy, nullptr, nullptr); //(name,energy,prev,next)
	if(cus->energy){
		if(numOfCus<MAXSIZE && !IsCusInRestaurant(cus)){
			if(!customers){
				customers = cus;
				customers->prev = customers;
				customers->next = customers;
				this->x = customers;
				numOfCus++;
			}else if(numOfCus<MAXSIZE/2){
				cus->energy>=x->energy? InsertCustomerNext(this->x,cus):InsertCustomerPrev(this->x,cus);
			}
			else{
				(cus->energy-findPos(cus)->energy<0)? InsertCustomerPrev(findPos(cus),cus):InsertCustomerNext(findPos(cus),cus);
			}
			this->AddList(cus); // historylist cus in restaurant
		}else if(numOfQueue<MAXSIZE && (!IsCusInQueue(cus) || !IsCusInRestaurant(cus))){
			this->InsertQueue(cus);
		}
	}
}

void imp_res::BLUE(int num){
	cout << "blue "<< num << endl;
	if(num<=0) return;
	num = num>MAXSIZE? MAXSIZE:num;
	int count = num;
	while(num){
		customer* cus = this->h_list;
		this->removeCus(cus);
		h_list->next->prev = nullptr;
		h_list=h_list->next;
		delete cus;
		num--;
	}
	while(count){
		customer* cus = this->h_queue;
		this->RED(cus->name, cus->energy);
		h_queue->next->prev = nullptr;
		h_queue = h_queue->next;
		delete cus;
		this->numOfQueue--;
		count--;
	}
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
	int sumEinDesk = 0; // Tổng energy chú thuật sư trên bàn ăn
	int sumEinRes = 0; // Tổng trị tuyệt đối Energy của oán linh trong Res

	customer* curr = customers;
	do{
		if(curr->energy>0) sumEinDesk += curr->energy;
		else sumEinRes += abs(curr->energy);
		curr = curr->next;
	}while(curr->next!=customers);

	customer* cur_q = h_queue;
	while(cur_q){
		if(cur_q->energy<0) sumEinRes += abs(cur_q->energy);
		cur_q = cur_q->next;
	}

	// remove customer
	customer* p = customers;
	do{
		if((sumEinDesk>=sumEinRes && p->energy<0) || (sumEinDesk<sumEinRes && p->energy>0)){
			p->prev->next = p->next;
			p->next->prev = p->prev;
			this->x = p->energy>0?  p->next: p->prev; // set x is new change
			delete p;
			numOfCus--;
		}
		p=p->next;
	}while(p->next!=customers);

	customer* q = h_queue;
	while(q){
		if((sumEinDesk>=sumEinRes && p->energy<0) || (sumEinDesk<sumEinRes && p->energy>0)){
			p->prev->next = p->next;
			p->next->prev = p->prev;
			this->x = p->energy>0?  p->next: p->prev; // set x is new change
			delete p;
			numOfQueue--;
		}
		p=p->next;
	}


	// print info customer was removed
	customer* n = t_list;
	while(n){
		if((sumEinDesk>=sumEinRes && p->energy<0) || (sumEinDesk<sumEinRes && p->energy>0)){
			cout<<n->name<<"-"<<n->energy<<"\n";
			// xoa khoi list
			if(n==t_list){
				n->prev->next = nullptr;
				t_list = n->prev;
			}else if(n==h_list) h_list = t_list = nullptr;
			 else{
				n->prev->next = n->next;
				n->next->prev = n->prev;
			}
		}
		n=n->prev;
		delete n;
	}

	// Nếu vị trí trống => add to res from queue
	while(numOfCus<MAXSIZE && numOfQueue>0){
		customer* cus = this->h_queue;
		this->RED(cus->name, cus->energy);
		h_queue->next->prev = nullptr;
		h_queue = h_queue->next;
		delete cus;
		this->numOfQueue--;
	}
}

void imp_res::LIGHT(int num){
	cout << "light " << num << endl;
	if(!num){
		customer* curr = h_queue;
		while(curr){
			cout<<curr->name<<"-"<<curr->energy<<endl;
			curr = curr->next;
		}
	}else{
		customer* cur = this->x;
		do{
			cout<<cur->energy<<"-"<<cur->energy<<endl;
			cur = num>0? cur->next:cur->prev;
		}while(cur->next!=this->x);
	}
}

/** METHOD HELPER **/

void imp_res::print(){
	customer* curr = customers;
	do{
		cout<<"["<<curr->name<<" "<<curr->energy<<"] ";
		curr = curr->next;
	}while(curr->next!=customers);
	cout<<numOfCus<<endl;
}

void imp_res::InsertCustomerPrev(customer* curr, customer* customer){
	if(!this->customers) return;
	customer->prev = curr->prev;
	customer->next = curr;
	curr->prev->next = customer;
	curr->prev = customer;
	curr = customer;
	numOfCus++;
}

void imp_res::InsertCustomerNext(customer* curr, customer* customer){
	if(!this->customers) return;
	customer->next = curr->next;
	customer->prev = curr;
	curr->next->prev = customer;
	curr->next = customer;
	curr = customer;
	this->numOfCus++;
}

Restaurant::customer* imp_res::findPos(Restaurant::customer* customer){
	int RES = INT_MIN;
	Restaurant::customer* posCus = nullptr;
	Restaurant::customer* curr = customers;
	do{
		if(abs(customer->energy - curr->energy)>RES){
			posCus = curr;
			RES = abs(customer->energy-curr->energy);
		}
	}while(curr->next!=customers);
	return posCus;
}

void imp_res::InsertQueue(customer* customer){
	if(!h_queue) {h_queue = customer; t_queue = h_queue;}
	else{
		t_queue->next = customer;
		customer->prev = t_queue;
		t_queue = t_queue->next;
	}
	numOfQueue++;
}

bool imp_res::IsCusInRestaurant(customer* cus){
	customer* curr = customers;
	do{
		if(cus->name == curr->name) return true;
		curr = curr->next;
	}while(curr->next!=customers);
	return false;
}

bool imp_res::IsCusInQueue(customer* cus){
	customer* curr = h_queue;
	do{
		if(cus->name == curr->name) return true;
		curr = curr->next;
	}while(curr->next!= h_queue);
	return false;
}

void imp_res::AddList(customer* cus){
	if(!h_list){
		h_list = cus;
		t_list = h_list;
	}else{
		t_list->next = cus;
		cus->prev = t_list;
		t_list = t_list->next;
	}
}

void imp_res::removeCus(customer* cus){
	customer* curr = customers;
	do{
		if(cus->name == curr->name){
			curr->prev->next = curr->next;
			curr->next->prev = curr->prev;
			this->x = curr->energy>0?  curr->next: curr->prev; // set x is new change
			delete curr;
			this->numOfCus--;
		}
		curr = curr->next;
	}while(curr->next!=customers);
}

void imp_res::InsertionSort(customer* list){

}