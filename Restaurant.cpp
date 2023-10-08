#include "main.h"

// extern int MAXSIZE; // using global variable from others file
class imp_res : public Restaurant
{	
	private:
		int numOfCus;
		int numOfQueue;
		customer* h_queue;
		customer* t_queue;
		customer* h_list;
		customer* t_list;
		customer* x; // pos of cus has new change
	public:	

		imp_res(): numOfCus(0), numOfQueue(0), h_queue(nullptr), t_queue(nullptr), h_list(nullptr), t_list(nullptr), x(nullptr) {};

		/** METHOD HELPER **/
		void InsertCustomerPrev(customer* curr, customer* customer);
		void InsertCustomerNext(customer* curr, customer* customer);
		void InsertQueue(customer* cus);
		void AddList(customer* cus);
		bool IsCusInRestaurant(string name);
		bool IsCusInQueue(string name);
		void removeCus(customer* cus);
		int InsertionSort(customer* list, int size, int incr);
		int ShellSort(customer* list, int size);
		customer* get(customer* cus, int index);
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
	//cout << name << " " << energy << endl;
	customer *cus = new customer (name, energy, nullptr, nullptr); //(name,energy,prev,next)
	if(cus->energy){
		//if(IsCusInQueue(cus->name)|| IsCusInRestaurant(cus->name)) return;
		if(numOfCus<MAXSIZE){
			if(!this->x){
				this->x = cus;
				this->x->prev = this->x;
				this->x->next = this->x;
				numOfCus++;
			}else if(numOfCus<MAXSIZE/2){
				cus->energy>=x->energy? InsertCustomerNext(this->x,cus):InsertCustomerPrev(this->x,cus);
			}
			else{
				(cus->energy-findPos(cus)->energy<0)? InsertCustomerPrev(findPos(cus),cus):InsertCustomerNext(findPos(cus),cus);
			}
			this->AddList(cus); // historylist cus in restaurant
		}else if(numOfQueue<MAXSIZE){
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
		cus->next->prev = nullptr;
		h_list = cus->next;
		cus->next = nullptr;
		delete cus;
		num--;
	}
	if(!h_queue) return;
	while(count){
		customer* cus = this->h_queue;
		this->RED(cus->name, cus->energy);
		cus->next->prev = nullptr;
		h_queue = cus->next;
		cus->next = nullptr;
		delete cus;
		this->numOfQueue--;
		count--;
	}
}

void imp_res::PURPLE(){
	cout << "purple"<< endl;
	// find pos customer has |E| MAX in queue
	if(!h_queue) return;
	int idx = 0;
	customer* maxEnergyCustomer = nullptr;
    customer* curr = h_queue;
    while (curr) {
        if (!maxEnergyCustomer || abs(curr->energy) >= abs(maxEnergyCustomer->energy)) {
            maxEnergyCustomer = curr;
        }
        curr = curr->next;
    }
	// lay size cua list can sort
	customer* p = h_queue;
	while(p){
		if(p==curr) break;
		p=p->next;
		idx++;
	}

	// sort by shellsort and return numofswap
	int numOfswap = ShellSort(h_queue,idx+1);
	// Tiếp tục thực hiện BLUE < N mode MAXSIE>
	BLUE(numOfswap%MAXSIZE);
}

void imp_res::REVERSAL(){
	cout << "reversal" << endl;
	string tmp = this->x->name;
	// dao nguoc oan linh
	customer* p = this->x;
	customer* q = this->x->next;
	while(p!=q){
		if(p->energy<0 && q->energy<0){
			swap(p->name,q->name);
			swap(p->energy, q->energy);
			if(q->next==p) break;
			q = q->next;
			p = p->prev;
		}
		if(p->energy>0) p = p->prev;
		if(q->energy>0) q=q->next;
	}

	// dao nguoc chu thuat su
	customer* pre = this->x;
	customer* cur = this->x->next;
	while(pre!=cur){
		if(cur->energy>0 && pre->energy){
			swap(cur->energy,pre->energy);
			swap(cur->name,pre->name);
			if(cur->next!=pre) break;
			pre = pre->prev;
			cur = cur->next;
		}
		if(cur->energy<0) cur=cur->next;
		if(pre->energy<0) pre=pre->prev;
	}
}

void imp_res::UNLIMITED_VOID(){
	cout << "unlimited_void" << endl;
}

void imp_res::DOMAIN_EXPANSION(){
	cout << "domain_expansion" << endl;
	int sumEinDesk = 0; // Tổng energy chú thuật sư trên bàn ăn
	int sumEinRes = 0; // Tổng trị tuyệt đối Energy của oán linh trong Res
	if(!this->x) return;
	customer* curr = this->x;
	do{
		if(curr->energy>0) sumEinDesk += curr->energy;
		else sumEinRes += abs(curr->energy);
		curr = curr->next;
	}while(curr!=this->x);

	if(!h_queue){
		customer* cur_q = h_queue;
		while(cur_q){
			if(cur_q->energy<0) sumEinRes += abs(cur_q->energy);
			cur_q = cur_q->next;
		}
	}

	// remove customer
	customer* p = this->x;
	do{
		customer* tmp = nullptr;
		if((sumEinDesk>=sumEinRes && p->energy<0) || (sumEinDesk<sumEinRes && p->energy>0)){
			p->prev->next = p->next;
			p->next->prev = p->prev;
			this->x = p->energy>0?  p->next: p->prev; // set x is new change
			tmp = p;
		}
		p=p->next;
		if(tmp){
			tmp->next = nullptr;
			tmp->prev = nullptr;
			delete tmp;
			numOfCus--;
		}
	}while(p!=this->x);

	customer* q = h_queue;
	while(q){
		customer* tmp =  nullptr;
		if((sumEinDesk>=sumEinRes && p->energy<0) || (sumEinDesk<sumEinRes && p->energy>0)){
			p->prev->next = p->next;
			p->next->prev = p->prev;
			this->x = p->energy>0?  p->next: p->prev; // set x is new change
			tmp = p;
		}
		p=p->next;
		if(tmp){
			tmp->next = nullptr;
			tmp->prev = nullptr;
			delete tmp;
			numOfQueue--;
		}
	}


	// print info customer was removed
	customer* n = t_list;
	while(n){
		customer* tmp = nullptr;
		if((sumEinDesk>=sumEinRes && n->energy<0) || (sumEinDesk<sumEinRes && n->energy>0)){
			cout<<n->name<<"-"<<n->energy<<"\n";
			// xoa khoi list
			tmp = n;
			if(n==t_list){
				t_list = t_list->prev;
			}else if(n==h_list){
				h_list = h_list->next;
				h_list->prev = nullptr;
			}
			 else{
				n->prev->next = n->next;
				n->next->prev = n->prev;
			}
		}
		n=n->prev;
		if(tmp){
			tmp->next = nullptr;
			tmp->prev = nullptr;
			delete tmp;
		}
	}

	// Nếu vị trí trống => add to res from queue
	while(numOfCus<MAXSIZE && numOfQueue>0){
		customer* cus = this->h_queue;
		this->RED(cus->name, cus->energy);
		h_queue->next->prev = nullptr;
		h_queue = h_queue->next;
		cus->prev = nullptr;
		cus->next = nullptr;
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
			cout<<cur->name<<"-"<<cur->energy<<endl;
			cur = num>0? cur->next:cur->prev;
		}while(cur!=this->x);
	}
}

/** METHOD HELPER **/

void imp_res::print(){
	customer* curr = this->x;
	do{
		cout<<"["<<curr->name<<" "<<curr->energy<<"] ";
		curr = curr->next;
	}while(curr!=this->x);
	cout<<numOfCus<<endl;
}

void imp_res::InsertCustomerPrev(customer* curr, customer* customer){
	if(!this->x) return;
	customer->prev = curr->prev;
	customer->next = curr;
	curr->prev->next = customer;
	curr->prev = customer;
	this->x = customer;
	numOfCus++;
}

void imp_res::InsertCustomerNext(customer* curr, customer* customer){
	if(!this->x) return; // x=null nothings
	customer->next = curr->next;
	customer->prev = curr;
	curr->next->prev = customer;
	curr->next = customer;
	this->x = customer;
	this->numOfCus++;
}

Restaurant::customer* imp_res::findPos(Restaurant::customer* customer){
	int RES = INT_MIN;
	Restaurant::customer* posCus = nullptr;
	Restaurant::customer* curr = this->x;
	do{
		if(abs(customer->energy - curr->energy)>RES){
			posCus = curr;
			RES = abs(customer->energy-curr->energy);
		}
	}while(curr!=this->x);
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

bool imp_res::IsCusInRestaurant(string name){
	customer* curr = this->x;
	do{
		if(curr->name == name) return true;
		curr = curr->next;
	}while(curr!=this->x);
	return false;
}

bool imp_res::IsCusInQueue(string name){
	customer* curr = h_queue;
	do{
		if(curr->name == name) return true;
		curr = curr->next;
	}while(curr!= h_queue);
	return false;
}

void imp_res::AddList(customer* cus){
	customer* tmp = new customer(cus->name,cus->energy,nullptr,nullptr);
	if(!h_list){
		h_list = tmp;
		t_list = h_list;
	}else{
		t_list->next = tmp;
		tmp->prev = t_list;
		t_list = t_list->next;
	}
}

void imp_res::removeCus(customer* cus){
	customer* curr = this->x;
	do{
		if(cus->name == curr->name){
			curr->prev->next = curr->next;
			curr->next->prev = curr->prev;
			this->numOfCus--;
			break;
		}
		curr = curr->next;
	}while(curr!=this->x);

	if(numOfCus==0) this->x = nullptr;
	else this->x = curr->energy>0?  curr->next: curr->prev; // set x is new change
	curr->prev = nullptr;
	curr->next = nullptr;
	delete curr;
}

int imp_res::InsertionSort(customer* list, int n, int incr){
	// Sắp xếp giảm dần |E| của sublist
	int count = 0; // num of swap
	for(int i = incr; i<n; i+=incr){
		for(int j = i; (j>=incr) && (abs(get(h_queue,j)->energy>abs(get(h_queue,j-incr)->energy))); j-=incr){
			// swap
			swap(get(h_queue,j)->name, get(h_queue,j-incr)->name);
			swap(get(h_queue,j)->energy,get(h_queue,j-incr)->energy);
			count++;
		}
	}
	return count;
}

Restaurant::customer* imp_res::get(customer* cus, int index){
	int idx = 0;
	customer* curr = h_queue;
	while(curr){
		if(idx == index) return curr;
		curr = curr->next;
		idx++;
	}
}

int imp_res::ShellSort(customer* list, int size){
	int count = 0;
	for(int i=size/2; i>2; i/=2){
		for(int j=0; j<i; j++){
			count+=InsertionSort(get(h_queue,j),size-j,i);
		}
	}
	count+=InsertionSort(h_queue, size, 1);
	return count;
}