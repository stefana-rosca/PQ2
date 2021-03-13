#include"SecondPriorityQueue.h"
#include<iostream>
#include<exception>
#include<vector>

using namespace std;

//Θ(1)
// constructor
SecondPriorityQueue::SecondPriorityQueue(Relation r)
{
	cap = 50;
	len = 0;
	el = new Element[cap];
	rel = r;
}

//O(n)
void SecondPriorityQueue::push(TElem e, TPriority p)
{//1) Array-ul este plin=> trebuie dublata capacitatea
	if (len == cap)
	{
		cap *= 2;
		auto* newElm = new Element[cap]; //creez un array cu capacitatea actualizata
		for (int i = 0; i < cap; i++)   //mut elem in noul array
		{
			newElm[i] = el[i];
		}
		delete[] el;                //sterg din memorie array-ul vechi
		el = newElm;               //redenumesc
	}
	//2) Array-ul este gol
	if (len == 0)
	{
		el[0].first = e;      //adaug pe prima poz
		el[0].second = p;
		len++;
		return;
	}
	//3) Daca mai exista deja elm in Array il adaug pe cel nou la final
	Element newElm;
	newElm.first = e;
	newElm.second = p;
	el[len++] = newElm;
	bubble_up(len - 1); //si apoi il pun in heap in functie de prioritatea sa cu ajutorul functiei bubble_up
}

//best case=O(1), avarage, worst case=O(n)
void SecondPriorityQueue::bubble_up(int p)//p=poz din care trebuie urcat nodul
{
	int poz = p;
	//cat timp pozitia este valida si nu se resprecta relatia
	//parent=(poz-1)/3
	while (poz > 0 && !rel(el[(poz - 1) / 3].second, el[poz].second))
	{
		swap(el[poz], el[(poz - 1) / 3]);//urc el[poz] in locul parintelui
		poz = (poz - 1) / 3;            //continui sa verific daca se respecta relatia
	}
}

//best case=O(1), avarage, worst case=O(n)
void SecondPriorityQueue::bubble_down(int p)
{
	int poz = p;
	int aux = p;  //nodul dintre cei trei copii care indeplineste conditiile de a fi urcat in heap

	// left child = poz * 3 + 1
	// middle child = poz * 3 + 2
	// right child = poz * 3 + 3
	
	//verific pentru toti copiii daca e valid si relatia fata de actualul aux
	// daca copilul are prioritate mai mare decat actualul aux, aux ii primeste val
	if (poz * 3 + 1 < len && rel(el[3 * poz + 1].second, el[aux].second))
	{
		aux = poz * 3 + 1;
	}
	if (poz * 3 + 2 < len && rel(el[3 * poz + 2].second, el[aux].second))
	{
		aux = poz * 3 + 2;
	}
	if (poz * 3 + 3 < len && rel(el[3 * poz + 3].second, el[aux].second))
	{
		aux = poz * 3 + 3;
	}
	if (aux != p)
	{
		swap(el[p], el[aux]);
		bubble_down(aux);
	}
	else
		return;
}

//worst,avarage case=O(n) 
//best case=O(1)
Element SecondPriorityQueue::top() const
{
	if (atMostOne())               //daca sunt mai putin de doua elem
	{
		throw exception();       //arunc exceptie
	}
	else{
		//deoarece trebuie sa returnez elem cu a doua cea mai mare prioritate acesta va fi unul din cei trei copii ai head-ului
		// asa ca e mai usor sa lucrez direct cu indexi(ex: 1 in loc de poz * 3 + 1 pt left child)
		int child = -1;   //child este indexul copilului cu a doua cea mai mare prioritate
		if (1 < len)     //acelasi princiupu ca si cu aux-ul de la functia bubble_down
		{
			child = 1;
		}
		if (2 < len && rel(el[2].second, el[child].second))
		{
			child = 2;
		}
		if (3 < len && rel(el[3].second, el[child].second))
		{
			child = 3;
		}
		if (child != -1)               //daca e valid
		{
			Element PQ2 = el[child];//pq2 primeste val de pe poz elm cu a doua cea mai mare prioritate
			return PQ2;            //il returneaza
		}
	}
}

//worst,avarage case=O(n) 
//best case=O(1)
Element SecondPriorityQueue::pop()
{
	if (atMostOne() == true)              //daca sunt mai putin de doua elm
	{
		throw exception();              //arunc exceptie
	}

	Element deletedElm = top();      //deletedElm primeste elm gasit in functia top
	int i = 0;
	while (i < len)                //parcurg cu i Array-ul
	{
		if (el[i] == top())      //cand gasesc elm egal cu cel gasit in top
		{
			el[i] = el[--len]; //il sterg 
			bubble_down(i);   //ma folosesc de bubble_down pt a reface heap-ul
			break;
		}
		i++;               //continui sa caut
	}
	return deletedElm;   //returnez elementul pe care l-am sters
}

//best,avarage,worst case=O(1)
bool SecondPriorityQueue::atMostOne() const
{
	if(len<2)             //daca lungimea este mai mica decat doi
	{
		return true;    //am maxim un element(sau e gol)
	}
	return false;     //altfel am minim doua elem
}

//Θ(1)
// destructor
SecondPriorityQueue::~SecondPriorityQueue()
{
	delete[] el;
}
