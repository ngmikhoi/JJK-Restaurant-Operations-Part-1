#include "main.h"


class imp_res : public Restaurant
{
public:
    struct Node{
        Node* next;
        Node* prev;
        customer* data;
        int order;
        Node* come;
        bool eating;
    };
    Node* come1st;
    Node* comeLast;
    customer* X;
    Node* enjoy1st;
    Node* enjoyLast;
    int numCus;
    Node* front;
    Node* rear;
    int numQueue;
    imp_res() {
        X = nullptr;
        numCus = 0;
        front = nullptr;
        rear = nullptr;
        numQueue = 0;
        come1st = nullptr;
        comeLast = nullptr;
        enjoy1st = nullptr;
        enjoyLast = nullptr;
    }
    ~imp_res(){
        if(X!=nullptr){
            customer* c=X->next;
            if(c!=nullptr){
                while(c!=X){
                    customer* tmp = c;
                    c=c->next;
                    delete tmp;
                }
            }
            delete X;
        }
        while(come1st!=nullptr){
            Node* tmp = come1st;
            come1st=come1st->next;
            delete tmp;
        }
        while(enjoy1st!=nullptr){
            Node* tmp = enjoy1st;
            enjoy1st=enjoy1st->next;
            delete tmp;
        }
        while(front!=nullptr){
            Node* tmp = front;
            front=front->next;
            delete tmp;
        }
        X = nullptr;
        numCus = 0;
        front = nullptr;
        rear = nullptr;
        numQueue = 0;
        come1st = nullptr;
        comeLast = nullptr;
        enjoy1st = nullptr;
        enjoyLast = nullptr;
    }
    void RED(string name, int energy)
    {
//			cout << name << " " << energy << endl;
        customer* cus = new customer (name, energy, nullptr, nullptr);
        if(cus->energy==0){
            delete cus;
            return;
        }
        if(enjoy1st!=nullptr){
            Node* check = enjoy1st;
            while(check!=nullptr){
                if(cus->name==check->data->name){
                    delete cus;
                    return;
                }
                check=check->next;
            }
        }
        if(front!=nullptr){
            Node* check = front;
            while(check!=nullptr){
                if(cus->name==check->data->name){
                    delete cus;
                    return;
                }
                check=check->next;
            }
        }
        if(numCus<MAXSIZE || numQueue<MAXSIZE){
            if(numCus==0 && numQueue==0){
                come1st = new Node;
                come1st->data = cus;
                come1st->prev = nullptr;
                come1st->next = nullptr;
                come1st->order = 1;
                comeLast = come1st;
            }
            else{
                Node* pNew = new Node;
                pNew->prev = comeLast;
                pNew->next = nullptr;
                pNew->data = cus;
                pNew->order = comeLast->order+1;
                comeLast->next = pNew;
                comeLast = pNew;
            }
        }
        if(numCus<MAXSIZE){
            if(numCus==0){
                numCus++;
                X = cus;
                enjoy1st = new Node;
                enjoy1st->data = cus;
                enjoy1st->prev = nullptr;
                enjoy1st->next = nullptr;
                enjoyLast = enjoy1st;
                enjoyLast->come = comeLast;
                comeLast->eating=true;
            }
            else if(numCus<MAXSIZE/2){
                if(cus->energy>=X->energy){
                    cus->prev=X;
                    if(X->next==nullptr){
                        cus->next=X;
                        X->prev=cus;
                        X->next=cus;
                    }
                    else{
                        X->next->prev=cus;
                        cus->next = X->next;
                        X->next=cus;
                    }
                }
                else{
                    cus->next=X;
                    if(X->prev==nullptr){
                        cus->prev=X;
                        X->next=cus;
                        X->prev=cus;
                    }
                    else{
                        X->prev->next=cus;
                        cus->prev = X->prev;
                        X->prev=cus;
                    }
                }
                numCus++;
                X = cus;
                Node* pNew = new Node;
                pNew->prev = enjoyLast;
                pNew->next = nullptr;
                pNew->data = cus;
                enjoyLast->next = pNew;
                enjoyLast = pNew;
                enjoyLast->come = comeLast;
                comeLast->eating=true;
            }
            else {
                int RES=cus->energy-X->energy;
                customer* who=X;
                if(numCus>1){
                    customer* c=X->next;
                    while(c!=X){
                        if(abs(cus->energy-c->energy)>abs(RES)){
                            who=c;
                            RES=cus->energy-c->energy;
                        }
                        c=c->next;
                    }
                }
                X=who;
                if(RES<0){
                    cus->next=X;
                    if(X->prev==nullptr){
                        cus->prev=X;
                        X->next=cus;
                        X->prev=cus;
                    }
                    else{
                        X->prev->next=cus;
                        cus->prev = X->prev;
                        X->prev=cus;
                    }
                }
                else{
                    cus->prev=X;
                    if(X->next==nullptr){
                        cus->next=X;
                        X->prev=cus;
                        X->next=cus;
                    }
                    else{
                        X->next->prev=cus;
                        cus->next = X->next;
                        X->next=cus;
                    }
                }
                numCus++;
                X = cus;
                Node* pNew = new Node;
                pNew->prev = enjoyLast;
                pNew->next = nullptr;
                pNew->data = cus;
                enjoyLast->next = pNew;
                enjoyLast = pNew;
                enjoyLast->come = comeLast;
                comeLast->eating=true;
            }
        }
        else if(numQueue<MAXSIZE){
            if(numQueue==0){
                front=new Node;
                front->order= comeLast->order;
                front->data = cus;
                front->prev = nullptr;
                front->next = nullptr;
                rear = front;
                rear->come = comeLast;
                comeLast->eating=false;
            }
            else{
                Node* iNew = new Node;
                iNew->order = comeLast->order;
                iNew->prev = rear;
                iNew->next = nullptr;
                iNew->data = cus;
                rear->next = iNew;
                rear = iNew;
                rear->come = comeLast;
                comeLast->eating=false;
            }
            numQueue++;
        }
        else{
            delete cus;
        }
    }
    void BLUE(int num)
    {
//			cout << "blue "<< num << endl;
        if(num>numCus){
            num=numCus;
        }
        if(num>0){
            for(int i=0; i<num; i++){
                Node* runEnjoy = enjoy1st;
                Node* who = enjoy1st;
                while(runEnjoy!=nullptr){
                    if(runEnjoy->come->order<who->come->order){
                        who=runEnjoy;
                    }
                    runEnjoy=runEnjoy->next;
                }
                customer* delCus =  who->data;
                Node* finE = who;
                Node* fin = who->come;
                Node* nexFinE = finE->next;
                Node* preFinE = finE->prev;
                if(nexFinE!=nullptr){
                    nexFinE->prev = preFinE;
                }
                if(finE==enjoyLast){
                    enjoyLast = enjoyLast->prev;
                    if(enjoyLast!=nullptr){
                        enjoyLast->next=nullptr;
                    }
                }
                if(preFinE!=nullptr){
                    preFinE->next = nexFinE;
                }
                if(finE==enjoy1st){
                    enjoy1st = enjoy1st->next;
                    if(enjoy1st!=nullptr){
                        enjoy1st->prev=nullptr;
                    }
                }
                delete finE;
                Node* nexFin = fin->next;
                Node* preFin = fin->prev;
                if(nexFin!=nullptr){
                    nexFin->prev = preFin;
                }
                if(fin==comeLast){
                    comeLast = comeLast->prev;
                    if(comeLast!=nullptr){
                        comeLast->next=nullptr;
                    }
                }
                if(preFin!=nullptr){
                    preFin->next = nexFin;
                }
                if(fin==come1st){
                    come1st = come1st->next;
                    if(come1st!=nullptr){
                        come1st->prev=nullptr;
                    }
                }
                delete fin;
                if(numCus>2){
                    customer* nex = delCus->next;
                    customer* pre = delCus->prev;
                    nex->prev = pre;
                    pre->next = nex;
                    if(delCus->energy>0){
                        X=nex;
                    }
                    else{
                        X=pre;
                    }
                }
                else if(numCus==2){
                    customer* nex = delCus->next;
                    nex->next=nullptr;
                    nex->prev=nullptr;
                    X=nex;
                }
                else if(numCus==1){
                    X=nullptr;
                }
                numCus--;
                delete delCus;
            }
            while(numQueue>0 && numCus<MAXSIZE){
                Node* tmp = front;
                tmp->come->eating=true;
                front=front->next;
                if (front==nullptr){
                    rear=nullptr;
                }
                else{
                    front->prev=nullptr;
                }
                numQueue--;
                customer* cus = tmp->data;
                cus->prev=nullptr;
                cus->next=nullptr;
                if(numCus==0){
                    numCus++;
                    X = cus;
                    enjoy1st = tmp;
                    enjoy1st->prev = nullptr;
                    enjoy1st->next = nullptr;
                    enjoyLast = enjoy1st;
                }
                else if(numCus<MAXSIZE/2){
                    if(cus->energy>=X->energy){
                        cus->prev=X;
                        if(X->next==nullptr){
                            cus->next=X;
                            X->prev=cus;
                            X->next=cus;
                        }
                        else{
                            X->next->prev=cus;
                            cus->next = X->next;
                            X->next=cus;
                        }
                    }
                    else{
                        cus->next=X;
                        if(X->prev==nullptr){
                            cus->prev=X;
                            X->next=cus;
                            X->prev=cus;
                        }
                        else{
                            X->prev->next=cus;
                            cus->prev = X->prev;
                            X->prev=cus;
                        }
                    }
                    numCus++;
                    X = cus;
                    tmp->prev = enjoyLast;
                    tmp->next = nullptr;
                    enjoyLast->next = tmp;
                    enjoyLast = tmp;
                }
                else{
                    int RES=cus->energy-X->energy;
                    customer* who=X;
                    if(numCus>1){
                        customer* c=X->next;
                        while(c!=X){
                            if(abs(cus->energy-c->energy)>abs(RES)){
                                who=c;
                                RES=cus->energy-c->energy;
                            }
                            c=c->next;
                        }
                    }
                    X=who;
                    if(RES<0){
                        cus->next=X;
                        if(X->prev==nullptr){
                            cus->prev=X;
                            X->next=cus;
                            X->prev=cus;
                        }
                        else{
                            X->prev->next=cus;
                            cus->prev = X->prev;
                            X->prev=cus;
                        }
                    }
                    else{
                        cus->prev=X;
                        if(X->next==nullptr){
                            cus->next=X;
                            X->prev=cus;
                            X->next=cus;
                        }
                        else{
                            X->next->prev=cus;
                            cus->next = X->next;
                            X->next=cus;
                        }
                    }
                    numCus++;
                    X = cus;
                    tmp->prev = enjoyLast;
                    tmp->next = nullptr;
                    enjoyLast->next = tmp;
                    enjoyLast = tmp;
                }
            }
        }
    }
    void PURPLE()
    {
//			cout << "purple"<< endl;
        if(numQueue>1){
            int numSort=1;
            Node* remCus = front;
            Node* run=front->next;
            for(int cnt=2;cnt<=numQueue;cnt++){
                if(abs(run->data->energy)>abs(remCus->data->energy) || (abs(run->data->energy)==abs(remCus->data->energy) && run->order>remCus->order)){
                    numSort = cnt;
                    remCus = run;
                }
                run=run->next;
            }
            if(numSort>1){
                int N = 0;
                for(int incr=numSort/2;incr>2;incr/=2){
                    for(int k=0;k<incr;k++){
                        for(int i=incr;i<(numSort-k);i+=incr){
                            for(int j=i; j>=incr;j-=incr){
                                Node* J_incr=front;
                                for(int t=0;t<j-incr+k;t++){
                                    J_incr=J_incr->next;
                                }
                                Node* J=J_incr;
                                for(int t=0;t<incr;t++){
                                    J=J->next;
                                }
                                if(abs(J->data->energy)>abs(J_incr->data->energy) ||(abs(J->data->energy)==abs(J_incr->data->energy) && J->order<J_incr->order)){
                                    N++;
                                    Node* nexJ= J->next;
                                    Node* preJ= J->prev;
                                    Node* nex = J_incr->next;
                                    Node* pre = J_incr->prev;
                                    J->prev=pre;
                                    if(pre!=nullptr){
                                        pre->next=J;
                                    }
                                    J->next=nex;
                                    if(nex!=nullptr){
                                        nex->prev=J;
                                    }
                                    J_incr->prev=preJ;
                                    if(preJ!=nullptr){
                                        preJ->next=J_incr;
                                    }
                                    J_incr->next=nexJ;
                                    if(nexJ!=nullptr){
                                        nexJ->prev=J_incr;
                                    }
                                    if(front==J_incr){
                                        front=J;
                                    }
                                    if(rear==J){
                                        rear=J_incr;
                                    }
                                }
                                else{
                                    break;
                                }
                            }
                        }
                    }
                }
                for(int i=1;i<numSort;i++){
                    for(int j=i; j>=1;j--){
                        Node* J_1=front;
                        for(int t=0;t<j-1;t++){
                            J_1=J_1->next;
                        }
                        Node* J=J_1->next;
                        if(abs(J->data->energy)>abs(J_1->data->energy) ||(abs(J->data->energy)==abs(J_1->data->energy) && J->order<J_1->order)){
                            N++;
                            Node* nexJ= J->next;
                            Node* preJ_1= J_1->prev;
                            J->prev=preJ_1;
                            if(preJ_1!=nullptr){
                                preJ_1->next=J;
                            }
                            J_1->next=nexJ;
                            if(nexJ!=nullptr){
                                nexJ->prev=J_1;
                            }
                            J->next=J_1;
                            J_1->prev=J;
                            if(front==J_1){
                                front=J;
                            }
                            if(rear==J){
                                rear=J_1;
                            }
                        }
                        else{
                            break;
                        }
                    }
                }
                BLUE(N%MAXSIZE);
            }
        }
    }
    void REVERSAL()
    {
//			cout << "reversal" << endl;
        if(numCus>1){
            Node* magician=nullptr;
            Node* spirit=nullptr;
            Node* tailMa=nullptr;
            Node* tailSpi=nullptr;
            int numMagic=0;
            int numSpirit=0;
            customer* c = X;
            if(c!=nullptr){
                for(int i=0;i<numCus;i++){
                    if(c->energy>0){
                        if(tailMa==nullptr){
                            magician = new Node;
                            magician->data = c;
                            magician->next = nullptr;
                            magician->prev = nullptr;
                            tailMa = magician;
                        }
                        else{
                            Node* newMa = new Node;
                            newMa->data=c;
                            newMa->prev=tailMa;
                            newMa->next=nullptr;
                            tailMa->next=newMa;
                            tailMa=newMa;
                        }
                        numMagic++;
                    }
                    else{
                        if(tailSpi==nullptr){
                            spirit = new Node;
                            spirit->data = c;
                            spirit->next = nullptr;
                            spirit->prev = nullptr;
                            tailSpi=spirit;
                        }
                        else{
                            Node* newSpi = new Node;
                            newSpi->data=c;
                            newSpi->prev=tailSpi;
                            newSpi->next=nullptr;
                            tailSpi->next=newSpi;
                            tailSpi=newSpi;
                        }
                        numSpirit++;
                    }
                    c = c->prev;
                }
            }
            if(numMagic>1){
                int low = 0;
                Node* lowMa = magician;
                int high = numMagic-1;
                Node* highMa = tailMa;
                while(high>low){
                    if(lowMa->data->prev==highMa->data && lowMa->data->next==highMa->data){}
                    else if(lowMa->data->prev==highMa->data){
                        customer* nex = lowMa->data->next;
                        customer* pre = highMa->data->prev;
                        lowMa->data->prev = pre;
                        lowMa->data->next = highMa->data;
                        highMa->data->prev = lowMa->data;
                        highMa->data->next = nex;
                        nex->prev = highMa->data;
                        pre->next = lowMa->data;
                    }
                    else if(lowMa->data->next==highMa->data){
                        customer* nex = highMa->data->next;
                        customer* pre = lowMa->data->prev;
                        lowMa->data->prev = highMa->data;
                        lowMa->data->next = nex;
                        highMa->data->prev = pre;
                        highMa->data->next = lowMa->data;
                        nex->prev = lowMa->data;
                        pre->next = highMa->data;
                    }
                    else{
                        customer* nexLow = lowMa->data->next;
                        customer* preLow = lowMa->data->prev;
                        customer* nexHigh = highMa->data->next;
                        customer* preHigh = highMa->data->prev;
                        lowMa->data->next = nexHigh;
                        lowMa->data->prev = preHigh;
                        highMa->data->next = nexLow;
                        highMa->data->prev = preLow;
                        nexLow->prev = highMa->data;
                        preLow->next = highMa->data;
                        nexHigh->prev = lowMa->data;
                        preHigh->next = lowMa->data;
                    }
                    lowMa=lowMa->next;
                    low++;
                    highMa=highMa->prev;
                    high--;
                }
            }
            if(numSpirit>1){
                int low = 0;
                Node* lowMa = spirit;
                int high = numSpirit-1;
                Node* highMa = tailSpi;
                while(high>low){
                    if(lowMa->data->prev==highMa->data && lowMa->data->next==highMa->data){}
                    else if(lowMa->data->prev==highMa->data){
                        customer* nex = lowMa->data->next;
                        customer* pre = highMa->data->prev;
                        lowMa->data->prev = pre;
                        lowMa->data->next = highMa->data;
                        highMa->data->prev = lowMa->data;
                        highMa->data->next = nex;
                        nex->prev = highMa->data;
                        pre->next = lowMa->data;
                    }
                    else if(lowMa->data->next==highMa->data){
                        customer* nex = highMa->data->next;
                        customer* pre = lowMa->data->prev;
                        lowMa->data->prev = highMa->data;
                        lowMa->data->next = nex;
                        highMa->data->prev = pre;
                        highMa->data->next = lowMa->data;
                        nex->prev = lowMa->data;
                        pre->next = highMa->data;
                    }
                    else{
                        customer* nexLow = lowMa->data->next;
                        customer* preLow = lowMa->data->prev;
                        customer* nexHigh = highMa->data->next;
                        customer* preHigh = highMa->data->prev;
                        lowMa->data->next = nexHigh;
                        lowMa->data->prev = preHigh;
                        highMa->data->next = nexLow;
                        highMa->data->prev = preLow;
                        nexLow->prev = highMa->data;
                        preLow->next = highMa->data;
                        nexHigh->prev = lowMa->data;
                        preHigh->next = lowMa->data;
                    }
                    lowMa=lowMa->next;
                    low++;
                    highMa=highMa->prev;
                    high--;
                }
            }
            while(magician!=nullptr){
                Node* tmp = magician;
                magician = magician->next;
                delete tmp;
            }
            while(spirit!=nullptr){
                Node* tmp = spirit;
                spirit = spirit->next;
                delete tmp;
            }
        }
    }
    void UNLIMITED_VOID()
    {
//			cout << "unlimited_void" << endl;
        if(numCus>=4){
            customer* ansX=X;
            int ansTail=3;
            int ansMini=2147483647;
            customer* begin=X;
            for(int k = 0; k<numCus;k++){
                customer* run=begin;
                int sum = 0;
                for (int i = 0; i < 4; i++) {
                    sum += run->energy;
                    run=run->next;
                }
                if(sum<ansMini || (sum==ansMini && ansTail<=3)){
                    ansMini=sum;
                    ansX=begin;
                    ansTail=3;
                }
                for (int i = 4; i < numCus; i++) {
                    sum = sum + run->energy;
                    if(sum<ansMini || (sum==ansMini && ansTail<=i)){
                        ansMini=sum;
                        ansX=begin;
                        ansTail=i;
                    }
                    run=run->next;
                }
                begin=begin->next;
            }
            customer* headSub = ansX;
            customer* tailSub = headSub;
            customer* leastEnergy = headSub;
            for(int i=0;i<ansTail;i++){
                tailSub = tailSub->next;
                if(tailSub->energy<leastEnergy->energy){
                    leastEnergy = tailSub;
                }
            }
            customer* forPrint = leastEnergy;
            for(int i=0;i<ansTail+1;i++){
                forPrint->print();
                if(forPrint==tailSub){
                    forPrint=headSub;
                }
                else{
                    forPrint=forPrint->next;
                }
            }
        }
    }
    void DOMAIN_EXPANSION()
    {
//			cout << "domain_expansion" << endl;
        if(numCus>1){
            int sumMagic=0;
            int sumSpirit = 0;
            int numMagic = 0;
            int numSpirit = 0;
            customer* onTable = X;
            for(int i=0;i<numCus;i++){
                if(onTable->energy>0){
                    sumMagic+=onTable->energy;
                    numMagic++;
                }
                else if(onTable->energy<0){
                    sumSpirit+=onTable->energy;
                    numSpirit++;
                }
                onTable=onTable->next;
            }
            Node* inQueue = front;
            for(int i=0;i<numQueue;i++){
                if(inQueue->data->energy>0){
                    sumMagic+=inQueue->data->energy;
                    numMagic++;
                }
                else if(inQueue->data->energy<0){
                    sumSpirit+=inQueue->data->energy;
                    numSpirit++;
                }
                inQueue=inQueue->next;
            }
            Node* r;
            if (sumMagic>=abs(sumSpirit) && numSpirit>0){
                r = comeLast;
                while(r!=nullptr) {
                    if (r->data->energy < 0) {
                        r->data->print();
                    }
                    r = r->prev;
                }
                r = enjoy1st;
                while(r!=nullptr){
                    Node* tmp = r;
                    r=r->next;
                    if(tmp->data->energy<0) {
                        Node *tmpNex = tmp->next;
                        Node *tmpPre = tmp->prev;
                        if (tmpNex != nullptr) {
                            tmpNex->prev = tmpPre;
                        }
                        if (tmp == enjoyLast) {
                            enjoyLast = enjoyLast->prev;
                            if (enjoyLast != nullptr) {
                                enjoyLast->next = nullptr;
                            }
                        }
                        if (tmpPre != nullptr) {
                            tmpPre->next = tmpNex;
                        }
                        if (tmp == enjoy1st) {
                            enjoy1st = enjoy1st->next;
                            if (enjoy1st != nullptr) {
                                enjoy1st->prev = nullptr;
                            }
                        }
                        delete tmp;
                    }
                }
                r = front;
                while(r!=nullptr){
                    Node* tmp= r;
                    r=r->next;
                    if(tmp->data->energy<0){
                        Node* tmpNex=tmp->next;
                        Node* tmpPre=tmp->prev;
                        if(tmpNex!=nullptr){
                            tmpNex->prev=tmpPre;
                        }
                        if(tmp==rear){
                            rear=rear->prev;
                            if(rear!=nullptr){
                                rear->next=nullptr;
                            }
                        }
                        if(tmpPre!=nullptr){
                            tmpPre->next=tmpNex;
                        }
                        if(tmp==front){
                            front=front->next;
                            if(front!=nullptr){
                                front->prev=nullptr;
                            }
                        }
                        delete tmp;
                    }
                }
                r = come1st;
                while(r!=nullptr){
                    Node* del = r;
                    r=r->next;
                    if(del->data->energy<0){
                        Node* nexDel=del->next;
                        Node* preDel=del->prev;
                        if(nexDel!=nullptr){
                            nexDel->prev=preDel;
                        }
                        if(del==comeLast){
                            comeLast=comeLast->prev;
                            if(comeLast!=nullptr){
                                comeLast->next=nullptr;
                            }
                        }
                        if(preDel!=nullptr){
                            preDel->next=nexDel;
                        }
                        if(del==come1st){
                            come1st=come1st->next;
                            if(come1st!=nullptr){
                                come1st->prev=nullptr;
                            }
                        }
                        customer* delCus = del->data;
                        if(del->eating){
                            if(numCus>2){
                                customer* nex = delCus->next;
                                customer* pre = delCus->prev;
                                nex->prev = pre;
                                pre->next = nex;
                                if(delCus->energy>0){
                                    X=nex;
                                }
                                else{
                                    X=pre;
                                }
                            }
                            else if(numCus==2){
                                customer* nex = delCus->next;
                                nex->next=nullptr;
                                nex->prev=nullptr;
                                X=nex;
                            }
                            else if(numCus==1){
                                X=nullptr;
                            }
                            numCus--;
                            delete delCus;
                        }
                        else{
                            numQueue--;
                            delete delCus;
                        }
                        delete del;
                    }
                }
            }
            else if(sumMagic<abs(sumSpirit) && numMagic>0){
                r = comeLast;
                while(r!=nullptr) {
                    if (r->data->energy > 0) {
                        r->data->print();
                    }
                    r = r->prev;
                }
                r = enjoy1st;
                while(r!=nullptr){
                    Node* tmp = r;
                    r=r->next;
                    if(tmp->data->energy>0) {
                        Node *tmpNex = tmp->next;
                        Node *tmpPre = tmp->prev;
                        if (tmpNex != nullptr) {
                            tmpNex->prev = tmpPre;
                        }
                        if (tmp == enjoyLast) {
                            enjoyLast = enjoyLast->prev;
                            if (enjoyLast != nullptr) {
                                enjoyLast->next = nullptr;
                            }
                        }
                        if (tmpPre != nullptr) {
                            tmpPre->next = tmpNex;
                        }
                        if (tmp == enjoy1st) {
                            enjoy1st = enjoy1st->next;
                            if (enjoy1st != nullptr) {
                                enjoy1st->prev = nullptr;
                            }
                        }
                        delete tmp;
                    }
                }
                r = front;
                while(r!=nullptr){
                    Node* tmp= r;
                    r=r->next;
                    if(tmp->data->energy>0){
                        Node* tmpNex=tmp->next;
                        Node* tmpPre=tmp->prev;
                        if(tmpNex!=nullptr){
                            tmpNex->prev=tmpPre;
                        }
                        if(tmp==rear){
                            rear=rear->prev;
                            if(rear!=nullptr){
                                rear->next=nullptr;
                            }
                        }
                        if(tmpPre!=nullptr){
                            tmpPre->next=tmpNex;
                        }
                        if(tmp==front){
                            front=front->next;
                            if(front!=nullptr){
                                front->prev=nullptr;
                            }
                        }
                        delete tmp;
                    }
                }
                r = come1st;
                while(r!=nullptr){
                    Node* del = r;
                    r=r->next;
                    if(del->data->energy>0){
                        Node* nexDel=del->next;
                        Node* preDel=del->prev;
                        if(nexDel!=nullptr){
                            nexDel->prev=preDel;
                        }
                        if(del==comeLast){
                            comeLast=comeLast->prev;
                            if(comeLast!=nullptr){
                                comeLast->next=nullptr;
                            }
                        }
                        if(preDel!=nullptr){
                            preDel->next=nexDel;
                        }
                        if(del==come1st){
                            come1st=come1st->next;
                            if(come1st!=nullptr){
                                come1st->prev=nullptr;
                            }
                        }
                        customer* delCus = del->data;
                        if(del->eating){
                            if(numCus>2){
                                customer* nex = delCus->next;
                                customer* pre = delCus->prev;
                                nex->prev = pre;
                                pre->next = nex;
                                if(delCus->energy>0){
                                    X=nex;
                                }
                                else{
                                    X=pre;
                                }
                            }
                            else if(numCus==2){
                                customer* nex = delCus->next;
                                nex->next=nullptr;
                                nex->prev=nullptr;
                                X=nex;
                            }
                            else if(numCus==1){
                                X=nullptr;
                            }
                            numCus--;
                            delete delCus;
                        }
                        else{
                            numQueue--;
                            delete delCus;
                        }
                        delete del;
                    }
                }
            }
            while(numQueue>0 && numCus<MAXSIZE){
                Node* tmp = front;
                tmp->come->eating=true;
                front=front->next;
                if (front==nullptr){
                    rear=nullptr;
                }
                else{
                    front->prev=nullptr;
                }
                numQueue--;
                customer* cus = tmp->data;
                cus->prev=nullptr;
                cus->next=nullptr;
                if(numCus==0){
                    numCus++;
                    X = cus;
                    enjoy1st = tmp;
                    enjoy1st->prev = nullptr;
                    enjoy1st->next = nullptr;
                    enjoyLast = enjoy1st;
                }
                else if(numCus<MAXSIZE/2){
                    if(cus->energy>=X->energy){
                        cus->prev=X;
                        if(X->next==nullptr){
                            cus->next=X;
                            X->prev=cus;
                            X->next=cus;
                        }
                        else{
                            X->next->prev=cus;
                            cus->next = X->next;
                            X->next=cus;
                        }
                    }
                    else{
                        cus->next=X;
                        if(X->prev==nullptr){
                            cus->prev=X;
                            X->next=cus;
                            X->prev=cus;
                        }
                        else{
                            X->prev->next=cus;
                            cus->prev = X->prev;
                            X->prev=cus;
                        }
                    }
                    numCus++;
                    X = cus;
                    tmp->prev = enjoyLast;
                    tmp->next = nullptr;
                    enjoyLast->next = tmp;
                    enjoyLast = tmp;
                }
                else{
                    int RES=cus->energy-X->energy;
                    customer* who=X;
                    if(numCus>1){
                        customer* c=X->next;
                        while(c!=X){
                            if(abs(cus->energy-c->energy)>abs(RES)){
                                who=c;
                                RES=cus->energy-c->energy;
                            }
                            c=c->next;
                        }
                    }
                    X=who;
                    if(RES<0){
                        cus->next=X;
                        if(X->prev==nullptr){
                            cus->prev=X;
                            X->next=cus;
                            X->prev=cus;
                        }
                        else{
                            X->prev->next=cus;
                            cus->prev = X->prev;
                            X->prev=cus;
                        }
                    }
                    else{
                        cus->prev=X;
                        if(X->next==nullptr){
                            cus->next=X;
                            X->prev=cus;
                            X->next=cus;
                        }
                        else{
                            X->next->prev=cus;
                            cus->next = X->next;
                            X->next=cus;
                        }
                    }
                    numCus++;
                    X = cus;
                    tmp->prev = enjoyLast;
                    tmp->next = nullptr;
                    enjoyLast->next = tmp;
                    enjoyLast = tmp;
                }
            }
        }
    }
    void LIGHT(int num)
    {
//			cout << "light " << num << endl;
        if(num==0){
            Node* c=front;
            while(c!=nullptr){
                c->data->print();
                c=c->next;
            }
        }
        else if(num>0){
            if(X!=nullptr){
                X->print();
                customer* c=X->next;
                if(c!=nullptr){
                    while(c!=X){
                        c->print();
                        c=c->next;
                    }
                }
            }
        }
        else{
            if(X!=nullptr){
                X->print();
                customer* c=X->prev;
                if(c!=nullptr){
                    while(c!=X){
                        c->print();
                        c=c->prev;
                    }
                }
            }
        }
    }
};
