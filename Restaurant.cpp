#include "main.h"

// extern int MAXSIZE; // using global variable from others file
class imp_res : public Restaurant
{	
	private:
		int numOfCus;
		int numOfQueue;
		int sizelist=0;
		customer* h_queue;
		customer* t_queue;
		customer* h_list;
		customer* t_list;
		customer* x; // pos of cus has new change
	public:	

		imp_res(): numOfCus(0), numOfQueue(0), h_queue(nullptr), t_queue(nullptr), h_list(nullptr), t_list(nullptr), x(nullptr) {};

		/** METHOD HELPER **/
		bool prior(customer* a, customer* b);
		void InsertCustomerPrev(customer* curr, customer* customer);
		void InsertCustomerNext(customer* curr, customer* customer);
		void InsertQueue(customer* cus);
		void AddList(customer* cus);
		bool IsCusInRestaurant(string name);
		bool IsCusInQueue(string name);
		bool IsCusInList(string name);
		void removeCusInDesk(string name);
		void removecus(customer* &head, customer* &tail, customer* cus);
		int InsertionSort(customer* list, int size, int incr);
		int ShellSort(customer* list, int size);
		customer* get(customer* list, int index);
		customer* findPos(customer* customer);
		void SwapCustomerInDesk(customer* a, customer* b);
		void swapCus(customer* a, customer* b);
		void print();
		int indexOfCus(customer* cus);
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
	if(IsCusInQueue(cus->name)|| IsCusInRestaurant(cus->name) || !cus->energy) return;
	//int dem = MAXSIZE%2?MAXSIZE/2+1 : MAXSIZE/2;
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
	}else if(numOfQueue<MAXSIZE){
		this->InsertQueue(cus);
	}
	if(!IsCusInList(cus->name) && sizelist<MAXSIZE*2) AddList(cus);
}

void imp_res::BLUE(int num){
	cout << "blue "<< num << endl;
	if(num<=0) return;

	// delete cus from history list and table
	num = num>numOfCus? numOfCus:num;
	// for(int i=0; i<num;i++){
	// 	if(!this->x) return;
	// 	customer* cus = this->h_list;
	// 	this->removeCusInDesk(cus->name);
	// 	this->removecus(h_list,t_list,cus);
	// 	sizelist--;
	// }

	int count = 0;
	customer* p = h_list;
	while(p){
		if(count==num) break;
		if(IsCusInRestaurant(p->name)){
			this->removeCusInDesk(p->name);
			this->removecus(h_list,t_list,p);
			sizelist--;
			count++;
		}
		p=p->next;
	}

	// insert cus from queue to table and delete cus in queue
	num = num>numOfQueue? numOfQueue:num;
	for(int i=0;i<num;i++){
		if(!h_queue) return;
		customer* cur = this->h_queue;
		string name = cur->name; int energy = cur->energy;
		this->removecus(h_queue,t_queue,cur);
		this->numOfQueue--;
		this->RED(name, energy);
	}

}

void imp_res::PURPLE(){
	cout << "Purple"<< endl;
	// find pos customer has |E| MAX in queue
	if(!h_queue) return;
	int idx = 0;
	customer* maxEnergyCustomer = nullptr;
    customer* curr = h_queue;
    while (curr) {
        if (!maxEnergyCustomer || abs(curr->energy) > abs(maxEnergyCustomer->energy)
			|| (abs(curr->energy) == abs(maxEnergyCustomer->energy)) && indexOfCus(curr)>indexOfCus(maxEnergyCustomer)) {
            maxEnergyCustomer = curr;
        }
        curr = curr->next;
    }
	// lay size cua list can sort
	customer* p = h_queue;
	while(p){
		if(p==maxEnergyCustomer) break;
		p=p->next;
		idx++;
	}

	// sort by shellsort and return numofswap
	int numOfswap = ShellSort(h_queue,idx+1);
	cout<<"Num of Swap: "<<numOfswap<<endl;
	// Tiếp tục thực hiện BLUE < N mode MAXSIE>
	BLUE(numOfswap%MAXSIZE);
}

void imp_res::REVERSAL(){
	cout << "reversal" << endl;

	// dao nguoc oan linh
	if(this->x==nullptr || this->x->next==nullptr) return;
	customer* p = this->x;
	customer* q = this->x->next;
	// while(p!=q){
	// 	if(p->energy<0 && q->energy<0){
	// 		this->SwapCustomerInDesk(p,q);
	// 		if(q->next==p) break;
	// 		q = q->next;
	// 		p = p->prev;
	// 		if(q==p) break;
	// 	}else if(q->next==p) break;
		
	// 	if(p->energy>0) p = p->prev;
	// 	if(q->energy>0) q=q->next;
	// }

	// // dao nguoc chu thuat su
	customer* pre = this->x;
	customer* cur = this->x->next;
	// while(pre!=cur){
	// 	if(cur->energy>0 && pre->energy>0){
	// 		this->SwapCustomerInDesk(cur,pre);
	// 		if(cur->next==pre) break;
	// 		pre = pre->prev;
	// 		cur = cur->next;
	// 		if(cur==pre) break;
	// 	}else if(cur->next==pre) break;
		
	// 	if(cur->energy<0) cur=cur->next;
	// 	if(pre->energy<0) pre=pre->prev;
	// }

	int start = 0, end = numOfCus-1;
	while(start<end){
		if(p->energy<0 && q->energy<0){
			this->SwapCustomerInDesk(p,q);
			q = q->next;
			p = p->prev;
			start++;
			end--;
		}
		if(p->energy>0){p = p->prev; start++;}
		if(q->energy>0) {q=q->next; end--;}
	}

	int s=0,e=numOfCus-1;
	while(s<e){
		if(cur->energy>0 && pre->energy>0){
			this->SwapCustomerInDesk(cur,pre);
			pre = pre->prev;
			cur = cur->next;
			s++;
			e--;
		}
		
		if(cur->energy<0) {cur=cur->next; e--;}
		if(pre->energy<0) {pre=pre->prev; s++;}
	}
}

void imp_res::UNLIMITED_VOID() {
    cout << "unlimited_void" << endl;

    customer* start = x;
    customer* end = nullptr;
	customer* s = nullptr;
    int maxLength = 4;
    int minSum = 999999;

    while (start) {
        int currentLen = 0;
        int currentSum = 0;
        customer* curr = start;

        while (curr) {
            currentLen++;
            currentSum += curr->energy;

            if ((currentLen >= 4 && currentSum < minSum) || (currentLen >= maxLength && currentSum == minSum) ) {
				maxLength = currentLen;
                minSum = currentSum;
				s = start;
                end = curr;
            }

            curr = curr->next;
            if (curr == start) break;
        }

        start = start->next;
        if (start == x) break;
    }


	// find min element in sublist and print sublist begin minElement
	if(s && end){
		//find minElement
		customer* minElement = s;
		customer* p = s;
		while(true){
			if(p->energy<minElement->energy){
				minElement = p;
			}
			p=p->next;
			if(p==end->next) break;
		}

		// print from minElemt to end
		customer* cur = minElement;
		while(true){
			cur->print();
			cur = cur->next;
			if(cur==end->next) break;
		}
		// print from s to minElement
		customer* n = s;
		while(n!=minElement){
			n->print();
			n=n->next;
		}
	}
}

void imp_res::DOMAIN_EXPANSION(){
	cout << "domain_expansion" << endl;

	if(!h_list) return;

	int sumEinDesk = 0; // Tổng energy chú thuật sư
	int sumEinRes = 0; // Tổng trị tuyệt đối Energy của oán linh trong Res

	customer* p = h_list;
	while(p){
		if(p->energy<0) sumEinRes += abs(p->energy);
		else sumEinDesk += p->energy;
		p=p->next;
	}


	// print info customer was removed
	customer* n = t_list;
	int sizel =  sizelist;
	for(int i=0;i<sizel;i++){
		customer* tmp = nullptr;
		if((sumEinDesk>=sumEinRes && n->energy<0) || (sumEinDesk<sumEinRes && n->energy>0)){
			tmp = n;
			n->print();
		}
		n=n->prev;
		// xoa khoi list
		if(tmp){
			if(IsCusInQueue(tmp->name)){
				customer* cur = h_queue;
				int idx=0;
				while(cur){
					if(cur->name==tmp->name) break;
					cur=cur->next;
					idx++;
				}
				removecus(h_queue,t_queue,get(h_queue,idx));
				numOfQueue--;
			}
			if(IsCusInRestaurant(tmp->name)) removeCusInDesk(tmp->name);
			removecus(h_list,t_list,tmp);
			sizelist--;
		}
		
	}

	// Nếu vị trí trống => add to res from queue
	while(numOfCus<MAXSIZE && numOfQueue>0){
		if(!h_queue) return;
		customer* cus = this->h_queue;
		string name = cus->name; int energy = cus->energy;
		this->removecus(h_queue,t_queue,cus);
		this->RED(name, energy);
		this->numOfQueue--;
	}
}

void imp_res::LIGHT(int num){
	cout << "light " << num << endl;
	if(!num){
		if(!h_queue) return;
		customer* curr = h_queue;
		while(curr){
			curr->print();
			curr = curr->next;
		}
	}else{
		if(!this->x) return;
		customer* cur = this->x;
		do{
			cur->print();
			cur = num>0? cur->next:cur->prev;
		}while(cur!=this->x);
	}
}

/** METHOD HELPER **/

void imp_res::print(){
	customer* curr = this->x;
	cout<<"Table: ";
	if(!this->x) cout<<"null ";
	else{
		do{
			cout<<"["<<curr->name<<" "<<curr->energy<<"] ";
			curr = curr->next;
		}while(curr!=this->x);
	}
	cout<<numOfCus<<endl;

	cout<<"Queue: ";
	if(!h_queue) cout<<"null ";
	else{
		customer* p = h_queue;
		while(p){
			cout<<"["<<p->name<<" "<<p->energy<<"] ";
			p = p->next;
		}
	}
	cout<<numOfQueue<<endl;

	cout<<"List: ";
	if(!h_list) cout<<"null ";
	else{
		customer* n = h_list;
		while(n){
			cout<<"["<<n->name<<" "<<n->energy<<"] ";
			n = n->next;
		}
	}
	cout<<sizelist<<endl;
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
	int RES = -999999;
	Restaurant::customer* posCus = nullptr;
	Restaurant::customer* curr = this->x;
	do{
		if(abs(customer->energy - curr->energy)>RES){
			posCus = curr;
			RES = abs(customer->energy-curr->energy);
		}
		curr=curr->next;
	}while(curr!=this->x);
	return posCus;
}

void imp_res::InsertQueue(customer* customer){
	if(!h_queue) {t_queue = customer; h_queue = t_queue;}
	else{
		t_queue->next = customer;
		customer->prev = t_queue;
		t_queue = t_queue->next;
	}
	numOfQueue++;
}

bool imp_res::IsCusInRestaurant(string name){
	if(this->x){
		customer* curr = this->x;
		do{
			if(curr->name == name) return true;
			curr = curr->next;
		}while(curr!=this->x);
	}
	return false;
}

bool imp_res::IsCusInQueue(string name){
	if(h_queue){
		customer* curr = h_queue;
		while(curr){
			if(curr->name == name) return true;
			curr = curr->next;
		}
	}
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
	sizelist++;
}

void imp_res::removeCusInDesk(string name){
	customer* curr = this->x;
	do{
		if(curr->name == name){
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

Restaurant::customer* imp_res::get(customer* list, int index){
	int idx = 0;
	customer* curr = list;
	while(curr){
		if(idx == index) return curr;
		curr = curr->next;
		idx++;
	}
	return nullptr;
}

int imp_res::InsertionSort(customer* list, int n, int incr){
	// Sắp xếp giảm dần |E| của sublist
	int count = 0; // num of swap
	for(int i = incr; i<n; i+=incr){
		for(int j = i; (j>=incr) && prior(get(list,j),get(list,j-incr)); j-=incr){
			// swap
			this->swapCus(get(list,j), get(list,j-incr));
			count++;
		}
	}
	cout<<count<<endl;
	return count;

}

int imp_res::ShellSort(customer* list, int size){
	int count = 0;
	for(int i=size/2; i>2; i/=2){
		for(int j=0; j<i; j++){
			customer* l = get(h_queue,j);
			count+=InsertionSort(l,size-j,i);
		}
	}
	count+=InsertionSort(h_queue, size, 1);
	return count;

}

void imp_res::SwapCustomerInDesk(customer* a, customer* b){
	if(!a || !b || a==b) return;

	string name = a->name; int e = a->energy;

	a->name = b->name;
	a->energy = b->energy;

	b->name = name;
	b->energy = e;
    
    // Update the head pointer if necessary
    if (this->x == a)
        this->x = b;
    else if (this->x == b)
        this->x = a;
}

void imp_res::swapCus(customer* a, customer* b){
	string name = a->name;
	int e = a->energy;

	a->name = b->name;
	a->energy = b->energy;
	b->name = name;
	b->energy = e;
}

void imp_res::removecus(customer* &head, customer* &tail, customer* cus){
	if(!cus || !head) return;
	
	if(head==tail) { head=nullptr; tail=nullptr;}
	else if(cus==head){
		head = head->next;
		head->prev =nullptr;
	}else if(cus == tail){
		tail = tail->prev;
		tail->next = nullptr;
	}else{
		cus->prev->next = cus->next;
		cus->next->prev = cus->prev;
	}

	delete cus;
}

bool imp_res::IsCusInList(string name){
	if(h_list){
		customer* curr = h_list;
		while(curr){
			if(curr->name == name) return true;
			curr = curr->next;
		}
	}
	return false;
}

int imp_res::indexOfCus(customer* cus){
	if(h_list){
		customer* cur = h_list;
		int idx = 0;
		while(cur){
			if(cus->name == cur->name) return idx;
			cur = cur->next;
			idx++;
		}
	}
	return -1;
}

bool imp_res::prior(customer* a, customer* b){
	if(abs(a->energy) > abs(b->energy)) return true;
	if((abs(a->energy) == abs(b->energy)) && indexOfCus(a)<indexOfCus(b)) return true;
	return false;
}